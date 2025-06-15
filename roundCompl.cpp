#include <cmath>
#include <print>

constexpr double roundCompl(double n) {
	const double foo = (n < 0) ? std::ceil(n) : std::floor(n);
	if (std::abs(n - foo) < 0.5) {
		return (n < 0) ? std::floor(n) : std::ceil(n);
	}
	return foo;
}

int main() {
	std::println("{}", roundCompl(4.0)); // 4
	std::println("{}", roundCompl(4.4)); // 5
	std::println("{}", roundCompl(4.5)); // 4
	std::println("{}", roundCompl(4.6)); // 4
	std::println("{}", roundCompl(5.0)); // 5
	std::println("{}", roundCompl(-4.0)); // -4
	std::println("{}", roundCompl(-4.4)); // -5
	std::println("{}", roundCompl(-4.5)); // -4
	std::println("{}", roundCompl(-4.6)); // -4
	std::println("{}", roundCompl(-5.0)); // -5
}
