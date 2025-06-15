#define EVAL1(...)__VA_ARGS__
#define EVAL2(...)EVAL1(EVAL1(EVAL1(EVAL1(__VA_ARGS__))))
#define EVAL3(...)EVAL2(EVAL2(EVAL2(EVAL2(__VA_ARGS__))))
#define EVAL4(...)EVAL3(EVAL3(EVAL3(EVAL3(__VA_ARGS__))))
#define EVAL(...)EVAL4(EVAL4(EVAL4(EVAL4(__VA_ARGS__))))
#define NONE
#define TRAILING_COMMA(...)__VA_OPT__(EVAL(TRAILING_COMMAA(__VA_ARGS__)))
#define TRAILING_COMMAA(X,...)TRAILING_COMMAAA##__VA_OPT__(A)(X,__VA_ARGS__)
#define TRAILING_COMMAAA(X,...)X
#define TRAILING_COMMAAAA(X,...)X,TRAILING_COMMAB NONE(__VA_ARGS__)
#define TRAILING_COMMAB(X,...)TRAILING_COMMABB##__VA_OPT__(B)(X,__VA_ARGS__)
#define TRAILING_COMMABB(X,...)X
#define TRAILING_COMMABBB(X,...)X,TRAILING_COMMAA NONE(__VA_ARGS__)
struct S{
    int a,b;
    S():TRAILING_COMMA(
        a(),
        b(),
    ){}
};
int main(){}
