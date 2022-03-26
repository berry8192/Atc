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

	int n, m;
	vector<LLi> a, b, d;
	vector<vector<LLi>> c;

	cin>> n >> m;
	a.resize(n+1);
	d.resize(n+m+1);
	c.resize(m+2);
	c[0].resize(n+m+1);

	rep(i, n+1) cin >> a[i];
	rep(i, n+m+1) cin >> c[0][i];
	reverse(all(a));
	reverse(all(c[0]));
	//PVL(c[0]);

	rep(i, m+1) {
		int div=c[i][0]/a[0];
		//cout<< "div" << div <<endl;
		b.push_back(div);
		rep(j, n+1){
			d[j]=div*a[j];
		}
		rep(j, m) d[n+1+j]=0;
		//PVL(d);
		for(int j=i+1;j<n+m+1;j++){
			//cout<< c[i][j] << "-" << d[j-i] <<endl;
			c[i+1].push_back(c[i][j-i]-d[j-i]);
		}
		//PVL(c[i+1]);
	}
	
	reverse(all(b));

	PVL(b);
 
	return 0;
}