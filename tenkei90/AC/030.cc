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
LLi n, k, ans=0;
vector<LLi> able, pri={1, 2, 3};

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//n以下の素数を配列に{1, 2, 3, 5, 7, ...} make_prime_list
//i, j, flag, sqx, xを使用
void mplist(LLi x){
	int flag;

	for(int i=5;i<=x;i+=2){
		flag=0;
		for(int j=1;j<(int)pri.size();j++){
			if(i%pri[j]==0){
				flag=1;
				break;
			}
			if(x<pri[j]*pri[j]) break;
		}
		if(flag==0) pri.emplace_back(i);
	}
}

void dfs(LLi x, LLi nxt, int dep){
	if(dep==k){
		//cout<< x <<endl;
		for(LLi i=x;i<=n;i+=x) able[i]=1;
		return;
	}
	for(int i=nxt;i<pri.size();i++){
		//cout<< x SP << nxt SP << dep <<endl;
		LLi tmp=x*pri[i];
		if(tmp>n) return;
		dfs(tmp, i+1, dep+1);
	}
}

int main(){

	cin>> n >> k;
	if(k==1){
		cout<< n-1 <<endl;
		return 0;
	}
	able.resize(n+1);

	mplist(n/2+1);//nまでの素数列挙
	//PV(pri);
	dfs(1, 1, 0);

	rep3(i, n+1, 2){
		if(able[i]) ans++;
	}
	cout<< ans << endl;
 
	return 0;
}