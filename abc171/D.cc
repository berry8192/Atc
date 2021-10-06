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

	LLi n, q, su=0, tmp;
	vector<int> v, b, c, mp;

	cin>> n;
	v.resize(n);
	mp.resize(100010);

	rep(i, n){
		cin >> v[i];
		su+=v[i];
		mp[v[i]]++;
	}
	
	cin>> q;
	b.resize(q);
	c.resize(q);

	rep(i, q) {
		cin>> b[i] >> c[i];
	}

	rep(i, q){
		mp[c[i]]+=mp[b[i]];
		tmp=mp[b[i]]*(c[i]-b[i]);
		mp[b[i]]=0;
		su+=tmp;
		cout<< su <<endl;
	}
 
	return 0;
}