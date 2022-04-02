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

	LLi n, k, x, tmp, us=0, ans=0;
	vector<LLi> a;

	cin>> n >> k >> x;
	a.resize(n);

	rep(i, n){
		cin >> a[i];
		tmp=a[i]/x;
		us+=tmp;
		a[i]=a[i]%x;
		//cout<< a[i] <<endl;
		//cout<< us <<endl;
	}
	sort(all(a), greater<LLi>());
	//PV(a);

	if(us>=k){
		us-=k;
	}else{
		k-=us;
		us=0;
		rep(i, n){
			a[i]=0;
			k--;
			if(k==0) break;
		}
	}

	ans=us*x;
	rep(i, n){
		ans+=a[i];
	}

	cout<< ans << endl;
 
	return 0;
}