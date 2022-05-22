#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int main(){

	//182-c 各桁に0を含まない数:nの桁をいくつか消して3の倍数にする。最小で何個消せばよいか
	int tmp, sz, mi=imax;
	ll n;
	string s;

	cin>> n;

	//nを文字列sに変換
	s=to_string(n);
	//桁数を取得
	sz=s.size();

	//1を左シフトして2^szが出せる
	for (int bit = 0; bit < (1<<sz); ++bit) {
        vector<int> S;
		tmp=0;
		//全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)) tmp+=(int)(s[i]-'0');
        }
		//cout<< bit SP << tmp <<endl;
		if(tmp%3==0){
			//第二引数は0のビットの個数
			mi=min(mi, sz-__builtin_popcount(bit));
		}
    }

	if(mi==sz) cout<< -1 << endl;
	else cout<< mi << endl;
 
	return 0;
}