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

	LLi n, ans=0;
	cin>> n;
	string s;
	cin>> s;
	vector<int> a, t, g, c;

	a.resize(n+1);
	t.resize(n+1);
	g.resize(n+1);
	c.resize(n+1);

	for(int i=1;i<=n;i++){
		a[i]=a[i-1];
		t[i]=t[i-1];
		g[i]=g[i-1];
		c[i]=c[i-1];
		if(s[i-1]=='A') a[i]++;
		if(s[i-1]=='T') t[i]++;
		if(s[i-1]=='G') g[i]++;
		if(s[i-1]=='C') c[i]++;
	}

	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(a[j]-a[i-1]==t[j]-t[i-1] && g[j]-g[i-1]==c[j]-c[i-1]) ans++;
		}
	}
		cout<< ans << endl;
 
	return 0;
}