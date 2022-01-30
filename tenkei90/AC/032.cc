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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

	int n, m, ans=imax;
	int bo[10][10], ng[11][11];
	vector<int> x, y;

	cin>> n;
	
	vector<int> p;
	rep(i, n) p.push_back(i);

	rep(i, n){
		rep(j, n){
			cin>> bo[i][j];
			ng[i][j]=0;
		}
		ng[10][i]=0;
	}

	cin>> m;
	x.resize(m);
	y.resize(m);

	rep(i, m){
		cin >> x[i] >> y[i];
		x[i]--;
		y[i]--;
		ng[x[i]][y[i]]=1;
		ng[y[i]][x[i]]=1;
	}

	do {
		int tmp=0, prv=10;
		//PV(p);
		rep(i, n){
			tmp+=bo[p[i]][i];
			if(ng[prv][p[i]]){
				tmp=imax;
				break;
			}
			prv=p[i];
		}
		ans=min(ans, tmp);
	} while (next_permutation(all(p)));

	if(ans==imax) ans=-1;
	cout<< ans << endl;
 
	return 0;
}