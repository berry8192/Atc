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

	LLi n, su=0;
	vector<LLi> v, w;
	set<LLi> st;

	cin>> n;
	v.resize(2*n);

	rep(i, n){
		cin >> v[i];
		v[i+n]=v[i];
		su+=v[i];
	}
	if(su%10){
		cout<<"No"<<endl;
		return 0;
	}
	w=ruiseki(v);
	//PV(v);
	//PV(w);

	rep(i, 2*n+1) {
		if (st.find(w[i]-su/10)!=st.end()){
			cout<<"Yes"<<endl;
			return 0;
		}
		st.insert(w[i]);
	}

	cout<< "No" << endl;
 
	return 0;
}