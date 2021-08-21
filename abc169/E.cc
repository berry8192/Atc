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
	vector<int> a, b;

	cin>> n;
	a.resize(n);
	b.resize(n);

	rep(i, n) cin >> a[i] >> b[i];
	
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	if(n%2==1){
		ans=b[n/2]-a[n/2]+1;
	}else{
		ans=b[n/2-1]+b[n/2]-(a[n/2-1]+a[n/2])+1;
	}

	cout<< ans << endl;
 
	return 0;
}