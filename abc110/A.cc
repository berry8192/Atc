#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int a, b, c;

	cin>> a >> b >> c;

	a=max(a, max(b, c))*10-max(a, max(b, c))+a+b+c;

	cout<< a << endl;

}
