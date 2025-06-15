#ifndef XIEITE_HEADER_CONCEPTS_ARITHMETIC
#	define XIEITE_HEADER_CONCEPTS_ARITHMETIC

#	include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept Arithmetic = std::is_arithmetic_v<Type>;
}

#endif


#ifndef XIEITE_HEADER_STRINGS_IS_DIGIT
#	define XIEITE_HEADER_STRINGS_IS_DIGIT

#	include <string_view>

namespace xieite::strings {
	[[nodiscard]] constexpr bool isDigit(const char character) noexcept {
		return (character >= '0') && (character <= '9');
		// Apparently digits are guaranteed to be in order
	}
}

#endif


#ifndef XIEITE_HEADER_STRINGS_TRIM
#	define XIEITE_HEADER_STRINGS_TRIM

#	include <cstddef>
#	include <string_view>

namespace xieite::strings {
	[[nodiscard]] constexpr std::string_view trim(const std::string_view string, const char character) noexcept {
		const std::size_t start = string.find_first_not_of(character);
		return (start == std::string_view::npos) ? "" : string.substr(start, string.find_last_not_of(character) - start + 1);
	}

	[[nodiscard]] constexpr std::string_view trim(const std::string_view string, const std::string_view characters) noexcept {
		const std::size_t start = string.find_first_not_of(characters);
		return (start == std::string_view::npos) ? "" : string.substr(start, string.find_last_not_of(characters) - start + 1);
	}
}

#endif


#ifndef XIEITE_HEADER_STRINGS_WHITESPACES
#	define XIEITE_HEADER_STRINGS_WHITESPACES

#	include <string_view>

namespace xieite::strings {
	inline constexpr std::string_view whitespaces = "\t\n\v\f\r ";
}

#endif


#ifndef XIEITE_HEADER_STRINGS_PARSE_NUMBER
#	define XIEITE_HEADER_STRINGS_PARSE_NUMBER

#	include <cmath>
#	include <concepts>
#	include <cstddef>
#	include <string_view>
// #	include "../concepts/arithmetic.hpp"
// #	include "../strings/is_digit.hpp"
// #	include "../strings/trim.hpp"
// #	include "../strings/whitespaces.hpp"

namespace xieite::strings {
	template<xieite::concepts::Arithmetic Number>
	[[nodiscard]] constexpr Number parseNumber(std::string_view value) noexcept {
		value = xieite::strings::trim(value, xieite::strings::whitespaces);
		const bool negative = value[0] == '-';
		if constexpr (std::integral<Number>) {
			Number result = 0;
			for (std::size_t i = negative || (value[0] == '+'); (i < value.size()) && xieite::strings::isDigit(value[i]); ++i) {
				result = result * 10 + (value[i] - '0');
			}
			return negative ? -result : result;
		} else {
			bool point = false;
			Number integer = 0;
			Number decimal = 0;
			int power = 0;
			for (std::size_t i = negative || (value[0] == '+'); i < value.size(); ++i) {
				if (xieite::strings::isDigit(value[i])) {
					Number& part = (point ? decimal : integer);
					part = part * 10 + (value[i] - '0');
				} else if ((value[i] == '.')) {
					point = true;
				} else {
					if ((value[i] == 'E') || (value[i] == 'e')){
						power = xieite::strings::parseNumber<int>(value.substr(i + 1));
					}
					break;
				}
			}
			return (!negative * 2 - 1) * (integer + decimal / std::pow(10, std::floor(std::log10(decimal)) + 1)) * std::pow(10, power);
		}
	}
}

#endif


#ifndef XIEITE_HEADER_STRINGS_VALID_NUMBER
#	define XIEITE_HEADER_STINGS_VALID_NUMBER

#	include <concepts>
#	include <cstddef>
#	include <string_view>
// #	include "../concepts/arithmetic.hpp"
// #	include "../strings/is_digit.hpp"
// #	include "../strings/trim.hpp"
// #	include "../strings/whitespaces.hpp"

