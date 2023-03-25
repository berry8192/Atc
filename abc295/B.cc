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

	int r, c;
	cin>> r >> c;
	char v[20][20];

	rep(i, r){
		rep(j, c){
			cin>> v[i][j];
		}
	}

	rep(i, r){
		rep(j, c){
			if('0'<=v[i][j] && v[i][j]<='9'){
				int bom=int(v[i][j]-'0');
				rep(k, r){
					rep(l, c){
						int dis=abs(i-k)+abs(j-l);
						if(dis<=bom && v[k][l]=='#') v[k][l]='.';
					}
				}
				v[i][j]='.';
			}
		}
	}

	rep(i, r){
		rep(j, c){
			cout<< v[i][j];
		}
		cout<< endl;
	}
 
	return 0;
}