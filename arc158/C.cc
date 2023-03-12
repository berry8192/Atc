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

ll v[16][10];
vector<vector<map<ll, ll>>> mp;

int main(){

	int n;
	ll ans=0;
	string s;
	mp.resize(16);
	rep(i, 16) mp[i].resize(15);

	cin>> n;

	rep(i, n){
		cin >> s;
		reverse(all(s));
		rep(j, s.size()){
			int tmp=int(s[j]-'0');
			v[j][tmp]++;
			ans+=2*n*tmp;
		}

		int sz=s.size();
		rep(j, 15-sz) s+='0';
		// cout<< s <<endl;
		rep3(j, 16, 2){
			rep(k, 16-j){
				string ss=s.substr(k, j);
				if(ss[0]=='0') continue;
				ll stmp=stoll(ss);
				ans-=9*mp[j][k][stmp];
				// cout<< ss <<endl;
				int hea=int(ss[0]-'0');
				string t;
				rep(l, ss.size()){
					t+=char(int('9'-ss[l])+'0');
				}
				rep3(l, 10, 10-hea){
					t[0]='0'+l;
					// cout<< t <<endl;
					ll ttmp=stoll(t);
					mp[j][k][ttmp]+=j;
				}
			}
		}
	}
	// cout<< ans <<endl;

	rep(i, 15) {
		rep3(j, 10, 1){
			// cout<< v[i][j] SP;
			rep3(k, 10, 10-j){
				ans-=v[i][j]*v[i][k]*9;
			}
		}
		// cout<< endl;
	}

	cout<< ans << endl;
 
	return 0;
}