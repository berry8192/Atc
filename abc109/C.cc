#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
//
if(a<0) a=b;
if(b<0) b=a;
//
	if (b == 0) return a;
	return gcd(b, a%b);
}

int lcm(int a, int b) {
	return a*b/gcd(a, b);
}

int main(){

	int n, x, ans=-1;
	vector<int> v;

	cin>> n >> x;
	v.resize(n+1);
	v[n]=x;
	for(int i=0;i<n;i++) cin>> v[i];
	sort(v.begin(), v.end());

	for(int i=0;i<v.size()-1;i++){
		v[i]=v[i+1]-v[i];
		ans=gcd(v[i], ans);
	}

	cout<< ans << endl;


}
