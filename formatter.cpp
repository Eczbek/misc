#include <format>
#include <print>

struct Foo {};

template<>
struct std::formatter<Foo> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Foo&, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "Foo");
    }
};

int main() {
    std::println("{}", Foo());
}
