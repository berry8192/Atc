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

int main(){

	int t, r, c;
	cin>> t;

	rep(lp, t){
		cin>> r >> c;
		int cnt=0;
		char tmp;
		vector<string> bo;
		bo.resize(r);
		rep(i, r) bo[i].resize(c);
		int flag=1;

		rep(i, r){
			cin>> bo[i];
			rep(j, c){
				if(bo[i][j]=='^') cnt++;
			}
		}

		if(cnt==0){
			cout<< "Case #" << lp+1 << ": " << "Possible" << endl;
			rep(i, r){
				cout<< bo[i] <<endl;
			}
			continue;
		}

		if(r==1 || c==1){
			cout<< "Case #" << lp+1 << ": " << "Impossible" << endl;
			continue;
		}

		cout<< "Case #" << lp+1 << ": " << "Possible" << endl;
		rep(i, r){
			rep(j, c){
				printf("^");
			}
			cout<< endl;
		}
	}
 
	return 0;
}