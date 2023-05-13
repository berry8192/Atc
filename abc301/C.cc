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

	string s, t, u="atcoder";
	cin>> s;
	cin>> t;
	vector<int> sd(26), td(26);
	int sa=0, ta=0, ls=0, lt=0;

	rep(i, s.size()) {
		if(s[i]=='@'){
			sa++;
		}else{
			sd[int(s[i]-'a')]++;
		}
		if(t[i]=='@'){
			ta++;
		}else{
			td[int(t[i]-'a')]++;
		}
	}
	rep(i, 26){
		int flag=1;
		rep(j, 7){
			if(char('a'+i)==u[j]){
				flag=0;
			}
		}
		if(flag && sd[i]!=td[i]){
			cout<< "No" <<endl;
			return 0;
		}
		if(sd[i]>td[i]) ls+=sd[i]-td[i];
		if(sd[i]<td[i]) lt+=td[i]-sd[i];
	}
	// cout<< sa <<endl;
	// cout<< ta <<endl;
	// cout<< ls <<endl;
	// cout<< lt <<endl;

	if(lt<=sa && ls<=ta) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}