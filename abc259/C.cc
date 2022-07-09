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

	string s, t, sc, tc;
	vector<int> sd, td;

	cin>> s;
	cin>> t;
	s+="0";
	t+="0";

	int tmp=1;
	rep(i, s.size()-1){
		if(s[i]==s[i+1]){
			tmp++;
		}else{
			sc+=s[i];
			sd.push_back(tmp);
			tmp=1;
		}
	}
	rep(i, t.size()-1){
		if(t[i]==t[i+1]){
			tmp++;
		}else{
			tc+=t[i];
			td.push_back(tmp);
			tmp=1;
		}
	}

	if(sc!=tc){
		cout<< "No" <<endl;
		return 0;
	}
	int flag=1;
	rep(i, sc.size()){
		if(td[i]<sd[i]){
			flag=0;
			break;
		}
		if(td[i]>sd[i] && sd[i]==1){
			flag=0;
			break;
		}
	}

	if(flag){
		cout<< "Yes" <<endl;
	}else{
		cout<< "No" <<endl;
	}
}