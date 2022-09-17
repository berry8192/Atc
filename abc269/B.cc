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

	int x1=-1, y1, x2, y2;
	vector<string> s(10);

	rep(i, 10) cin>> s[i];

	rep(i, 10){
		rep(j, 10){
			if(s[i][j]=='#'){
				if(x1==-1){
					x1=i+1;
					y1=j+1;
				}
				x2=i+1;
				y2=j+1;
			}
		}
	}

	cout<< x1 SP << x2 <<endl;
	cout<< y1 SP << y2 << endl;
 
	return 0;
}