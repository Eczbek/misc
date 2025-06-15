#include <print>
#include <random>
#include <string>
#include <utility>

inline std::mt19937 rng = std::mt19937(std::random_device()());

inline std::string crispiness() noexcept {
	static auto dist = std::uniform_int_distribution(0, 1);
	switch (dist(rng)) {
	case 0:
		return "really";
	case 1:
		return "really " + crispiness();
	}
	std::unreachable();
}

inline std::string cooked() noexcept {
	static auto dist = std::uniform_int_distribution(0, 2);
	switch (dist(rng)) {
	case 0:
		return "scrambled";
	case 1:
		return "poached";
	case 2:
		return "fried";
	}
	std::unreachable();
}

inline std::string protein() noexcept {
	static auto dist = std::uniform_int_distribution(0, 2);
	switch (dist(rng)) {
	case 0:
		return crispiness() + " crispy bacon";
	case 1:
		return "sausage";
	case 2:
		return cooked() + " eggs";
	}
	std::unreachable();
}

inline std::string bread() noexcept {
	static auto dist = std::uniform_int_distribution(0, 2);
	switch (dist(rng)) {
	case 0:
		return "toast";
	case 1:
		return "biscuits";
	case 2:
		return "English muffin";
	}
	std::unreachable();
}

inline std::string breakfast() noexcept {
	static auto dist = std::uniform_int_distribution(0, 2);
	switch (dist(rng)) {
	case 0:
		return protein() + " with " + breakfast() + " on the side";
	case 1:
		return protein();
	case 2:
		return bread();
	}
	std::unreachable();
}

int main() {
	for (int i = 0; i < 50; ++i) {
		std::println("{}", breakfast());
	}
}
