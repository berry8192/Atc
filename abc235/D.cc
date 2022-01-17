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

vector<int> bo;
int ans=99999999;
LLi a, n;

void dfs(LLi x, int dep){
	//cout<< x SP << dep <<endl;
	if(bo[x]>dep){
		bo[x]=dep;
	}else{
		return;
	}
	if(x%a==0) dfs(x/a, dep+1);

	if(x<=10) return;
	string s=to_string(x);
	if(s[1]=='0') return;
	int sz=s.size();
	string tmp=s+s;
	string tmp2=tmp.substr(1, sz);
	//cout<< "#" <<tmp2 <<endl;
	dfs(stoll(tmp2), dep+1);
	// rep(i, sz){
	// 	string tmp2=tmp.substr(i+1, sz);
	// 	if(tmp2[0]=='0') continue;
	// 	dfs(stoll(tmp2), dep+i+1);
	// }
}

int main(){
	cin>> a >> n;

	bo.resize(1000010, imax);

	dfs(n, 0);

	if(bo[1]!=imax) cout<< bo[1] << endl;
	else cout<< -1 <<endl;
 
	return 0;
}