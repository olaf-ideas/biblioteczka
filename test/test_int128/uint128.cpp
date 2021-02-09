#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

struct uint128 {
    ull one, two;

};

ostream& operator << (ostream &os, const uint128 &v) {
    return os << v.one << " * 2**64 + " << v.two;
}

uint128 operator + (const uint128 &a, const uint128 &b){ 
    return uint128{a.one + b.one + (a.two + b.two < a.two),
                   a.two + b.two};
}

uint128 mul(ull one, ull two) {
    ull a = one >> 32ull;
    ull b = one - (a << 32ull);
    ull c = two >> 32ull;
    ull d = two - (c << 32ull);

    uint128 res{a * c, b * d};

    for(int rep : {0, 1}) {
        ull x = (rep ? a * d : b * c);
        res.one += x >> 32ull;
        x -= (x >> 32ull) << 32ull;
        res = res + uint128{0, x << 32ull};
    }

    return res;
}

ull my_randULL() {
	int type = rand() % 3;
	if(type == 0) return numeric_limits<ull>::max() - rand() % 30;
	if(type == 1) return rand() % 30;
	assert(type == 2);
	ull x = 0;
	for(int i = 0; i < 64; ++i)
		x = 2 * x + rand() % 2;
	return x;
}

void write(ull a, ull b) {
	cout << "assert " << a << " * " << b << " == ";
	uint128 p = mul(a, b);
	cout << p.one << " * 2**64 + " << p.two << "\n";
}

int main() {
	srand(5023);
	string ff = "py_random_file_asdf";
	assert(freopen(ff.c_str(), "w", stdout));
	for(int i = 0; i < 50000; ++i) {
		write(my_randULL(), my_randULL());
	}
	fflush(stdout);
	system(("python3 " + ff).c_str());
}
