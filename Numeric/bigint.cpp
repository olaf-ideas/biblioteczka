#include <bits/stdc++.h>

using namespace std;

typedef long long int LL;
typedef long double LD;

struct BigInt {
	const int base = 1e9;

	vector<int> num;
	
	BigInt(LL x=0) { *this = BigInt(to_string(x)); }
	
	BigInt(const string &s) {
		for(int i = (int)s.size(); i > 0; i -= 9) {
			if(i < 9)	num.push_back(atoi(s.substr(0, i).c_str()));
			else 		num.push_back(atoi(s.substr(i - 9, 9).c_str()));
		}
		fix();
	}

	void fix() { while(num.size() > 1 && num.back() == 0) num.pop_back(); }
	
	friend ostream& operator << (ostream& o, const BigInt &bigint) {
		o << bigint.num.back();
		for(int i = (int)bigint.num.size() - 2; i >= 0; i--)
			o << setw(9) << setfill('0') << bigint.num[i];
		return o;
	}
	
	friend istream& operator >> (istream& i, BigInt &bigint) {
		string s; i >> s;
		bigint = BigInt(s);
		return i;
	}
	
	BigInt& operator = (const BigInt &other) { num = other.num; return *this; }
	BigInt& operator = (LL val) { *this = BigInt(val); return *this; }
	BigInt& operator = (const string &s) { *this = BigInt(s); return *this; }
	
	BigInt& operator += (const BigInt &other) {
		for(int i = 0, buf = 0; i < (int)max(num.size(), other.num.size()) || buf; i++) {
			if(i == (int)num.size())	num.push_back(0);
			num[i] += buf + (i < (int)other.num.size() ? other.num[i] : 0);
			buf = num[i] >= base;
			if(buf)	num[i] -= base;
		}
		return *this;
	}
	
	BigInt operator + (const BigInt &other) const { BigInt res = *this; res += other; return res; }
	BigInt operator + (const string &other) const { BigInt res = *this; res += BigInt(other); return res; }
	BigInt operator + (const LL &other) const { BigInt res = *this; res += BigInt(other); return res; }
	
	BigInt& operator -= (const BigInt &other) {
		assert(*this >= other);
		for(int i = 0, buf = 0; i < (int)other.num.size() || buf; i++) {
			num[i] -= buf + (i < (int)other.num.size() ? other.num[i] : 0);
			buf = num[i] < 0;
			if(buf)	num[i] += base;
		}
		fix();
		return *this;
	}
	
	BigInt operator - (const BigInt &other) const { BigInt res = *this; res -= other; return res; }
	BigInt operator - (const string &other) const { BigInt res = *this; res -= BigInt(other); return res; }
	BigInt operator - (const LL &other) const { BigInt res = *this; res -= BigInt(other); return res; }

	 //O(n * 2)
	BigInt operator * (const BigInt &other) const {
		BigInt res;
		res.num.resize(num.size() + other.num.size(), 0);
		for(int i = 0; i < (int)num.size(); i++) {
			for(int j = 0, buf = 0; j < (int)other.num.size() || buf; j++) {
				LL sum = res.num[i + j] + num[i] * 1LL * (j < (int)other.num.size() ? other.num[j] : 0) + buf;
				res.num[i + j] = int(sum % base);
				buf = int(sum / base);
			}
		}
		res.fix();
		return res;
	}
		
	BigInt& operator *= (const BigInt &other) { *this = *this * other; return *this; }
	BigInt& operator *= (const string &other) { *this = *this * BigInt(other); return *this; }
	BigInt& operator *= (const LL &other) { *this = *this * BigInt(other); return *this; }
		
	bool operator < (const BigInt &other) const {
		if(num.size() != other.num.size())	return num.size() < other.num.size();
		for(int i = (int)num.size() - 1; i >= 0; i--) {
			if(num[i] != other.num[i]) {
				return num[i] < other.num[i];
			}
		}
		return false;
	}
	
	bool operator == (const BigInt &other) const { return num == other.num; }
	bool operator != (const BigInt &other) const { return !(*this == other); }
	bool operator >= (const BigInt &other) const { return !(*this < other); }
	bool operator <= (const BigInt &other) const { return *this < other || *this == other; }
	bool operator >  (const BigInt &other) const { return !(*this <= other); }
};

template <class T>
struct Matrix {
	vector<vector<T>> mat;
	int n, m;
	Matrix(int _n, int _m) : mat(_n, vector<T>(_m, T())), n(_n), m(_m) { }
	
	Matrix operator * (const Matrix &other) const {
		Matrix res(n, other.m);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < other.m; j++) {
				for(int k = 0; k < n; k++) {
					res.mat[i][j] = res.mat[i][j] + mat[i][k] * other.mat[k][j];
				}
			}
		}
		return res;
	}
	
	struct Row {
		vector<T> &row;
		Row(vector<T> &_row) : row(_row) { }
		T& operator [] (int j) { return row[j]; }
	};
	
	Row operator [] (int i) { return Row(mat[i]); }
	
	friend Matrix pot(Matrix mx, LL k) {
		Matrix res(mx.n, mx.m);
		for(int i = 0; i < mx.n; i++)	res.mat[i][i] = 1;
		for(; k; k >>= 1, mx = mx * mx)
			if(k & 1)	res = res * mx;
		return res;
	}
	
	friend ostream& operator << (ostream& o, const Matrix &mx) {
		o << '[';
		for(int i = 0; i < mx.n - 1; i++) {
			o << '[';
			for(int j = 0; j < mx.m - 1; j++) {
				o << mx.mat[i][j] << ", ";
			}
			o << mx.mat[i].back() << "],\n";
		}
		o << '[';
		for(int j = 0; j < mx.m - 1; j++)
			o << mx.mat.back()[j] << ", ";
		return o << mx.mat.back().back() << "]]";
	}
};