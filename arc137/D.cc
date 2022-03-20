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

string tob(LLi n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

int main(){

	int n, m;
	vector<LLi> v;
	vector< vector<LLi> > ans;
	//vector<string> w;

	cin>> n >> m;
	v.resize(n);
	//w.resize(n);
	ans.resize(60);
	rep(i, 60) ans[i].resize(n);

	rep(i, n){
		cin >> v[i];
		//w[i]=tob(v[i], 32);
	}

	// rep(i, n) {
	// 	cout<< w[i] <<endl;
	// }
	rep(i, n){
		ans[0][i]=v[i];
		if(i) ans[0][i]=(ans[0][i]^ans[0][i-1]);
	}

	rep(i, 59){
		rep(j, n){
			ans[i+1][j]=ans[i][j];
			if(j) ans[i+1][j]=(ans[i+1][j]^ans[i+1][j-1]);
		}
	}

	int mod=m;
	rep(i, m){
		if(i && ans[0][n-1]==ans[i][n-1]) mod=i;
		cout<< ans[i%mod][n-1] << " ";
	}
	cout<< endl;
 
	return 0;
}