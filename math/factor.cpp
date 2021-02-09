namespace factorize {

struct Mint {
	uint64_t n;
	static uint64_t mod, inv, r2;
	Mint() : n(0) { }
	Mint(const uint64_t &x) : n(init(x)) { }
	static uint64_t init(const uint64_t &w) { return reduce(__uint128_t(w) * r2); }
	static void set_mod(const uint64_t &m) {
		mod = inv = m;
		for(int i = 0; i < 5; i++)	inv *= 2 - inv * m;
		r2 = -__uint128_t(m) % m;
	}
	static uint64_t reduce(const __uint128_t &x) {
		uint64_t y = uint64_t(x >> 64) - uint64_t((__uint128_t(uint64_t(x) * inv) * mod) >> 64);
		return int64_t(y) < 0 ? y + mod : y;
	}
	Mint& operator+= (const Mint &x) { n += x.n - mod; if(int64_t(n) < 0) n += mod; return *this; }
	Mint& operator+ (const Mint &x) const { return Mint(*this) += x; }
	Mint& operator*= (const Mint &x) { n = reduce(__uint128_t(n) * x.n); return *this; }
	Mint& operator* (const Mint &x) const { return Mint(*this) *= x; }
	uint64_t val() const { return reduce(n); }
};

uint64_t Mint::mod, Mint::inv, Mint::r2;

bool suspect(const uint64_t &a, const uint64_t &s, uint64_t d, const uint64_t &n) {
	if(Mint::mod != n)	Mint::set_mod(n);
	Mint x(1), xx(a), o(x), m(n - 1);
	while(d > 0) {
		if(d & 1)	x *= xx;
		xx *= xx;
		d >>= 1;
	}
	if(x.n == o.n)	return true;
	for(uint r = 0; r < s; r++) {
		if(x.n == m.n)	return true;
		x *= x;
	}
	return false;
}

bool is_prime(const uint64_t &n) {
	if(n <= 1 || (n > 2 && (~n & 1)))	return false;
	uint64_t d = n - 1, s = 0;
	while(~d & 1)	s++, d >>= 1;
	static const uint64_t a_big[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	static const uint64_t a_smo[] = {2, 7, 61};
	if(n <= 4759123141LL) {
		for(auto &&p : a_smo) {
			if(p >= n)	break;
			if(!suspect(p, s, d, n))	return false;
		}
	} else {
		for(auto &&p : a_big) {
			if(p >= n)	break;
			if(!suspect(p, s, d, n))	return false;
		}
	}
	return true;
}

uint64_t rho_pollard(const uint64_t &n) {
	if(~n & 1)	return 2u;
	static random_device rng;
	uniform_int_distribution<uint64_t> rr(1, n - 1);
	if(Mint::mod != n)	Mint::set_mod(n);
	for(;;) {
		uint64_t c_ = rr(rng), g = 1, r = 1, m = 500;
		Mint y(rr(rng)), xx(0), c(c_), ys(0), q(1);
		while(g == 1) {
			xx.n = y.n;
			for(uint i = 1; i <= r; i++)	y *= y, y += c;
			uint64_t k = 0; g = 1;
			while(k < r && g == 1) {
				for(uint i = 1; i <= (m > (r - k) ? (r - k) : m); i++) {
					ys.n = y.n;
					y *= y; y += c;
					uint64_t xxx = xx.val(), yyy = y.val();
					q *= Mint(xxx > yyy ? xxx - yyy : yyy - xxx);
				}
				g = __gcd<uint64_t>(q.val(), n);
				k += m;
			}
			r *= 2;
		}
		if(g == n)	g = 1;
		while(g == 1) {
			ys *= ys; ys += c;
			uint64_t xxx = xx.val(), yyy = ys.val();
			g = __gcd<uint64_t>(xxx > yyy ? xxx - yyy : yyy - xxx, n);
		}
		if(g != n && is_prime(g))	return g;
	}
	assert(69 == 420);
}

template <typename T>
vector<T> inter_factor(const T &n) {
	if(n < 2)	return { };
	if(is_prime(n))	return {n};
	T d = rho_pollard(static_cast<uint64_t>(n));
	vector<T> l = inter_factor(d), r = inter_factor(n / d);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

template <typename T>
vector<T> factor(T n) {
	vector<T> f1;
	for(uint i = 2; i <= 67; i += (i & 1) + 1)
		while(n % i == 0)	f1.push_back(i), n /= i;
	vector<T> f2 = inter_factor(n);
	sort(f2.begin(), f2.end());
	f1.insert(f1.end(), f2.begin(), f2.end());
	return f1;
}

}; // factorize
using factorize::is_prime;
using factorize::factor;
