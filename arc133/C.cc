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

	int h, w, k, tmp, cmp;
	LLi ans=0, sa=0, sb=0;
	vector<int> a, b;

	cin>> h >> w >> k;
	if(h<w) swap(h, w);
	a.resize(h);
	b.resize(w);

	rep(i, h){
		if(h<w) cin >> b[i];
		else cin >> a[i];
		sa+=a[i];
	}
	rep(i, w){
		if(h<w) cin >> a[i];
		else cin >> b[i];
		sb+=b[i];
	}
	if(sa%k!=sb%k){
		cout<< -1 <<endl;
		return 0;
	}
	if(w==1){
		cout<< b[0] <<endl;
		return 0;
	}

	rep(i, w){
		tmp=w*(k-1);
		cmp=tmp/k*k+b[i];
		if(cmp>tmp) cmp-=k;
		ans+=cmp;
		cout<< ans <<endl;
	}
	rep(i, h){
		tmp=w*(k-1);
		cmp=tmp/k*k+a[i];
		if(cmp>tmp) cmp-=k;
		ans+=cmp;
		cout<< ans <<endl;
	}
	
	cout<< ans << endl;
 
	return 0;
}