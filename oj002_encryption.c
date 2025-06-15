#include "https://raw.githubusercontent.com/camel-cdr/boline/main/boline/boline.c"

#define LPAREN (
#define RPAREN )
#define COMMA ,

#define ASCII_0(F) F(,,,,,,,,,,,,,,,)
#define ASCII_1(F) F(,,,,,,,,,,,,,,,)
#define ASCII_2(F) F(,!,,,,%,&,,LPAREN,RPAREN,*,+,COMMA,-,.,/)
#define ASCII_3(F) F(0,1,2,3,4,5,6,7,8,9,:,;,<,=,>,?)
#define ASCII_4(f) f(@,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)
#define ASCII_5(F) F(P,Q,R,S,T,U,V,W,X,Y,Z,[,,],^,_)
#define ASCII_6(F) F(,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o)
#define ASCII_7(F) F(p,q,r,s,t,u,v,w,x,y,z,{,|,},~,)
#define ASCII_8(F) F(,,,,,,,,,,,,,,,)
#define ASCII_9(F) F(,,,,,,,,,,,,,,,)
#define ASCII_a(F) F(,,,,,,,,,,,,,,,)
#define ASCII_b(F) F(,,,,,,,,,,,,,,,)
#define ASCII_c(F) F(,,,,,,,,,,,,,,,)
#define ASCII_d(F) F(,,,,,,,,,,,,,,,)
#define ASCII_e(F) F(,,,,,,,,,,,,,,,)
#define ASCII_f(F) F(,,,,,,,,,,,,,,,)

#define IS_ID_0(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_1(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_2(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_3(F) F(1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0)
#define IS_ID_4(F) F(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
#define IS_ID_5(F) F(1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1)
#define IS_ID_6(F) F(0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
#define IS_ID_7(F) F(1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0)
#define IS_ID_8(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_9(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_a(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_b(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_c(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_d(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_e(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#define IS_ID_f(F) F(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)

#define TO_ASCII(seq) TO_ASCIIr seq
#define TO_ASCIIr(a,b) ASCII_##b(B4_AT_##a)


#define IS_ID(seq) IS_IDr seq
#define IS_IDr(a,b) IS_ID_##b(B4_AT_##a)



#define B64_ROT32(x) (B_FX(B64_ROT32r,B_SCAN x))
#define B64_ROT32r(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) i,j,k,l,m,n,o,p,a,b,c,d,e,f,g,h

#define MSWS32(pair) MSWS32_1 pair
#define MSWS32_1(x,w) MSWS32_2(B64_MUL(x,x),B64_ADD(w,(9,a,2,e,c,1,a,d,e,c,e,4,d,a,5,b)))
#define MSWS32_2(x,w) (B64_ROT32(B64_ADD(x,w)),w) 

#define MSWS32_WARMUP(pair) MSWS32(MSWS32(MSWS32(MSWS32(MSWS32(MSWS32(pair))))))

#define MSWS32_OUT(pair) MSWS32_OUT_1 pair
#define MSWS32_OUT_1(x,w) B8_FROM_Bn(x)

// B8_XOR(B8(1,3),MSWS32_OUT(MSWS32(KEY))) -> (1,b)


#define SEQ_TERM(...) SEQ_TERM_(__VA_ARGS__))
#define SEQ_TERM_(...) __VA_ARGS__##_RM

#define EMPTY()
#define RPAREN_F() )

#define TO_GUIDE_A(...) (__VA_ARGS__) RPAREN_F EMPTY()()TO_GUIDE_B
#define TO_GUIDE_B(...) (__VA_ARGS__) RPAREN_F EMPTY()()TO_GUIDE_A
#define TO_GUIDE_A_RM
#define TO_GUIDE_B_RM
#define TO_GUIDE(seq) SEQ_TERM(TO_GUIDE_A seq)

// TO_GUIDE((1)(2)(3)(4)(5)) -> (1) )(2) )(3) )(4) )(5) ))



#define DECRYPT(seq) DECRYPT_SCAN(DECRYPTA LPAREN MSWS32_WARMUP((KEY,B64_0)),, TO_GUIDE(seq))

#define DECRYPT_PROBE(...) ,DECRYPT_1
#define DECRYPTA(s,l,v) B_CHECK(DECRYPT_PROBE v,DECRYPT_END)(DECRYPTB,MSWS32(s),l,v)
#define DECRYPTB(s,l,v) B_CHECK(DECRYPT_PROBE v,DECRYPT_END)(DECRYPTA,MSWS32(s),l,v)

#define DECRYPT_1(n,s,l,v) DECRYPT_2(n,s,l,B8_XOR(v,MSWS32_OUT(s)))
#define DECRYPT_2(n,s,l,v) B_CATe(DECRYPT_ID,IS_ID(v))(n,s,l,TO_ASCII(v))

#define DECRYPT_ID1(n,s,l,a) n(s,B_CATe(l,a),
#define DECRYPT_ID0(n,s,l,a) l a n(s,,

#define DECRYPT_END(...)
#define DECRYPT_SCAN(...) __VA_ARGS__



#ifdef USE_INVALID_KEY
# define KEY B64(d,e,a,d,b,e,e,a)
#else
# define KEY B64(d,e,a,d,b,e,e,f)
#endif

DECRYPT(
(0,f)(6,1)(d,b)(2,0)(e,7)(c,6)(6,a)(f,b)(0,b)(9,9)(e,0)(9,6)(8,3)(e,6)(e,9)(4,a)(b,2)(a,b)(1,2)(2,b)(6,e)(a,6)(a,e)(5,0)(c,d)(7,7)(b,7)(b,4)(5,2)(5,c)(3,2)(d,c)(0,d)(7,c)(9,9)(2,8)(7,b)(a,2)(5,e)(4,8)(4,e)(4,f)(c,8)(1,e)(8,e)(b,1)(3,0)(7,3)(b,a)(1,7)(6,c)(d,2)(f,5)(9,5)(6,f)(2,1)(d,d)(4,d)(3,7)(f,1)(d,b)(5,7)(4,a)(a,7)(6,4)(9,e)(7,1)(e,3)(7,6) 
)
