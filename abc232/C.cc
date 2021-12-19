#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, m, flag=0, tmp;
	vector<int> v, a, b, c, d;
	vector< vector<int> > bo;

	cin>> n >> m;
	a.resize(m);
	b.resize(m);
	c.resize(m);
	d.resize(m);
	bo.resize(9);
	rep(i, 9) bo[i].resize(9);

	rep(i, m) cin >> a[i] >> b[i];
	rep(i, m){
		cin >> c[i] >> d[i];
		bo[c[i]-1][d[i]-1]=1;
		bo[d[i]-1][c[i]-1]=1;
	}
	//PVV(bo);
	rep(i, n) v.push_back(i);
	do {
		//cout<< endl;
		//PV(v);
		tmp=1;
		rep(i, m){
			//cout<< v[a[i]-1] SP << v[b[i]-1] <<endl;
			if(!bo[v[a[i]-1]][v[b[i]-1]]){
				tmp=0;
				break;
			}
			// cout<< a[v[i]]-1 SP << b[v[i]]-1 <<endl;
			// if(!bo[a[v[i]]-1][b[v[i]]-1]){
			// 	tmp=0;
			// 	break;
			// }
		}
		if(tmp){
			flag=1;
			break;
		}
	} while (next_permutation(all(v)));

	if(flag) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}