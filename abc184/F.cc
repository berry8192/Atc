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

	LLi n, t, sz1, sz2, tmp, ma=-1;
	vector<LLi> v1, v2, s1, s2;

	cin>> n >> t;
	sz1=n/2;
	sz2=n-sz1;
	v1.resize(sz1);
	v2.resize(sz2);

	rep(i, sz1) cin >> v1[i];
	rep(i, sz2) cin >> v2[i];

	for (int bit = 0; bit < (1<<sz1); ++bit) {
		tmp=0;
		//全ての桁に対する処理
        for (int i = 0; i < sz1; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)) tmp+=v1[i];
        }
		//cout<< bit SP << tmp <<endl;
		s1.push_back(tmp);
    }
	for (int bit = 0; bit < (1<<sz2); ++bit) {
		tmp=0;
		//全ての桁に対する処理
        for (int i = 0; i < sz2; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)) tmp+=v2[i];
        }
		//cout<< bit SP << tmp <<endl;
		s2.push_back(tmp);
    }
	sort(all(s2));
	//PVL(s1);
	//PVL(s2);

	rep(i, s1.size()){
		auto lb = lower_bound(all(s2), t-s1[i]);
		int p=lb-s2.begin();
		//cout<< s1[i] SP << p SP << s2[p] <<endl;
		if(s2[p]+s1[i]<=t) ma=max(ma, s2[p]+s1[i]);
		if(s2[max(0, p-1)]+s1[i]<=t) ma=max(ma, s2[max(0, p-1)]+s1[i]);
	}

	cout<< ma <<endl;
 
	return 0;
}