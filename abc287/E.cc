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

int imax=2147483647;
ll lmax=9223372036854775807;
ll mod2=1000000007;
ll mod=998244353;

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

	int n, mlen=0;
	cin>> n;
	vector<string> s(n);

	rep(i, n){
		cin >> s[i];
		mlen=max(mlen, int(s[i].size()));
	}

	// ローリングハッシュ?
	vector<map<ll, int>> v(mlen);
	vector<vector<ll>> w(n);
	vector<map<ll, int>> v2(mlen);
	vector<vector<ll>> w2(n);

	rep(i, n) {
		ll tmp=0;
		ll tmp2=0;
		ll d=1;
		ll d2=1;
		rep(j, s[i].size()){
			tmp+=int(s[i][j]-'a'+1)*d;
			tmp%=mod;
			d*=27;
			d%=mod;
			tmp2+=int(s[i][j]-'a'+1)*d2;
			tmp2%=mod2;
			d2*=27;
			d2%=mod;
			v[j][tmp]++;
			w[i].push_back(tmp);
			v2[j][tmp2]++;
			w2[i].push_back(tmp2);
		}
	}

	rep(i, n){
		repr(j, s[i].size()){
			if(v[j][w[i][j]]>1 && v2[j][w2[i][j]]>1){
				cout<< j+1 <<endl;
				break;
			}
			if(j==0) cout<< 0 <<endl;
		}
	}
 
	return 0;
}