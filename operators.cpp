template<auto f>struct A{template<class T>struct B{T x;

                        constexpr   T operator&&(T y    ){return static_cast<T>(f(  x,y));}
                        constexpr   T operator||(T y    ){return static_cast<T>(f(  x,y));}
                        constexpr   T operator& (T y    ){return static_cast<T>(f(  x,y));}
                        constexpr   T operator| (T y    ){return static_cast<T>(f(  x,y));}
                        constexpr   T operator^ (T y    ){return static_cast<T>(f(  x,y));}
                 friend constexpr   T operator&=(T y,B b){return static_cast<T>(f(b.x,y));}
                 friend constexpr   T operator|=(T y,B b){return static_cast<T>(f(b.x,y));}
                 friend constexpr   T operator^=(T y,B b){return static_cast<T>(f(b.x,y));}};
template<class T>friend constexpr B<T>operator&&(T x,A  ){return{                   x   };}
template<class T>friend constexpr B<T>operator||(T x,A  ){return{                   x   };}
template<class T>friend constexpr B<T>operator& (T x,A  ){return{                   x   };}
template<class T>friend constexpr B<T>operator| (T x,A  ){return{                   x   };}
template<class T>friend constexpr B<T>operator^ (T x,A  ){return{                   x   };}
template<class T>       constexpr B<T>operator&=(T x    ){return{                   x   };}
template<class T>       constexpr B<T>operator|=(T x    ){return{                   x   };}
template<class T>       constexpr B<T>operator^=(T x    ){return{                   x   };}};

#define    nand    &&A<[](auto x,auto y){return     !x||!y ;}>()&&
#define    nor     ||A<[](auto x,auto y){return     !x&&!y ;}>()||
#define    xnor    ^ A<[](auto x,auto y){return      x== y ;}>()^
#define    nand_eq &=A<[](auto&x,auto y){return x=  !x||!y ;}>()&=
#define    nor_eq  |=A<[](auto&x,auto y){return x=  !x&&!y ;}>()|=
#define    xnor_eq ^=A<[](auto&x,auto y){return x=   x== y ;}>()^=
#define bitnand    & A<[](auto x,auto y){return     !x| !y ;}>()&
#define bitnor     | A<[](auto x,auto y){return     !x& !y ;}>()|
#define bitxor     ^ A<[](auto x,auto y){return      x^  y ;}>()^
#define bitxnor    ^ A<[](auto x,auto y){return   ~(~x^ ~y);}>()^
#define bitand_eq  &=A<[](auto&x,auto y){return x=   x&  y ;}>()&=
#define bitnand_eq &=A<[](auto&x,auto y){return x=  !x| !y ;}>()&=
#define bitor_eq   |=A<[](auto&x,auto y){return x=   x|  y ;}>()|=
#define bitnor_eq  |=A<[](auto&x,auto y){return x=  !x& !y ;}>()|=
#define bitxor_eq  ^=A<[](auto&x,auto y){return x=   x^  y ;}>()^=
#define bitxnor_eq ^=A<[](auto&x,auto y){return x=~(~x^ ~y);}>()^=


#include <print>
#define FOO(a,b,op,str) std::println(#a" " str" "#b" = {:b}",static_cast<unsigned>(a op b));
#define BAR(a0,a1,op,str)\
	FOO(a0,0,op,str)\
	FOO(a1,0,op,str)\
	FOO(a0,1,op,str)\
	FOO(a1,1,op,str)\
	std::println();
#define BAZ(op) BAR(0,1,op,#op)
#define QUX(op) BAR((x=0),(x=1),op,#op)
int main(){int x;
	BAZ(and)
	BAZ(nand)
	BAZ(or)
	BAZ(nor)
	BAZ(xor)
	BAZ(xnor)
	QUX(and_eq)
	QUX(nand_eq)
	QUX(or_eq)
	QUX(nor_eq)
	QUX(xor_eq)
	QUX(xnor_eq)
	BAZ(bitand)
	BAZ(bitnand)
	BAZ(bitor)
	BAZ(bitnor)
	BAZ(bitxor)
	BAZ(bitxnor)
	QUX(bitand_eq)
	QUX(bitnand_eq)
	QUX(bitor_eq)
	QUX(bitnor_eq)
	QUX(bitxor_eq)
	QUX(bitxnor_eq)
}
