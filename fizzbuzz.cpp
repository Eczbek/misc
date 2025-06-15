#include <bits/stdc++.h>
using namespace std::literals;

int main() {
	for (int i = 1; i <= 20; ++i) {
	    std::puts((i % 15 ? i % 5 ? i % 3 ? std::to_string(i) : "fizz"s : "buzz"s : "fizzbuzz"s).c_str());
	}
}
