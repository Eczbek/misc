#include <climits>

static const unsigned char BitReverseTable256[256] = 
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};


void printBinary(unsigned int x) {
	unsigned int y = 32;
	while (y--) {
		__builtin_printf("%d", (x >> y) & 1);
	}
	__builtin_printf("\n");
}


int main() {
	unsigned int v = 0b11110000110011001010101011111111; // reverse 32-bit value, 8 bits at time
	// unsigned int c; // c will get v reversed

	printBinary(v);

	unsigned int s = sizeof(v) * CHAR_BIT; // bit size; must be power of 2 
	unsigned int mask = (unsigned int)-1;         
	while ((s >>= 1) > 0) {
		mask ^= (mask << s);
		v = ((v >> s) & mask) | ((v << s) & ~mask);
	}

	printBinary(v);
}
