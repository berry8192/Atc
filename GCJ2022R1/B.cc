#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	int t, su;
	int v[3][4], mi[4];
	cin>> t;
	rep(lp, t){
		rep(i, 4) mi[i]=1000000;
		su=0;
		rep(i, 3){
			rep(j, 4){
				cin>> v[i][j];
			}
		}
		cout<< "Case #" << lp+1 << ": ";
		rep(i, 4){
			rep(j, 3){
				mi[i]=min(mi[i], v[j][i]);
			}
			if(su+mi[i]>1000000) mi[i]=1000000-su;
			su+=mi[i];
		}
		if(su<1000000) cout<< "IMPOSSIBLE" <<endl;
		else{
			rep(i, 3) cout<< mi[i] << " ";
			cout<< mi[3] <<endl;
		}
	}

	return 0;
}