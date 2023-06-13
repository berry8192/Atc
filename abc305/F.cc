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

	int n, m, k, cur=1, tmp;
	string s;
	cin>> n >> m;
	vector<int> seen(n+1), prev(n+1);
	vector<set<int>> st(n+1);

	rep(lp, n*2){
		cin>> k;
		if(k==-1) return 1;
		rep(i, k){
			cin>> tmp;
			if(tmp==n){
				cout<< n <<endl;
				cin>> s;
				return 0;
			}
			if(!seen[cur]) st[cur].insert(tmp);
		}
		seen[cur]=1;
		int flag=0;
		while(!st[cur].empty()){
			int nxt=*st[cur].begin();
			if(seen[nxt]){
				st[cur].erase(nxt);
				continue;
			}
			prev[nxt]=cur;
			cout<< nxt <<endl;
			st[cur].erase(nxt);
			cur=nxt;
			flag=1;
			break;
		}
		if(flag) continue;
		cout<< prev[cur] <<endl;
		cur=prev[cur];
	}
	cout<< "WA" <<endl;
 
	return 0;
}