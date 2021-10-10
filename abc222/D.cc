#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

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

	int n;
	LLi cnt, ans=0;
	vector<LLi> a, b, v, rv;

	cin>> n;
	a.resize(31);
	b.resize(31);
	v.resize(31);
	rv.resize(31);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	for(int i=0;i<=30;i++){
		if(a[0]<=i && i<=b[0]){
			v[i]=1;
		}else{
			v[i]=0;
		}
	}
	for(int i=1;i<=30;i++) rv[i]=(rv[i-1]+v[i])%mod;
	PVL(rv);

	for(int i=1;i<n;i++){
		cnt=0;
		for(LLi j=0;j<=30;j++){
			if(a[i]<=j && j<=b[i]){
				//max(0LL, min(b[i-1]-a[i-1], j-a[i-1]));
				v[j]=rv[j];
			}else{
				v[j]=0;
			}
		}
	for(int j=1;j<=30;j++) rv[j]=(rv[j-1]+v[j])%mod;
	PVL(rv);
	}

	for(int i=0;i<=30;i++){
		cout<< v[i] <<endl;
		if(a[n-1]<=i && i<=b[n-1]){
			ans+=v[i];
			ans=ans%mod;
		}
	}

	cout<< ans <<endl;
 
	return 0;
}