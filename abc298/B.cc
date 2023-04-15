#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

vector<vector<int>> rot(vector<vector<int>> x){
	vector<vector<int>> rtn=x;
	int sz=x.size();
	rep(i, sz){
		rep(j, sz){
			rtn[i][j]=x[j][sz-1-i];
		}
	}
	return rtn;
}

int main(){

	int n;
	cin>> n;
	vector<vector<int>> a, b;
	rep(i, n) a.resize(n, vector<int>(n));
	rep(i, n) b.resize(n, vector<int>(n));

	rep(i, n){
		rep(j, n){
			cin>> a[i][j];
		}
	}
	rep(i, n){
		rep(j, n){
			cin>> b[i][j];
		}
	}

	rep(lp, 4){
		b=rot(b);
		int flag=1;
		rep(i, n){
			rep(j, n){
				if(a[i][j] && !b[i][j]) flag=0;
			}
		}
		if(flag){
			cout<< "Yes" <<endl;
			return 0;
		}
	}

	cout<< "No" << endl;
 
	return 0;
}