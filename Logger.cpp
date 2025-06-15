#include <cstdint>
#include <format>
#include <fstream>
#include <ostream>
#include <print>
#include <string_view>
#include <syncstream>
#include <utility>

#define FORWARD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

struct Color {
	std::uint8_t red;
	std::uint8_t green;
	std::uint8_t blue;
};

struct Logger {
public:
	Logger(std::ostream& outputStream) noexcept
	: outputStream(outputStream) {}

	template<typename... Arguments>
	void log(const std::format_string<Arguments...> format, Arguments&&... arguments) {
		this->print(Color(255, 255, 255), format, FORWARD(arguments)...);
	}

	template<typename... Arguments>
	void warn(const std::format_string<Arguments...> format, Arguments&&... arguments) {
		this->print(Color(255, 255, 0), format, FORWARD(arguments)...);
	}

	template<typename... Arguments>
	void error(const std::format_string<Arguments...> format, Arguments&&... arguments) {
		this->print(Color(255, 0, 0), format, FORWARD(arguments)...);
	}

	void flush() {
		std::flush(this->outputStream);
	}

private:
	std::osyncstream outputStream;

	template<typename... Arguments>
	void print(const Color color, const std::format_string<Arguments...> format, Arguments&&... arguments) {
		std::print(this->outputStream, "\x1B[38;2;{};{};{}m[{} : {}] ", color.red, color.green, color.blue, __FILE__, __LINE__);
		std::print(this->outputStream, format, FORWARD(arguments)...);
		std::println(this->outputStream, "\x1B[0m");
	}
};


#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main() {
	Logger logger = Logger(std::cout);
	logger.log("log");
	logger.warn("warning");
	logger.error("error");
}
