#include <array>
#include <concepts>
#include <cstddef>
#include <deque>
// #include <flat_map>
// #include <flat_set>
#include <forward_list>
#include <list>
#include <map>
// #include <mdspan>
#include <print>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template<typename Iterator, typename Value = decltype(*std::declval<Iterator>())>
concept ConstantIterator = !std::is_assignable_v<decltype(*std::declval<Iterator>()), Value>;

template<auto getter>
struct Helper {
	[[nodiscard]] constexpr std::string_view operator()() noexcept {
		static constexpr auto get = [] -> std::string {
			return xieite::strings::replace(getter(), " >", ">");
		};
		static constexpr auto data = xieite::containers::makeArray<char, get().size()>(get());
		return std::string_view(data.begin(), data.end());
	}
};

template<typename Type>
struct Name
: Helper<[] -> std::string_view {
	return xieite::types::name<Type>;
}> {};

template<typename Type>
inline constexpr std::string_view name = Name<Type>()();

template<>
struct Name<std::string> {
	[[nodiscard]] constexpr std::string_view operator()() noexcept {
		return "std::string";
	}
};

template<>
struct Name<std::wstring> {
	[[nodiscard]] constexpr std::string_view operator()() noexcept {
		return "std::wstring";
	}
};

template<>
struct Name<std::u8string> {
	[[nodiscard]] constexpr std::string_view operator()() noexcept {
		return "std::u8string";
	}
};

template<>
struct Name<std::u16string> {
	[[nodiscard]] constexpr std::string_view operator()() noexcept {
		return "std::u16string";
	}
};

template<>
struct Name<std::u32string> {
	[[nodiscard]] constexpr std::string_view operator()() noexcept {
		return "std::u32string";
	}
};

template<typename Character, typename Traits, typename Allocator>
struct Name<std::basic_string<Character, Traits, Allocator>>
: Helper<[] -> std::string {
	std::string result = "std::basic_string<" + std::string(name<Character>);
	if constexpr (!std::same_as<Traits, std::char_traits<Character>>) {
		result += ", " + std::string(name<Traits>);
	}
	if constexpr (!std::same_as<Allocator, std::allocator<Character>>) {
		result += ", " + std::string(name<Allocator>);
	}
	return result + ">";
}> {};

template<typename Iterator>
struct Name<std::reverse_iterator<Iterator>>
: Helper<[] -> std::string {
	return "std::reverse_iterator<" + std::string(name<Iterator>) + ">";
}> {};

