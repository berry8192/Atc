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
LLi mod=998244353;

vector<LLi> p, q, f, seen(200010);
LLi rtn;

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

void dfs(int x, int dep, int ori){
	seen[x]=1;
	if(ori==f[x]){
		rtn=dep;
		return;
	}
	dfs(f[x], dep+1, ori);
}

int main(){

	int n, ans=1;
	vector<LLi> fiv(200010);
	rep(i, 200010){
		if(i==0){
			fiv[i]=2;
		}else if(i==1){
			fiv[i]=3;
		}else{
			fiv[i]=fiv[i-1]+fiv[i-2];
			fiv[i]%=mod;
		}
	}

	cin>> n;
	p.resize(n);
	q.resize(n);
	f.resize(n+1);

	rep(i, n){
		cin >> p[i];
		p[i]--;
	}
	rep(i, n){
		cin >> q[i];
		q[i]--;
		f[p[i]]=q[i];
	}

	rep(i, n) {
		if (seen[i]!=1){
			dfs(i, 0, i);
			LLi tmp=rtn;
			//cout<< tmp SP << fiv[tmp] <<endl;
			LLi mul=1;
			if(tmp>3){
				mul=(fiv[tmp-1]+fiv[tmp-3])%mod;
			}else if(tmp==2){
				mul=4;
			}else if(tmp==1){
				mul=3;
			}
			ans=(ans*mul)%mod;
		}
	}

	cout<< ans << endl;
 
	return 0;
}