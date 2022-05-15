#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
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

	int n, x, ans;
	vector<int> v;

	cin>> n >> x;
	v.resize(n);

	// if(n==3 && x==1){
	// 	cout<< "1 2 3" <<endl;
	// 	return 0;
	// }

	if(n%2){
		if(x==n/2+1) ans=n-1;
		else ans=n-2;
	}else{
		if(x==n/2 || x==n/2+1) ans=n-1;
		else ans=n-2;
	}

	v[0]=x;
	if(ans==n-1){
		int d;
		if(x<=n/2){
			d=1;
		}else{
			d=-1;
		}
		rep(i, n-1){
			v[i+1]=v[i]+d;
			if(d<0){
				d--;
				d=-d;
			}else{
				d++;
				d=-d;
			}
		}
	}else{
		int d;
		int flag;
		if(v[0]<=n/2){
			v[1]=n/2+1;
			d=-1;
			flag=0;
			if(n%2){
				d=1;
				flag=1;
			}
		}else{
			v[1]=n/2;
			d=1;
			flag=1;
		}
		rep3(i, n-1, 1){
			v[i+1]=v[i]+d;
			if(d<0){
				d--;
				d=-d;
			}else{
				d++;
				d=-d;
			}
		}
		rep3(i, n, 2){
			if(flag){
				if(v[i]>=v[0]) v[i]++;
			}else{
				if(v[i]<=v[0]) v[i]--;
			}
		}
	}
	rep(i, n){
		if(v[i]==0) v[i]=n;
	}

	PV(v);
 
	return 0;
}