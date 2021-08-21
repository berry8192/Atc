#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

LLi mod=998244353;
int imax=2147483647;
long long int llimax=9223372036854775807;

vector<int> v, seen, d;
//vector< vector<int> > inv;
int st, flag;

//LLi型vectorを出力
bool dfs(int x, int cnt) {
	if(seen[x]) return false;
	seen[x]=cnt;
	//cout<< x SP << cnt <<endl;
	if(v[x]==st) return true;
	if(d[v[x]]) return false;
	return dfs(v[x], cnt);
}

LLi modpow(LLi a, LLi n, LLi mod) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, cnt=0;
	LLi ans=0;

	cin>> n;
	v.resize(n+1);
	seen.resize(n+1);
	//inv.resize(n+1);
	d.resize(n+1);

	rep(i, n){
		cin >> v[i+1];
		if(i+1==v[i+1]){
			d[i+1]=1;
			ans++;
		}
		//inv[i+1].push_back(v[i+1]);
	}
	//PV(d);

	for(int i=1;i<n+1;i++) {
		cnt++;
		st=i;
		if(d[i]) continue;
		//cout<< "%" <<endl;
		if(dfs(i, cnt)) ans++;
	}
	//cout<< "#" <<endl;
	cout<< (modpow(2, ans, mod)-1+mod)%mod << endl;
 
	return 0;
}