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

int n, k;
vector<LLi> x, y, z;
LLi ans=llimax;

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

void dfs(vector< vector<int> > p, int idx){
	if(idx==n){
		//cout<<"end"<<endl;
		//PVV(p);
		LLi tmp=0;
		rep(i, int(p.size())){
			rep(j, p[i].size()){
				rep3(l, p[i].size(), j+1){
					LLi xx=x[p[i][j]]-x[p[i][l]];
					LLi yy=y[p[i][j]]-y[p[i][l]];
					tmp=max(tmp, xx*xx+yy*yy);
				}
			}
		}
		//cout<< "tmp=" << tmp <<endl;
		ans=min(ans, tmp);
		return;
	}
	rep(i, int(p.size())){
		if(k-p.size()>n-idx) break;
		vector< vector<int> > q=p;
		q[i].push_back(idx);
		dfs(q, idx+1);
	}
	if(int(p.size())<k){
		p.push_back({idx});
		dfs(p, idx+1);
	}
}

int main(){
	cin>> n >> k;
	x.resize(n);
	y.resize(n);
	z.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	dfs({}, 0);

	cout<< ans << endl;
 
	return 0;
}