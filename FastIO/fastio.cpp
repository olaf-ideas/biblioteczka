#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

void scan(ll *x){
    register char c = 0, sign = 1;
    while(c < 33)   c = getchar();
    if(c == 45)    sign = -1, c = getchar();
    (*x) = 0;
    while(c > 32 && c != 46)   (*x)=(*x)*10+c-48, c = getchar();
    (*x) *= sign;
}

void scan(string *x){
    register char c = 0;
    while(c < 33)   c = getchar();
    while(c > 32)   x->push_back(c), c = getchar();
}

void scan(char *x){
    (*x) = getchar();
}

void endl(){putchar('\n');}

void print(ll x, bool end){
    if(x == 0){
        putchar('0');
        return;
    }else if(x < 0)  putchar('-'), x = -x;
    char tab[19];
    int p = 0;
    while(x)    tab[p++] = (x%10)+48, x /= 10;
    while(p--)  putchar(tab[p]);
    if(end) endl();
}

void print(string x, bool end=false){
    for(char& c : x)    putchar(c);
    if(end) endl();
}

void print(ld x, const int eps, bool end=false){
    if(x < 0)   putchar('-'), x=-x;
    ll k = (x*pow(10,eps));
    char arr[60];
    int p = 0;
    for(char i = 0; i < eps; i++)   arr[p++] = (k%10)+48, k /= 10;
    arr[p++] = '.';
    do{arr[p++] = (k%10)+48, k /= 10;}while(k);
    while(p--)  putchar(arr[p]);
    if(end) endl();
}


void print(char x, bool end=false){
    putchar(x);
    if(end) endl();
}

int main(){
    ll x;
    string s;
    char c;
    
    scan(&x);
    scan(&s);
    scan(&c);

    print(x);  
    print(s);
    print(c);

    //demo
    ld y = 54321.12345;
    print(y);
}