template<>
struct Name<std::reverse_iterator<std::string::iterator>>
: Helper<[] -> std::string_view {
	return "std::string::reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::string::const_iterator>>
: Helper<[] -> std::string_view {
	return "std::string::const_reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::wstring::iterator>>
: Helper<[] -> std::string_view {
	return "std::wstring::reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::wstring::const_iterator>>
: Helper<[] -> std::string_view {
	return "std::wstring::const_reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::u8string::iterator>>
: Helper<[] -> std::string_view {
	return "std::u8string::reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::u8string::const_iterator>>
: Helper<[] -> std::string_view {
	return "std::u8string::const_reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::u16string::iterator>>
: Helper<[] -> std::string_view {
	return "std::u16string::reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::u16string::const_iterator>>
: Helper<[] -> std::string_view {
	return "std::u16string::const_reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::u32string::iterator>>
: Helper<[] -> std::string_view {
	return "std::u32string::reverse_iterator";
}> {};

template<>
struct Name<std::reverse_iterator<std::u32string::const_iterator>>
: Helper<[] -> std::string_view {
	return "std::u32string::const_reverse_iterator";
}> {};

template<typename Iterator>
struct Name<std::basic_const_iterator<Iterator>>
: Helper<[] -> std::string {
	return "std::basic_const_iterator<" + std::string(name<Iterator>) + ">";
}> {};

template<typename Iterator, typename Container>
struct Name<__gnu_cxx::__normal_iterator<Iterator, Container>>
: Helper<[] -> std::string {
	std::string result = std::string(name<Container>) + "::";
	if constexpr (ConstantIterator<Iterator>) {
		result += "const_";
	}
	return result + "iterator";
}> {};

template<typename Value, typename Reference, typename Pointer>
struct Name<std::_Deque_iterator<Value, Reference, Pointer>>
: Helper<[] -> std::string {
	std::string result = "std::deque<" + std::string(name<Value>) + ">::";
	if (std::is_const_v<std::remove_reference_t<Reference>>) {
		result += "const_";
	}
	return result + "iterator";
}> {};

template<typename Value>
struct Name<std::_Fwd_list_iterator<Value>>
: Helper<[] -> std::string {
	return "std::forward_list<" + std::string(name<Value>) + ">::iterator";
}> {};

template<typename Value>
struct Name<std::_Fwd_list_const_iterator<Value>>
: Helper<[] -> std::string {
	return "std::forward_list<" + std::string(name<Value>) + ">::const_iterator";
}> {};

template<typename Value, typename Allocator>
struct Name<std::list<Value, Allocator>>
: Helper<[] -> std::string {
	std::string result = "std::list<" + std::string(name<Value>);
	if constexpr (!std::same_as<Allocator, std::allocator<Value>>) {
		result += ", " + std::string(name<Allocator>);
	}
	return result + ">";
}> {};

template<typename Value>
struct Name<std::_List_iterator<Value>>
: Helper<[] -> std::string {
	return "std::list<" + std::string(name<Value>) + ">::iterator";
}> {};

template<typename Value>
struct Name<std::_List_const_iterator<Value>>
: Helper<[] -> std::string {
	return "std::list<" + std::string(name<Value>) + ">::const_iterator";
}> {};

template<typename Value>
struct Name<std::_Rb_tree_const_iterator<Value>>
: Helper<[] -> std::string {
	return "std::set<" + std::string(name<Value>) + ">::const_iterator";
}> {};

template<typename Key, typename Value>
struct Name<std::_Rb_tree_iterator<std::pair<Key, Value>>>
: Helper<[] -> std::string {
	return "std::map<" + std::string(name<std::remove_const_t<Key>>) + ", " + std::string(name<Value>) + ">::iterator";
}> {};

template<typename Key, typename Value>
struct Name<std::_Rb_tree_const_iterator<std::pair<Key, Value>>>
: Helper<[] -> std::string {
	return "std::map<" + std::string(name<std::remove_const_t<Key>>) + ", " + std::string(name<Value>) + ">::const_iterator";
}> {};

template<typename Value, bool constantIterators, bool cache>
struct Name<std::__detail::_Node_iterator<Value, constantIterators, cache>>
: Helper<[] -> std::string {
	return "std::unordered_set<" + std::string(name<Value>) + ">::iterator";
}> {};

template<typename Value, bool constantIterators, bool cache>
struct Name<std::__detail::_Node_const_iterator<Value, constantIterators, cache>>
: Helper<[] -> std::string {
	return "std::unordered_set<" + std::string(name<Value>) + ">::const_iterator";
}> {};

template<typename Key, typename Value, bool constantIterators, bool cache>
struct Name<std::__detail::_Node_iterator<std::pair<Key, Value>, constantIterators, cache>>
: Helper<[] -> std::string {
	return "std::unordered_map<" + std::string(name<std::remove_const_t<Key>>) + ", " + std::string(name<Value>) + ">::iterator";
}> {};

template<typename Key, typename Value, bool constantIterators, bool cache>
struct Name<std::__detail::_Node_const_iterator<std::pair<Key, Value>, constantIterators, cache>>
: Helper<[] -> std::string {
	return "std::unordered_map<" + std::string(name<std::remove_const_t<Key>>) + ", " + std::string(name<Value>) + ">::const_iterator";
}> {};

template<typename T>
struct Foo {};

int main() {
	std::println("{}", name<Foo<std::string>>);
	
	std::println("{}", name<int>);
	std::println("{}", name<std::string>);
	std::println("{}", name<std::string::iterator>);
	std::println("{}", name<std::string::reverse_iterator>);
	std::println("{}", name<std::string::const_iterator>);
	std::println("{}", name<std::string::const_reverse_iterator>);
	std::println("{}", name<std::wstring>);
	std::println("{}", name<std::wstring::iterator>);
	std::println("{}", name<std::wstring::reverse_iterator>);
	std::println("{}", name<std::wstring::const_iterator>);
	std::println("{}", name<std::wstring::const_reverse_iterator>);
	std::println("{}", name<std::u8string>);
	std::println("{}", name<std::u8string::iterator>);
	std::println("{}", name<std::u8string::reverse_iterator>);
	std::println("{}", name<std::u8string::const_iterator>);
	std::println("{}", name<std::u8string::const_reverse_iterator>);
	std::println("{}", name<std::u16string>);
	std::println("{}", name<std::u16string::iterator>);
	std::println("{}", name<std::u16string::reverse_iterator>);
	std::println("{}", name<std::u16string::const_iterator>);
	std::println("{}", name<std::u16string::const_reverse_iterator>);
	std::println("{}", name<std::u32string>);
	std::println("{}", name<std::u32string::iterator>);
	std::println("{}", name<std::u16string::reverse_iterator>);
	std::println("{}", name<std::u16string::const_iterator>);
	std::println("{}", name<std::u32string::const_reverse_iterator>);
	std::println("{}", name<std::array<int, 5>>);
	std::println("{}", name<std::array<int, 5>::iterator>);
	std::println("{}", name<std::array<int, 5>::reverse_iterator>);
	std::println("{}", name<std::array<int, 5>::const_iterator>);
	std::println("{}", name<std::array<int, 5>::const_reverse_iterator>);
	std::println("{}", name<std::vector<int>>);
	std::println("{}", name<std::vector<int>::iterator>);
	std::println("{}", name<std::vector<int>::reverse_iterator>);
	std::println("{}", name<std::vector<int>::const_iterator>);
	std::println("{}", name<std::vector<int>::const_reverse_iterator>);
	std::println("{}", name<std::deque<int>>);
	std::println("{}", name<std::deque<int>::iterator>);
	std::println("{}", name<std::deque<int>::reverse_iterator>);
	std::println("{}", name<std::deque<int>::const_iterator>);
	std::println("{}", name<std::deque<int>::const_reverse_iterator>);
	std::println("{}", name<std::forward_list<int>>);
	std::println("{}", name<std::forward_list<int>::iterator>);
	std::println("{}", name<std::forward_list<int>::const_iterator>);
	std::println("{}", name<std::list<int>>);
	std::println("{}", name<std::list<int>::iterator>);
	std::println("{}", name<std::list<int>::reverse_iterator>);
	std::println("{}", name<std::list<int>::const_iterator>);
	std::println("{}", name<std::list<int>::const_reverse_iterator>);
	std::println("{}", name<std::set<int>>);
	std::println("{}", name<std::set<int>::iterator>);
	std::println("{}", name<std::set<int>::reverse_iterator>);
	std::println("{}", name<std::set<int>::const_iterator>);
	std::println("{}", name<std::set<int>::const_reverse_iterator>);
	std::println("{}", name<std::map<int, int>>);
	std::println("{}", name<std::map<int, int>::iterator>);
	std::println("{}", name<std::map<int, int>::reverse_iterator>);
	std::println("{}", name<std::map<int, int>::const_iterator>);
	std::println("{}", name<std::map<int, int>::const_reverse_iterator>);
	std::println("{}", name<std::multiset<int>>);
	std::println("{}", name<std::multiset<int>::iterator>);
	std::println("{}", name<std::multiset<int>::reverse_iterator>);
	std::println("{}", name<std::multiset<int>::const_iterator>);
	std::println("{}", name<std::multiset<int>::const_reverse_iterator>);
	std::println("{}", name<std::multimap<int, int>>);
	std::println("{}", name<std::multimap<int, int>::iterator>);
	std::println("{}", name<std::multimap<int, int>::reverse_iterator>);
	std::println("{}", name<std::multimap<int, int>::const_iterator>);
	std::println("{}", name<std::multimap<int, int>::const_reverse_iterator>);
	std::println("{}", name<std::unordered_set<int>>);
	std::println("{}", name<std::unordered_set<int>::iterator>);
	std::println("{}", name<std::unordered_set<int>::const_iterator>);
	std::println("{}", name<std::unordered_map<int, int>>);
	std::println("{}", name<std::unordered_map<int, int>::iterator>);
	std::println("{}", name<std::unordered_map<int, int>::const_iterator>);
	std::println("{}", name<std::unordered_multiset<int>>);
	std::println("{}", name<std::unordered_multiset<int>::iterator>);
	std::println("{}", name<std::unordered_multiset<int>::const_iterator>);
	std::println("{}", name<std::unordered_multimap<int, int>>);
	std::println("{}", name<std::unordered_multimap<int, int>::iterator>);
	std::println("{}", name<std::unordered_multimap<int, int>::const_iterator>);
	std::println("{}", name<std::stack<int>>);
	std::println("{}", name<std::queue<int>>);
	std::println("{}", name<std::priority_queue<int>>);
	std::println("{}", name<std::span<int>>);
	std::println("{}", name<std::span<int>::iterator>);
	std::println("{}", name<std::span<int>::reverse_iterator>);
	std::println("{}", name<std::span<int>::const_iterator>);
	std::println("{}", name<std::span<int>::const_reverse_iterator>);
}

// https://en.cppreference.com/w/cpp/container
