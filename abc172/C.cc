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

	LLi n, m, k, ra=0, rb=0, rt=0, ma=0;
	vector<LLi> a, b;

	cin>> n >> m >> k;
	a.resize(n);
	b.resize(m);

	rep(i, n) cin >> a[i];
	rep(i, m) cin >> b[i];

	rep(i, n) {
		if(rt+a[i]<=k){
			rt+=a[i];
			ra++;
		}else{
			break;
		}
	}

	rep(i, m) {
		if(rt+b[i]<=k){
			rt+=b[i];
			rb++;
		}else{
			break;
		}
	}

	ma=ra+rb;

	while(1){
		if(ra==0) break;
		ra--;
		rt-=a[ra];

		while(1){
			if(rb==m) break;
			if(rt+b[rb]<=k){
				rt+=b[rb];
				rb++;
			}else{
				break;
			}
		}

		ma=max(ma, ra+rb);
	}

	cout<< ma << endl;
 
	return 0;
}