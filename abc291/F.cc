#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=1047483647;
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

	int n, m;
	cin>> n >> m;
	vector<string> s(n);
	vector<int> dis(n, imax), rdis(n, imax);

	rep(i, n) cin >> s[i];

	dis[0]=0;
	rdis[n-1]=0;
	rep3(i, n, 1) {
		int mi=imax;
		rep(j, min(i+1, m)){
			if(i-j-1<0) break;
			// cout<< i SP<< j << endl;
			if(s[i-j-1][j]=='1'){
				mi=min(mi, dis[i-j-1]+1);
			}
			dis[i]=mi;
		}
	}
	// PV(dis);
	for(int i=n-2;i>=0;i--){
		rep(j, m){
			if(s[i][j]=='1'){
				rdis[i]=min(rdis[i], rdis[i+j+1]+1);
			}
		}
	}
	// PV(rdis);

	rep3(i, n-1, 1){
		// cout<< "i " << i <<endl;
		int mi=imax;
		for(int j=max(0, i-(m-1));j<i;j++){
			// cout<< "j " << j <<endl;
			for(int k=i+1;k<=min(n-1, i+m-1);k++){
				// cout<< i SP << j SP << k <<endl;
				if(k-j-1>=m) break;
				if(s[j][k-j-1]=='1'){
					mi=min(mi, dis[j]+rdis[k]+1);
					// cout<< dis[j] SP << rdis[k] <<endl;
				}
			}
		}
		if(mi<imax) cout<< mi SP;
		else cout<< -1 SP;
	}
	cout<< endl;
 
	return 0;
}