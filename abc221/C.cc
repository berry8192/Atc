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

	int n, sz;
	LLi ans=0, aa, bb;
	string s, tmpa, tmpb;
    vector<int> a, b;
	vector<int> v;

	cin>> s;
	sz=s.size();

	rep(i, s.size()){
		v.push_back((int)(s[i]-'0'));
	}

	for (int bit = 0; bit < (1<<sz); ++bit) {
		a.clear();
		b.clear();
		tmpa="0";
		tmpb="0";
		//全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				a.push_back((int)(s[i]-'0'));
			}else{
				b.push_back((int)(s[i]-'0'));
			}
        }
		
		sort(a.begin(), a.end(), greater<int>());
		sort(b.begin(), b.end(), greater<int>());

		rep(i, a.size()) tmpa+=to_string(a[i]);
		rep(i, b.size()) tmpb+=to_string(b[i]);

		aa=stoi(tmpa);
		bb=stoi(tmpb);
		//cout<< aa SP << bb <<endl;

		ans=max(aa*bb, ans);
    }

	cout<< ans << endl;
 
	return 0;
}