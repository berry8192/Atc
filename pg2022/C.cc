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

	int n, m, k;
	string s, t;
	vector<int> x, y;

	cin>> n >> m;
	cin>> s;
	cin>> t;
	cin>> k;
	x.resize(k);
	y.resize(k);
	vector<vector<int>> v(n, vector<int>(m));
	bitset<20> bs(t);
	cout<< bs <<endl;
	bitset<20> bs1(0);
	bs1[m-1]=1;
	cout<< bs1 <<endl;
	bitset<20> bs2=(bs ^ bs1);
	bitset<20> bs3=(bs & bs1);
	cout<< bs2 <<endl;
	cout<< bs3 <<endl;
	return 0;

	rep(i, k) cin >> x[i] >> y[i];

	rep(i, n) {
		v[i][0]=int(s[i]-'0');
	}
	rep(i, m) {
		v[0][i]=int(t[i]-'0');
	}

	rep3(i, n, 1){
		rep3(j, m, 1){
			v[i][j]=v[i-1][j]^v[i][j-1];
		}
	}

	PVV(v);

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}

/*

30 34
111111010010111111010010010010
1011101011011101011101010111010101
4
2 6
4 5
5 7
3 3


*/