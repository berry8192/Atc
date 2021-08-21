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

	int n;
	LLi ans=0, cnt=0;
	vector<LLi> a, b, c;

	cin>> n;
	a.resize(n);
	b.resize(n);
	c.resize(n);

	rep(i, n){
		cin >> a[i] >> b[i];
		ans-=a[i];
		c[i]=2*a[i]+b[i];
	}

	sort(c.begin(), c.end(), greater<LLi>());
	for(int i=0;i<n;i++){
		ans+=c[i];
		cnt++;
		if(ans>0) break;
	}

	cout<< cnt << endl;
 
	return 0;
}