#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int main(){

	long long int n, a, b, c, d, e, mi;
	long long int dure=5;

	cin>> n >> a >> b >> c >> d >> e;

	mi=min(a, b);
	mi=min(c, mi);
	mi=min(d, mi);
	mi=min(e, mi);

	dure+=(n-1)/mi;

	cout<< dure << endl;

}
