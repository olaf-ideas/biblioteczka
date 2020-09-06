#include <bits/stdc++.h>

using namespace std;

struct Bitset {
	vector<uint32_t> bit;
	int n;
	Bitset(uint32_t _n=0) : bit((_n >> 5) + 1), n(_n) { }
	bool operator == (const Bitset &other) { return bit == other.bit; }
	bool operator != (const Bitset &other) { return bit != other.bit; }
	
	bool test(uint32_t x) { return bit[x >> 5] & (1 << (x & 31)); }
	uint32_t get_block_id(uint32_t x) { return bit[x >> 5]; }
    	
	int count() { int res = 0; for(uint32_t i : bit) res += __builtin_popcount(i); return res;}
	int size() { return n; }
	
	Bitset& operator = (const Bitset &other) { n = other.n, bit = other.bit; return *this; }
	
	void set(uint32_t x) { bit[x >> 5] |= 1 << (x & 31); }
	void flip(uint32_t x) { bit[x >> 5] ^= 1 << (x & 31); }
	void reset(uint32_t x){ bit[x >> 5] &= ~(1 << (x & 31)); }

	void assign(size_t nn, uint32_t v = 0) { bit.assign((nn >> 5) + 1, v); }
	void resize(size_t nn, uint32_t v = 0) { bit.resize((nn >> 5) + 1, v); }
};
