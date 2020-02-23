#include <bits/stdc++.h>
using namespace std;
const int MINN = 100005, MAXN = 1000005;

int rand(int a, int b){return a+rand()%(b-a+1);}

int main(int argc, char *argv[]){
    srand(atoi(argv[1]));
    int n = rand(MINN,MAXN);
    
    printf("%d\n", n);
    for(int i = 0; i < n; i++){
        char c = rand('a', 'z');
        printf("%c", c);
    }
    printf("\n");
}