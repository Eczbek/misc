export module Logging;
import std;

/*
Works exactly like std::print. Fail and assert will show verbose logging data (failure location.)
Logging::info("hello world");
Logging::warn("{} + {}", "sweg and", 5);
Logging::fail("{} {}", "the ", " game");
Logging::assert(false == true, "False was not true"); //outputs to cerr
*/

namespace Logging {
    constexpr const char *logName = "last_run_log.txt";
    bool logFileInitialized = false;
    constexpr bool loggingToFileEnabled = true;
    constexpr bool loggingToConsoleEnabled = true;

    enum class Severity { Info, Warning, Failure, Assertion };
    constexpr auto minimumConsoleLoggingSeverity = Severity::Info;
    constexpr auto minimumFileLoggingSeverity = Severity::Info;

    constexpr const char *severityNameLookup[] = {"Info", "Warning", "Failure", "Assertion Failed"};
    constexpr const char *severityColorLookup[] = {"\033[32m", "\033[33m", "\033[31m", "\033[30m"}; //ANSI color codes
    consteval bool meetsMinimumSeverity(Severity a, Severity b) { return static_cast<int>(a) >= static_cast<int>(b); }
    consteval bool isSeverity(Severity a, Severity b) { return static_cast<int>(a) == static_cast<int>(b); }

    template<Severity S, class... LogArgs>
    struct log
    {
        explicit log(std::format_string<LogArgs...> fmt,
                     LogArgs&&... args,
                     std::ostream& outputStream = std::cout,
                     const std::source_location& location = std::source_location::current())
        {
            std::ofstream logFile;
            auto now = std::chrono::round<std::chrono::seconds>(std::chrono::system_clock::now());
            auto severityName = severityNameLookup[static_cast<int>(S)];
            auto severityColor = severityColorLookup[static_cast<int>(S)];

            std::string content = std::format(fmt, std::forward<LogArgs>(args)...);

            if constexpr (loggingToConsoleEnabled && meetsMinimumSeverity(S, minimumConsoleLoggingSeverity)) {
                constexpr auto resetColor = "\033[0m";
                if constexpr (meetsMinimumSeverity(S, Severity::Failure)) {
                    std::print(outputStream,
                               "[{:%Y-%m-%d %H:%M:%S}]\n {}[{}]{}\nFile name: {}\nFunction name: {}\nLine error: {}\nMessage: {}\n",
                               now,
                               severityColor,
                               severityName,
                               resetColor,
                               location.file_name(),
                               location.function_name(),
                               location.line(),
                               content);
                } else {
                    std::print(outputStream, "[{:%Y-%m-%d %H:%M:%S}]\n {}[{}]{} {}\n", now, severityColor, severityName, resetColor, content);
                }
            }

            if constexpr (!loggingToFileEnabled) {
                return;
            }

            if (!logFileInitialized) {
                logFileInitialized = true;
                logFile.open(logName, std::ios::out | std::ios::trunc);
                logFile.close();
            }

            logFile.open(logName, std::ios::out | std::ios::app);
            if (logFile.is_open() && meetsMinimumSeverity(S, minimumFileLoggingSeverity)) {
                if constexpr (meetsMinimumSeverity(S, Severity::Failure)) {
                    std::print(
                        logFile,
                        "[{:%Y-%m-%d %H:%M:%S}]\n [{}]\nFile name: {}\nFunction name: {}\nLine error: {}\nMessage: {}\n",
                        now,
                        severityName,
                        location.file_name(),
                        location.function_name(),
                        location.line(),
                        content);
                } else {
                    std::print(logFile, "[{:%Y-%m-%d %H:%M:%S}]\n [{}] {}\n", now, severityName, content);
                }
                logFile.close();
            }
        }
    };

    export template<class... LogArgs>
    struct info : log<Severity::Info, LogArgs...> {
        using log<Severity::Info, LogArgs...>::log;
    };

    export template<class... LogArgs>
    struct warn : log<Severity::Warning, LogArgs...> {
        using log<Severity::Warning, LogArgs...>::log;
    };

    export template<class... LogArgs>
    struct fail : log<Severity::Failure, LogArgs...> {
        using log<Severity::Failure, LogArgs...>::log;
    };

    export template<typename... LogArgs>
    struct assert {
        assert(
            const bool condition,
            std::format_string<LogArgs...> fmt,
                             LogArgs&&... args,
                             const std::source_location& location = std::source_location::current())
        {
            if (!condition) return;
            log<Severity::Assertion, LogArgs...>(
                std::format_string<LogArgs...>(fmt),
                std::forward<LogArgs>(args)...,
                std::cerr,
                location
            );
            std::abort();
        }
    };

    //Deduction guides:
    template<class... LogArgs>
    info(std::format_string<LogArgs...>, LogArgs&&...) -> info<LogArgs...>;

    template<class... LogArgs>
    warn(std::format_string<LogArgs...>, LogArgs&&...) -> warn<LogArgs...>;

    template<class... LogArgs>
    fail(std::format_string<LogArgs...>, LogArgs&&...) -> fail<LogArgs...>;

    template<typename... LogArgs>
    assert(bool, std::format_string<LogArgs...>, LogArgs&&...) -> assert<LogArgs...>;
}
