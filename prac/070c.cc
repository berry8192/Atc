#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long int gcd(long long int a, long long int b){
	long long int r;
	if(a>b) swap(a, b);

	r=a%b;
	while(r!=0){
		a=b;
		b=r;
		r=a%b;
	}

	return b;
}

long long int lcm(long long int a, long long int b){
	long long int g;
	g=gcd(a, b);
	return a/g*b;

}

int main(){

	int n;
	long long int ans;
	vector<long long int> t;

	cin>> n;
	t.resize(n);

	for(int i=0;i<n;i++) cin>> t[i];

	sort(t.begin(), t.end());

	ans=t[0];
	for(int i=1;i<n;i++){
		//cout<< ans << endl;
		ans=lcm(ans, t[i]);
	}

	cout<< ans << endl;


}
