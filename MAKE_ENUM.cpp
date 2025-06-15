// #include <xieite/pp/at.hpp>
#include <xieite/pp/each.hpp>
#include <xieite/pp/eat.hpp>
#include <xieite/pp/paren.hpp>
#include <xieite/pp/scan.hpp>
#include <xieite/pp/str.hpp>
#include <xieite/pp/unwrap.hpp>
#include <xieite/pp/wrap.hpp>

#define XIEITE_AT(n) XIEITE_PCAT(XIEITE_AT_, n)
#define XIEITE_AT_0(x, ...) x
#define XIEITE_AT_1(_, ...) XIEITE_AT_0(__VA_ARGS__)
#define XIEITE_AT_2(_, ...) XIEITE_AT_1(__VA_ARGS__)
#define XIEITE_AT_3(_, ...) XIEITE_AT_2(__VA_ARGS__)
#define XIEITE_AT_4(_, ...) XIEITE_AT_3(__VA_ARGS__)
#define XIEITE_AT_5(_, ...) XIEITE_AT_4(__VA_ARGS__)
#define XIEITE_AT_6(_, ...) XIEITE_AT_5(__VA_ARGS__)
#define XIEITE_AT_7(_, ...) XIEITE_AT_6(__VA_ARGS__)

#define STR_AT(n) XIEITE_PCAT(STR_AT_, n)
#define STR_AT_0(x, ...) #x
#define STR_AT_1(_, ...) STR_AT_0(__VA_ARGS__)
#define STR_AT_2(_, ...) STR_AT_1(__VA_ARGS__)
#define STR_AT_3(_, ...) STR_AT_2(__VA_ARGS__)
#define STR_AT_4(_, ...) STR_AT_3(__VA_ARGS__)
#define STR_AT_5(_, ...) STR_AT_4(__VA_ARGS__)
#define STR_AT_6(_, ...) STR_AT_5(__VA_ARGS__)
#define STR_AT_7(_, ...) STR_AT_6(__VA_ARGS__)

// #include <string_view>
// #include <print>

// #define _0_ ), (DETAIL_XIEITE_AT_0,
// #define _1_ ), (DETAIL_XIEITE_AT_1,
// #define _2_ ), (DETAIL_XIEITE_AT_2,
// #define _0_STR ), (STR_0,
// #define _1_STR ), (STR_1,
// #define _2_STR ), (STR_2,

#define XIEITE_0_(m) ), (m(0),
#define XIEITE_1_(m) ), (m(1),
#define XIEITE_2_(m) ), (m(2),
#define XIEITE_3_(m) ), (m(3),
#define XIEITE_4_(m) ), (m(4),
#define XIEITE_5_(m) ), (m(5),
#define XIEITE_6_(m) ), (m(6),
#define XIEITE_7_(m) ), (m(7),
#define XIEITE_0 XIEITE_0_(XIEITE_AT)
#define XIEITE_1 XIEITE_1_(XIEITE_AT)
#define XIEITE_2 XIEITE_2_(XIEITE_AT)
#define XIEITE_3 XIEITE_3_(XIEITE_AT)
#define XIEITE_4 XIEITE_4_(XIEITE_AT)
#define XIEITE_5 XIEITE_5_(XIEITE_AT)
#define XIEITE_6 XIEITE_6_(XIEITE_AT)
#define XIEITE_7 XIEITE_7_(XIEITE_AT)
#define XIEITE_$(...) )(XIEITE_LPAREN, __VA_ARGS__)(XIEITE_RPAREN,

// #define STR_0(x, ...) XIEITE_STR(x)
// #define STR_1(_, ...) STR_0(__VA_ARGS__)
// #define STR_2(_, ...) STR_1(__VA_ARGS__)

//#define DETAIL_XIEITE_GEN_EACH_999(args, ...) __VA_OPT__(DETAIL_XIEITE_GEN_EACH_1(args, __VA_ARGS__))


//#define LOOP2(x, ...) __VA_OPT__(DETAIL_XIEITE_GEN_EACH_0(x, __VA_ARGS__))


//#define BAZ(...) DETAIL_XIEITE_GEN_INSERT(__VA_ARGS__)


#define XIEITE_GEN(pattern, ...) __VA_OPT__(XIEITE_EVAL(DETAIL_XIEITE_GEN((DETAIL_XIEITE_GEN_START pattern), __VA_ARGS__)))
#define DETAIL_XIEITE_GEN(entries, ...) DETAIL_XIEITE_GEN_EACH_0(entries, __VA_ARGS__)
#define DETAIL_XIEITE_GEN_START(...) (XIEITE_EAT, __VA_ARGS__)
#define DETAIL_XIEITE_GEN_EACH_0(entries, args, ...) DETAIL_XIEITE_GEN_EACH_1 XIEITE_WRAP(args, XIEITE_UNWRAP(entries)) __VA_OPT__(DETAIL_XIEITE_GEN_NEXT_0 XIEITE_SCAN(()) (entries, __VA_ARGS__))
#define DETAIL_XIEITE_GEN_NEXT_0() DETAIL_XIEITE_GEN_EACH_0
#define DETAIL_XIEITE_GEN_EACH_1(args, entry, ...) DETAIL_XIEITE_GEN_INSERT XIEITE_WRAP(args, XIEITE_UNWRAP(entry)) __VA_OPT__(DETAIL_XIEITE_GEN_NEXT_1 XIEITE_SCAN(()) (args, __VA_ARGS__))
#define DETAIL_XIEITE_GEN_NEXT_1() DETAIL_XIEITE_GEN_EACH_1
#define DETAIL_XIEITE_GEN_INSERT(args, m, ...) m args __VA_ARGS__


#define MAKE_ENUM(E, ...) \
	enum E { \
		XIEITE_GEN((XIEITE_0 = XIEITE_1,), __VA_ARGS__) \
	}; \
	std::string_view E_str(E e) { \
		switch (e) { \
			XIEITE_GEN((case E::XIEITE_0: return XIEITE_STR_ XIEITE_$(XIEITE_0);), __VA_ARGS__) \
		} \
	}
	
MAKE_ENUM(E, (a, 1), (b, 2), (c, 3))

int main() {
	std::println("{}", E_str(E::b));
}

// basically HolyBlackCat's macros but worse
