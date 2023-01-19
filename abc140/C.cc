#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, ans;
	vector<int> v;

	cin>> n;
	v.resize(n);
	for(int i=0;i<n-1;i++) cin>> v[i];

	ans=v[n-2];
	for(int i=n-1;0<i;i--){
		ans+=min(v[i], v[i-1]);
	}
	ans+=v[0];

	cout<< ans << endl;

}