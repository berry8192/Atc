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

	int h, w, ans=0, ma;
	vector< vector<int> > v;
	vector<int> cnt;

	cin>> h >> w;
	cnt.resize(h*w+1);
	v.resize(h);
	rep(i, h) v[i].resize(w);

	rep(i, h){
		rep(j, w){
			cin >> v[i][j];
		}
	}

	int sz=h;
	for (int bit = 0; bit < (1<<sz); ++bit) {
        vector<int> S;
		rep(i, h*w+1) cnt[i]=0;
		int tmp=0;
		//全ての桁に対する処理
		rep(j, w){
			int val=0;
			int flag=1;
			for (int i = 0; i < sz; ++i) {
				//探索対象となっているbitかどうかを判定
				if(bit & (1<<i)){
					if(val!=0 && val!=v[i][j]){
						flag=0;
						break;
					}
					val=v[i][j];
				}
			}
			if(flag){
				cnt[val]+=__builtin_popcount(bit);
				//cout<< __builtin_popcount(bit) <<endl;
			}
		}
		//cout<< bit SP << tmp <<endl;
		ma=0;
		rep(i, h*w+1) ma=max(ma, cnt[i]);
		ans=max(ans, ma);
    }

	cout<< ans << endl;
 
	return 0;
}