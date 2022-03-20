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

template <class T> vector<LLi> ruiseki(T vv){
	vector<LLi> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
		// xx[i+1]=xx[i+1]%mod;
	}
	return xx;
}

int main(){

	int n, ma=-1, mi=imax, tmp1, tmp2;
	vector<LLi> v, w;
	set<int> st1;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		if(v[i]==0) v[i]=-1;
	}
	w=ruiseki(v);

	//PV(w);

	st1.insert(0);
	rep(i, n+1){
		tmp1=*st1.rbegin();
		tmp2=*st1.begin();
		//cout<< tmp1 SP << tmp2 <<endl;
		tmp1=w[i]-tmp1;
		tmp2=w[i]-tmp2;
		ma=max(ma, tmp2);
		mi=min(mi, tmp1);
		st1.insert(w[i]);
	}

	cout<< ma-mi+1 << endl;
 
	return 0;
}