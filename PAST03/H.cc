#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;


long long int lmax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	LLi n, l, t1, t2, t3, s1, s2=lmax, s3=lmax, ans, tmp;
	vector<LLi> v, dp;

	cin>> n >> l;
	v.resize(l+11);
	dp.resize(l+11);

	rep(i, n){
		cin >> tmp;
		v[tmp]=1;
	}
	cin>> t1 >> t2 >> t3;

	dp[0]=0;
	for(int i=1;i<l+11;i++){
		s1=dp[i-1]+t1;
		if(i>1) s2=dp[i-2]+t1+t2;
		if(i>3) s3=dp[i-4]+t1+t2*3;
		//cout<< s1 << " " << s2 << " " << s3 <<endl;
		if(v[i]) dp[i]=t3;
		dp[i]+=min(s1, min(s2, s3));
	}

	ans=min(dp[l], dp[l-1]+t1/2+t2/2);
	ans=min(ans, dp[l-2]+t1/2+3*t2/2);
	ans=min(ans, dp[l-3]+t1/2+5*t2/2);

	cout<< ans <<endl;
	//PV(dp);
 
	return 0;
}