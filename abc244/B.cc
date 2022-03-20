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

	int a;
	cin>> a;
	int x=0, y=0;
	string s;
	cin>> s;
	int dir=0;
	int dx[]={1, 0, -1, 0};
	int dy[]={0, -1, 0, 1};

	rep(i, s.size()){
		if(s[i]=='S'){
			x+=dx[dir];
			y+=dy[dir];
		}else{
			dir++;
			dir%=4;
		}
	}

	cout<< x SP << y <<endl;
 
	return 0;
}