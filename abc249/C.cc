#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, k, ma=0;
	vector<string> s;

	cin>> n >> k;
	s.resize(n);

	rep(i, n) cin >> s[i];

	for (int bit = 0; bit < (1<<n); ++bit) {
        vector<int> tmp(26);
		//全ての桁に対する処理
        for (int i = 0; i < n; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				rep(j, s[i].size()){
					tmp[int(s[i][j]-'a')]++;
				}
				//cout<< i SP;
			}
        }
		//cout<< bit SP << tmp <<endl;
		int ans=0;
		rep(i, 26){
			if(tmp[i]==k) ans++;
		}
		ma=max(ans, ma);
		//cout<< endl;
    }

	cout<< ma << endl;
 
	return 0;
}