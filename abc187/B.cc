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
	vector<int> x, y;

	cin>> n;
	x.resize(n);
	y.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(abs(y[i]-y[j])<=abs(x[i]-x[j])) ans++;
		}
	}

	cout<< ans << endl;
 
	return 0;
}