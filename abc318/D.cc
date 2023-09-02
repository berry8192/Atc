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

vector<vector<int>> v(16, vector<int>(16));

int n, fedge;
ll ma=0;
void dfs(int edge, ll sco){
	int from;
	rep(i, n){
		if(((1<<i)&edge)==0){
			from=i;
			break;
		}
	}
	// cout<< "from: " << from <<endl;
	rep3(i, n, from+1){
		if(((1<<i)&edge)==0){
			// cout<< "to: " << i <<endl;
			int nedge=edge;
			nedge+=(1<<from)+(1<<i);
			if(fedge==nedge){
				ma=max(ma, sco+v[from][i]);
				continue;
			}
			dfs(nedge, sco+v[from][i]);
		}
	}
}

int main(){

	int tmp;
	ll ans=0;

	cin>> n;
	// cout<< fedge <<endl;

	rep(i, n-1){
		rep(j, (n-1)-i){
			cin>> tmp;
			v[i][j+1+i]=tmp;
			v[j+1+i][i]=tmp;
		}
	}
	if(n%2) n++;
	fedge=(1<<n)-1;
	// PVV(v);

	dfs(0, 0);

	cout<< ma << endl;
 
	return 0;
}