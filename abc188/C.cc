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

	int n, tmp;
	vector< vector<int> > v;
	map<int, int> m;

	cin>> n;
	v.resize(n);

	rep(i, 1<<n){
		cin >> tmp;
		m[tmp]=i+1;
		v[0].push_back(tmp);
	}

	for(int i=0;i<n-1;i++) {
		//PV(v[i]);
		for(int j=0;j<v[i].size();j+=2){
			v[i+1].push_back(max(v[i][j], v[i][j+1]));
		}
	}

	cout<< m[min(v[n-1][0], v[n-1][1])] << endl;
 
	return 0;
}