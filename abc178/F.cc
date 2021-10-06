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

	int n, pre, sta, stb;
	vector<int> a, b;
	map<int, int> mp;

	cin>> n;
	a.resize(n);
	b.resize(n);
	vector<pair<int, int>> pa(n);

	rep(i, n) cin >> a[i];
	rep(i, n){
		cin >> b[i];
		mp[b[i]]++;
	}
	
	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
  		// key, valueを使う
		pa.push_back(value, key);
	}

	sort(pa.begin(), pa.end());

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}