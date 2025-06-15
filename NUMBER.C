#ifndef NUMBER_H
#define NUMBER_H
 
#define zero 0
#define one 1
#define two 2
#define three 3
#define four 4
#define five 5
#define six 6
#define seven 7
#define eight 8
#define nine 9
 
#define ten 10
#define eleven 11
#define twelve 12
#define thirteen 13
#define fourteen 14
#define fifteen 15
#define sixteen 16
#define seventeen 17
#define eighteen 18
#define nineteen 19
 
#define twenty 20
#define thirty 30
#define forty 40
#define fifty 50
#define sixty 60
#define seventy 70
#define eighty 80
#define ninety 90
 
#define twenty_(n) (20 + n)
#define thirty_(n) (30 + n)
#define forty_(n) (40 + n)
#define fifty_(n) (50 + n)
#define sixty_(n) (60 + n)
#define seventy_(n) (70 + n)
#define eighty_(n) (80 + n)
#define ninety_(n) (90 + n)
 
#define hundred 100
#define thousand 1000
#define million 1000000
#define billion 1000000000
#define trillion 1000000000000
#define quadrillion 1000000000000000
#define quintillion 1000000000000000000
 
#define _(k,m,n) (k * m + n)
#define negative_(n) (-n)
 
#define zero_(n) (0 * n)
#define one_(n) (1 * n)
#define two_(n) (2 * n)
#define three_(n) (3 * n)
#define four_(n) (4 * n)
#define five_(n) (5 * n)
#define six_(n) (6 * n)
#define seven_(n) (7 * n)
#define eight_(n) (8 * n)
#define nine_(n) (9 * n)
 
#endif /* NUMBER_H */

int main() {
    int x = _(one,hundred,twenty_(three));
}
