#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

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

	int n, q;
	vector<int> a, b, x, y, ansl, ansr;
	set<int> st, ws;

	cin>> n;
	a.resize(n);
	b.resize(n);
	ansl.resize(n, imax);
	ansr.resize(n);
	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];
	b.push_back(-1);
	
	cin>> q;
	x.resize(q);
	y.resize(q);
	rep(i, q){
		cin >> x[i] >> y[i];
		x[i]--;
		y[i]--;
	}

	int pos=0;
	rep(i, n) {
		if(st.find(a[i])!=st.end()){
			//cout<< "! " << a[i] <<endl;
			ansl[i]=ansl[i-1];
			ansr[i]=ansr[i-1];
			continue;
		}
		st.insert(a[i]);
		ws.insert(a[i]);
		// b[pos]がaのsetに入っていなければa[i]はNoになる
		if(st.find(b[pos])==st.end()){
			ansl[i]=-1;
			ansr[i]=-1;
		}else{
			while(st.find(b[pos])!=st.end()){
				if(ws.find(b[pos])!=ws.end()) ws.erase(b[pos]);
				if(ws.empty()) ansl[i]=min(ansl[i], pos);
				pos++;
			}
			ansr[i]=pos-1;
		}
	}

	// PV(ansl);
	// PV(ansr);

	rep(i, q){
		if(ansl[x[i]]<=y[i] && y[i]<=ansr[x[i]]) cout<< "Yes" <<endl;
		else cout<< "No" <<endl;
	}
 
	return 0;
}