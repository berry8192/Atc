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

	int n, k, ans=0;
	vector<int> v;
	map<int, int> ma;

	cin>> n >> k;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, k) {
		ma[v[i]]++;
		//cout<< "   " << ma[v[i]] <<endl;
	}
	ans=ma.size();
		//cout<< ans <<endl;
	for(int i=k;i<n;i++){
		ma[v[i-k]]--;
		//cout<< "   " << ma[v[i-k]] <<endl;
		if(ma[v[i-k]]==0) ma.erase(v[i-k]);
		ma[v[i]]++;
		//cout<< "   " << ma[v[i]] <<endl;
		ans=max(ans, (int)ma.size());
		//cout<< ans <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}