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

int main(){

	ll h, w, n, q, cr, cc;
	vector<ll> r, c, l;
	vector<char> d;
	map<ll, set<ll>> tate, yoko;

	cin>> h >> w >> cr >> cc >> n;
	r.resize(n);
	c.resize(n);
	rep(i, n){
		cin >> r[i] >> c[i];
		tate[c[i]].insert(r[i]);
		yoko[r[i]].insert(c[i]);
	}

	cin>> q;
	d.resize(q);
	l.resize(q);
	rep(i, q) cin >> d[i] >> l[i];

	rep(i, q) {
		if(d[i]=='L'){
			auto itr=yoko[cr].lower_bound(cc);
			if(itr==yoko[cr].begin()){
				cc-=l[i];
			}else{
				itr--;
				ll nxt=*itr;
				cc=max(nxt+1, cc-l[i]);
			}
			cc=max(1LL, cc);
		}else if(d[i]=='R'){
			auto itr=yoko[cr].lower_bound(cc);
			// cout<< yoko[cr].size() <<endl;
			if(itr==yoko[cr].end()){
				cc+=l[i];
			}else{
				ll nxt=*itr;
				// cout<< nxt <<endl;
				cc=min(nxt-1, cc+l[i]);
			}
			cc=min(w, cc);
		}else if(d[i]=='U'){
			auto itr=tate[cc].lower_bound(cr);
			if(itr==tate[cc].begin()){
				// cout<< *itr <<endl;
				cr-=l[i];
			}else{
				itr--;
				ll nxt=*itr;
				cr=max(nxt+1, cr-l[i]);
			}
			cr=max(1LL, cr);
		}else if(d[i]=='D'){
			auto itr=tate[cc].lower_bound(cr);
			if(itr==tate[cc].end()){
				cr+=l[i];
			}else{
				ll nxt=*itr;
				cr=min(nxt-1, cr+l[i]);
			}
			cr=min(h, cr);
		}else{
			assert(0);
		}
		cout<< cr SP << cc <<endl;
	}
 
	return 0;
}