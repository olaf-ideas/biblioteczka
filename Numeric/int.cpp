#include <bits/stdc++.h>

using namespace std;

struct Int {
    static const int base = 1e9;
    static const int base_digits = 9;

    vector<int> num; 
    int sign;

    int size() {
        if(num.empty())   return 0;
        int ans = ((int) num.size() - 1) * base_digits;
        for(int x = num.back(); x; x /= 10) ans++;
        return ans; 
    }

    void fix() {
        while(num.size() > 1 && num.back() == 0) num.pop_back();
        if(num.empty()) sign = 1; 
    }

    Int abs() const { Int res = *this; res.sign = 1; return res; }

    Int() : num(1, 0), sign(1) { }

    Int(const string &s) : sign(1) { read(s); }
    Int(long long v) { Int(to_string(v)); }

    Int& operator = (const Int &v) { sign = v.sign, num = v.num; return *this; }
    Int& operator = (const string &s) { *this = Int(s); return *this; }
    Int& operator = (long long v) { *this = Int(v); return *this; }

    Int operator + (const Int &v) const {
        if(sign != v.sign)  return *this - (-v);
        Int res = v;
        for(int i = 0, buf = 0; i < (int) max(num.size(), v.num.size()) || buf; i++) {
            if(i == (int) res.num.size())   res.num.push_back(0);
            res.num[i] += buf + (i < (int) num.size() ? num[i] : 0);
            buf = res.num[i] >= base;
            if(buf) res.num[i] -= base;
        }
        return res;
    }

    Int operator - (const Int &v) const {
        if(sign != v.sign)  return *this + (-v);
        if(abs() < v.abs()) return -(v - *this);
        Int res = *this;
        for(int i = 0, buf = 0; i < (int) v.num.size() || buf; i++) {
            res.num[i] -= buf + (i < (int) v.num.size() ? v.num[i] : 0);
            buf = res.num[i] < 0;
            if(buf) res.num[i] += base;
        }
        res.fix();
        return res;
    }

    Int operator * (int v) const { Int res = *this; return res *= v; }

    Int& operator *= (int v) {
        if(v < 0)   sign = -sign, v = -v;
        for(int i = 0, buf = 0; i < (int) num.size() || buf; i++) {
            if(i == (int) num.size())   num.push_back(0);
            long long cur = num[i] * (long long) v + buf;
            buf = (int) (cur / base);
            num[i] = (int) (cur % base);
        }
        fix();
        return *this;
    }

    Int& operator += (const Int& v) { *this = *this + v; return *this; }
    Int& operator -= (const Int& v) { *this = *this - v; return *this; }

    Int operator -() const { Int res = *this; res.sign = -sign; return res; }

    void read(const string &s) {
        sign = 1;
        num.clear();
        int pos = 0;
        while(pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if(s[pos] == '-')   sign = -sign;
            pos++;
        }
        for(int i = (int) s.size() - 1; i >= pos; i -= base_digits) {
            num.push_back(0);
            for(int j = max(pos, i - base_digits + 1); j <= i; j++)
                num.back() = num.back() * 10 + s[j] - 48;
        }
        fix();
    }

    bool operator < (const Int &v) const {
        if(sign != v.sign)  return sign < v.sign;
        if(num.size() != v.num.size())  return num.size() * sign < v.num.size() * v.sign;
        for(int i = (int) num.size() - 1; i >= 0; i--) if(num[i] != v.num[i])
            return num[i] * sign < v.num[i] * v.sign;
        return false;
    }

    bool operator == (const Int &v) const { return sign == v.sign && num == v.num; }
    bool operator != (const Int &v) const { return !(*this == v); } 
    bool operator <= (const Int &v) const { return *this == v || *this < v; }
    bool operator >  (const Int &v) const { return !(*this <= v); }
    bool operator >= (const Int &v) const { return *this > v || *this == v; }

    friend istream& operator >> (istream &is, Int &v) { string s; is >> s; v.read(s); return is; }

    friend ostream& operator << (ostream &os, const Int &v) {
        if(v.sign == -1)    os << '-';
        os << (v.num.empty() ? 0 : v.num.back());
        for(int i = (int) v.num.size() - 2; i >= 0; i--)    os << setw(base_digits) << setfill('0') << v.num[i];
        return os;
    }
};

int main() {
    Int a; int b;
    cin >> a >> b;
    cout << (a * b) << '\n';
}
