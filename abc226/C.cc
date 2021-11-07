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
LLi ans=0;
vector<LLi> t, k, gt;
vector< vector<LLi> > a;

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

void dfs(int x){
	//cout<< x <<endl;
	if(gt[x]==1) return;
	ans+=t[x];
	int flag=1;
	rep(i, a[x].size()){
		if(gt[a[x][i]]==0){
			flag=0;
			break;
		}
	}
	if(flag){
		gt[x]=1;
		return;
	}else{
		rep(i, a[x].size()){
			if(gt[a[x][i]]==0){
				dfs(a[x][i]);
			}
		}
		gt[x]=1;
	}
}

int main(){

	int n, tmp;

	cin>> n;
	t.resize(n+1);
	k.resize(n+1);
	gt.resize(n+1);
	a.resize(n+1);

	rep(i, n){
		cin >> t[i+1] >> k[i+1];
		rep(j, k[i+1]){
			cin>> tmp;
			a[i+1].push_back(tmp);
		}
	}

	dfs(n);

	cout<< ans <<endl;
 
	return 0;
}