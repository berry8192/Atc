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

	int n, ans=0;
	vector<int> v, w(3);

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	sort(v.begin(), v.end());

	rep(i, n){
		rep(j, n){
			rep(k, n){
				if(v[i]==v[j] || v[i]==v[k] || v[j]==v[k]) break;
				w[0]=v[i];
				w[1]=v[j];
				w[2]=v[k];
				sort(w.begin(), w.end());
				if(w[0]+w[1]>w[2]) ans++;
			}
		}
	}

	cout<< ans/2 << endl;
 
	return 0;
}