void xorswap(int& __restrict__ a, int& __restrict__ b) { a ^= b; b ^= a; a ^= b; }
void addswap(int& __restrict__ a, int& __restrict__ b) { a += b; b = a - b; a -= b; }
void mulswap(int& __restrict__ a, int& __restrict__ b) { a *= b; b = a / b; a /= b; }
void whyswap(int& __restrict__ a, int& __restrict__ b) { a = a + b - (b = a); }
