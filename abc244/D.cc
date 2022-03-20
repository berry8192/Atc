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

	int n, sa=0, ta=0;
	vector<int> s, t;
	char u;

	rep(i, 3){
		cin>> u;
		if(u=='R') s.push_back(0);
		if(u=='G') s.push_back(1);
		if(u=='B') s.push_back(2);
	}
	rep(i, 3){
		cin>> u;
		if(u=='R') t.push_back(0);
		if(u=='G') t.push_back(1);
		if(u=='B') t.push_back(2);
	}

	rep(i, 3){
		if((s[1]-s[0]+3)%3==1 && (s[2]-s[1]+3)%3==1) sa=1;
	}
	rep(i, 3){
		if((t[1]-t[0]+3)%3==1 && (t[2]-t[1]+3)%3==1) ta=1;
	}

	if(sa==ta) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}