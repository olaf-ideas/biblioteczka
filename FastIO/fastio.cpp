#include<bits/stdc++.h>
using namespace std;
using ll = long long;

void scan(ll *x){
	register int c = 0, s = 1;
	while(c < 33)		c = getchar();
	if(c == 45)			s = -1, c = getchar();
	for(*x = 0; c > 32 && c != 46; c = getchar())	*x = *x*10+c-48;
	(*x) *= s;
}

void scan(string *x){
	register int c = 0;
	while(c < 33)	c = getchar();
	while(c > 32)	x->push_back(char(c)), c = getchar();
}

void print(ll x){
	if(x == 0){
		putchar('0');
		return;
	}else if(x < 0)	putchar('-'), x = -x;
	int tab[19], p = 0;
	while(x)		tab[p++] = int(x%10)+48, x /= 10;
	while(p--)	putchar(tab[p]);
}

void print(string x){
	for(char& c : x)	putchar(c);
}
void print(char x){
	putchar(x);
}

int main(){

}