namespace xieite::strings {
	template<xieite::concepts::Arithmetic Number>
	[[nodiscard]] constexpr Number validNumber(std::string_view value) noexcept {
		value = xieite::strings::trim(value, xieite::strings::whitespaces);
		if (!xieite::strings::isDigit(value[0]) && (value[0] != '+') && (value[0] != '-')) {
			return false;
		}
		if constexpr (std::integral<Number>) {
			for (std::size_t i = 1; i < value.size(); ++i) {
				if (!xieite::strings::isDigit(value[i])) {
					return false;
				}
			}
		} else {
			bool point = false;
			for (std::size_t i = 1; i < value.size(); ++i) {
				if (xieite::strings::isDigit(value[i])) {
					continue;
				} else if (!point && (value[i] == '.')) {
					point = true;
				} else if ((value[i] == 'E') || (value[i] == 'e')) {
					return xieite::strings::validNumber<int>(value.substr(i));
				} else {
					return false;
				}
			}
		}
		return true;
	}
}

#endif


#ifndef XIEITE_HEADER_STRINGS_UNFORMAT
#	define XIEITE_HEADER_STRINGS_UNFORMAT

#	include <array>
#	include <concepts>
#	include <cstddef>
#	include <stdexcept>
#	include <string_view>
#	include <tuple>
#	include <utility>
// #	include "../concepts/arithmetic.hpp"
// #	include "../strings/parse_number.hpp"
// #	include "../strings/valid_number.hpp"

namespace xieite::strings {
	template<typename... Types>
	requires((... && (xieite::concepts::Arithmetic<Types> || std::constructible_from<std::string_view>)))
	constexpr void unformat(const std::string_view input, const std::string_view format, Types&... results) {
		std::array<std::string_view, sizeof...(Types)> strings;
		bool indicesDecided = false;
		bool hasIndices;
		std::size_t nextIndex = 0;
		std::size_t i = 0;
		std::size_t j = 0;
		while ((i < format.size()) && (j < input.size())) {
			if ((format[i] == '{') && ((format.size() - i) > 1) && (format[i + 1] == '{') || (format[i] == '}') && ((format.size() - i) > 1) && (format[i + 1] == '}')) {
				++i;
			} else if (format[i] == '{') {
				++i;
				const std::size_t indexEnd = format.find('}', i);
				if (indexEnd == std::string_view::npos) {
					throw std::invalid_argument("Last indexed placeholder not terminated");
				}
				const std::string_view indexString = trim(format.substr(i, indexEnd - i), whitespaces);
				i = indexEnd;
				if (!indicesDecided) {
					indicesDecided = true;
					hasIndices = !!indexString.size();
				} else if (hasIndices != !!indexString.size()) {
					throw std::invalid_argument("Placeholders inconsistently indexed");
				}
				if (hasIndices && !validNumber<std::size_t>(indexString)) {
					throw std::invalid_argument("Placeholder contains invalid index");
				}
				const std::size_t index = hasIndices ? xieite::strings::parseNumber<std::size_t>(indexString) : nextIndex;
				++nextIndex;
				if (index >= sizeof...(Types)) {
					throw std::invalid_argument("Placeholder index out of range");
				}
				const std::size_t inputEnd = ((format.size() - i) > 1) ? input.find(format[i + 1], j) : std::string_view::npos;
				const std::size_t inputLength = (inputEnd != std::string_view::npos) ? (inputEnd - j) : std::string_view::npos;
				strings[index] = input.substr(j, inputLength);
				j = inputEnd - 1;
			}
			++i;
			++j;
		}
		([&results..., &strings]<std::size_t... indices>(std::index_sequence<indices...>) {
			const std::tuple<Types&...> tuple = std::make_tuple(std::ref(results)...);
			(..., ([&strings, tuple] {
				if constexpr (xieite::concepts::Arithmetic<Types>) {
					if (!xieite::strings::validNumber<Types>(strings[indices])) {
						throw std::invalid_argument("Input cannot be parsed as number");
					}
					std::get<indices>(tuple) = xieite::strings::parseNumber<Types>(strings[indices]);
				} else {
					std::get<indices>(tuple) = Types(strings[indices]);
				}
			})());
		})(std::make_index_sequence<sizeof...(Types)>());
	}
}

#endif



#include <iostream>
#include <string>

int main() {
    std::string x;
    int y;
    double z;

    const std::string_view input = "Hello, world! 20 + 3.14159";
    xieite::strings::unformat(input, "Hello, {1}! {0} + {2}", y, x, z);

    std::cout
        << x << '\n'
        << y << '\n'
        << z << '\n';
}
