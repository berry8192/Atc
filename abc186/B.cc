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

	int h, w, mi=200, su=0;
	vector< vector<int> > v;

	cin>> h >> w;
	v.resize(h);
	rep(i, h) v[i].resize(w);

	rep(i, h){
		rep(j, w){
			cin >> v[i][j];
			mi=min(mi, v[i][j]);
			su+=v[i][j];
		}
	}

	cout<< su-h*w*mi << endl;
 
	return 0;
}