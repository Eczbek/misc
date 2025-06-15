#include <cstdio>

#define expand_empty_if_
#define expand_empty_if_1
#define expand_empty_if_true
#define expand_args(...)  __VA_ARGS__
#define eval_macro(x)     eval_macro2(expand_empty_if_##x)
#define eval_macro2(...)  macro_arg0(__VA_OPT__(,)1,)
#define expand0_if(y,...) __VA_OPT__(expand_args y)
#define macro_arg0(y,...) y

#define HAVE_MACRO(x)   (eval_macro(x)+0)
#define IF_MACRO(x,...) expand0_if((__VA_ARGS__),eval_macro(x))

template<int> void perhaps_do_thing() { std::puts("did thing"); }
template<> void perhaps_do_thing<0>() {}

int main() {
    perhaps_do_thing<HAVE_MACRO(CAN_DO_THING)>();

#if HAVE_MACRO(CAN_DO_THING)
	std::puts("eee");
#endif
}
