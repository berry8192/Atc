#include <bits/stdc++.h>

using namespace std;

int main(){

	int x, a, b;

	cin>> x;

	a = x / 500;
	x = x % 500;
	b = x / 5;

	cout << a * 1000 + b * 5 << endl;

	return 0;
}
