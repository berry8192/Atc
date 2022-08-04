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

	int n, q;
	string s;
	int t, l, r;
	char c;
	vector<vector<int>> v(1000);
	rep(i, 1000) v[i].resize(26);

	cin>> n;
	cin>> s;
	cin>> q;

	rep(i, n){
		v[i/1000][int(s[i]-'a')]=1;
	}

	rep(lp, q){
		cin>> t;
		if(t==1){
			cin>> l >> c;
			l--;
			int ls=l/1000;
			s[l]=c;
			rep(i, 26) v[ls][i]=0;
			for(int i=ls*1000;i<(ls+1)*1000;i++){
				if(n==i) break;
				v[ls][int(s[i]-'a')]=1;
			}
		}else{
			cin>> l >> r;
			int ls=(l+1000-1)/1000;
			l--;
			int rs=(r-1)/1000;
			//cout<< l SP << r <<endl;
			//cout<< ls SP << rs <<endl;
			vector<int> d(26);
			if(ls<rs){
				for(int i=l;i<ls*1000;i++){
					d[int(s[i]-'a')]=1;
				}
				for(int i=rs*1000;i<r;i++){
					d[int(s[i]-'a')]=1;
				}
				for(int i=ls;i<rs;i++){
					rep(j, 26) d[j]+=v[i][j];
				}
			}else{
				for(int i=l;i<r;i++){
					d[int(s[i]-'a')]=1;
				}
			}
			
			int tmp=0;
			rep(i, 26){
				if(d[i]>0) tmp++;
			}
			cout<< tmp <<endl;
		}
	}

	return 0;
}