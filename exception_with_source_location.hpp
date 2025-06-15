#include <format>
#include <source_location>
#include <iostream>

template<typename ... Args>
struct Message {
    std::format_string<Args...> message;
    std::source_location loc;

    template<typename T>
    consteval Message(const T& m, const std::source_location& location = std::source_location::current()) 
        : message(m), loc(location) {}
};

template <typename... Args>
void Exception(const Message<std::type_identity_t<Args>...>& message, Args&&... args)
{
    std::cout << message.loc.function_name() << '\n';
    std::cout << std::format(message.message, std::forward<Args>(args)...);
}

int main() {
    Exception("abcde {}", 1);
}
