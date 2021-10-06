#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

int main(){

	int n;
	vector<int> a, dp;

	cin>> n;
	a.resize(n);
	dp.resize(n);

	for(int i=0;i<n;i++) cin>> a[i];

	dp[0]=0;
	dp[1]=abs(a[1]-a[0]);

	for(int i=2;i<n;i++){
		dp[i]=min(dp[i-2]+abs(a[i]-a[i-2]), dp[i-1]+abs(a[i]-a[i-1]));
	}

	cout<< dp[n-1] << endl;

}
