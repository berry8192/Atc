#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, s, su=0;
	string ans;
	vector<int> a, v, ad, ar;
	//ad i番の福袋をつかってる
	//ar 前のadのidx

	cin>> n >> s;
	a.resize(n);
	v.resize(n);
	ad.resize(s+1);
	ar.resize(s+1);

	rep(i, n){
		cin >> a[i]>> v[i];
		su+=min(a[i], v[i]);
		v[i]-=a[i];
		if(v[i]>=0) ans+='A';
		else ans+='B';
		v[i]=abs(v[i]);
		//v[i]==b[i]-a[i]
	}

	if(su>s){
		cout<< "Impossible" <<endl;
		return 0;
	}

	rep(i, n) {
		repr(j, s+1){
			if(j==0 || (j+v[i]<=s && ad[j]!=0)){
				//cout<< i SP << j <<endl;
				if(ad[j+v[i]]==0) ad[j+v[i]]=i+1;
				if(ar[j+v[i]]==0) ar[j+v[i]]=j;
			}
		}
	}
	// PV(ad);
	// PV(ar);
	// PV(v);

	int pos=s-su;
	while(pos){
		//cout<< pos SP << ad[pos]  SP << ar[pos] <<endl;
		if(ad[pos]==0){
			cout<< "Impossible" <<endl;
			return 0;
		}
		if(ans[ad[pos]-1]=='A') ans[ad[pos]-1]='B';
		else ans[ad[pos]-1]='A';
		pos=ar[pos];
		//cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}