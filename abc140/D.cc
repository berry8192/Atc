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

void rle(string s, vector<pair<char, int>> &vec)
{
  int cnt = 1;
  for(int i = 1; i < (int)s.size(); i++){
    if(s[i] != s[i-1]){
      vec.push_back({s[i-1], cnt});
      cnt = 0;
    }
    cnt++;
  }
  vec.push_back({s.back(), cnt});
}

int main(){

	int n, k, ans=0;
	string s;
	vector<pair<char, int>> v;

	cin>> n >> k;
	cin>> s;

	rle(s, v);

	int tmp=n-v.size()+k*2;
	cout<< min(max(0, tmp), n-1) <<endl;
 
	return 0;
}