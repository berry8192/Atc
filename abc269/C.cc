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

string tob(ll n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

int main(){

	ll n, sz;
	string s;
	vector<ll> v, ans;

	cin>> n;

	s=tob(n);

	//cout<< s <<endl;

	rep(i, s.size()){
		if(s[i]=='1') v.push_back(i);
	}

	sz=v.size();

	//1を左シフトして2^szが出せる
	for (ll bit = 0; bit < (1<<sz); ++bit) {
		ll tmp=0;
		//全ての桁に対する処理
        for (ll i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1LL<<i)) tmp+=(1LL<<v[i]);
        }
		//cout<< bit SP << tmp <<endl;
		ans.push_back(tmp);
    }

	rep(i, ans.size()) cout<< ans[i] << endl;
 
	return 0;
}