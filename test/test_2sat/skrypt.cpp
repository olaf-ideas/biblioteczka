#include <bits/stdc++.h>

using namespace std;

int main() {
	char c;
	while((c = getchar()) != EOF) {
		if(c == '\n')	cout << "\\n";
		else if(c == '\t')	cout << "\\t";
		else				cout << c;
	}
	cout << '\n';
}
