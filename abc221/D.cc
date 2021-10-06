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

	int n, peo=0, prvd=0;
	vector<int> a, b, ans;
	map<int, int> mp;

	cin>> n;
	a.resize(n);
	b.resize(n);
	ans.resize(200010);

	rep(i, n) cin >> a[i] >> b[i];

	rep(i, n) {
		mp[a[i]]++;
		mp[a[i]+b[i]]--;
	}
	mp[0]=0;

	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
		if(key==0) continue;
  		// key, valueを使う
		//cout<< key << " " << value <<endl;
		ans[peo]+=key-prvd;
		peo+=value;
		prvd=key;
	}

	for(int i=1;i<=n;i++){
		cout<< ans[i] <<endl;
	}
 
	return 0;
}