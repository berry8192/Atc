#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

	int n, k, le=0, ans=0, flag=1;
	map<int, int> mp;
	vector<int> v;

	cin>> n >> k;

	v.resize(n);
	rep(i, n) cin>> v[i];

	rep(i, n){
		if(mp.size()<k || 1){
			mp[v[i]]++;
		}
		while(mp.size()>k){
			mp[v[le]]--;
			if(mp[v[le]]==0) mp.erase(v[le]);
			le++;
		}
		if(mp.size()==k){
          ans=max(ans, i-le+1);
          flag=0;
        }
		//cout<< i << " " << le <<" " << mp.size() <<endl;
	}

  	if(flag) ans=n;
	cout<< ans << endl;
 
	return 0;
}
