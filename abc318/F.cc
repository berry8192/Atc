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

vector<ll> sorted_unique(vector<ll> vv){
	vector<ll> rtn;
	rtn.push_back(vv[0]);
	rep(i, vv.size()-1){
		if(vv[i]!=vv[i+1]) rtn.push_back(vv[i+1]);
	}
	return rtn;
}

int main(){

	ll n, ans=0;
	vector<ll> x, l, pos, p;

	cin>> n;
	x.resize(n);
	l.resize(n);

	rep(i, n) cin >> x[i];
	rep(i, n) cin >> l[i];

	rep(i, n) {
		rep(j, n){
			pos.push_back(x[i]-l[j]-1);
			pos.push_back(x[i]-l[j]);
			pos.push_back(x[i]-l[j]+1);
			pos.push_back(l[i]-x[j]-1);
			pos.push_back(l[i]-x[j]);
			pos.push_back(l[i]-x[j]+1);
			pos.push_back(x[i]+l[j]-1);
			pos.push_back(x[i]+l[j]);
			pos.push_back(x[i]+l[j]+1);
			pos.push_back(l[i]+x[j]-1);
			pos.push_back(l[i]+x[j]);
			pos.push_back(l[i]+x[j]+1);
		}
	}
	sort(all(pos));
	p=sorted_unique(pos);
	// PV(p);

	bool getx=false;
	ll getp;
	rep(i, p.size()){
		vector<ll> dist(n);
		rep(j, n){
			dist[j]=abs(x[j]-p[i]);
		}
		sort(all(dist));
		int flg=1;
		rep(j, n){
			if(l[j]<dist[j]){
				flg=0;
				break;
			}
		}
		if(flg){
			// cout<< "get: ";
			// cout<< p[i] <<endl;
			if(getx){
				ans+=p[i]-getp;
			}else{
				ans++;
			}
			getp=p[i];
			getx=true;
		}else{
			// cout<< "not get: ";
			// cout<< p[i] <<endl;
			// if(getx) ans++;
			getx=false;
		}
	}

	cout<< ans << endl;
 
	return 0;
}