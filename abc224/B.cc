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

	int a, b;
	cin>> a >> b;
	vector< vector<int> > v;
	v.resize(a);
	for(int i=0;i<a;i++) v[i].resize(b);

	rep(i, a){
		rep(j, b){
			cin>> v[i][j];
		}
	}

	for(int i1=0;i1<a;i1++){
		for(int j1=0;j1<b;j1++){
			for(int i2=i1+1;i2<a;i2++){
				for(int j2=j1+1;j2<b;j2++){
					if(v[i1][j1]+v[i2][j2]>v[i2][j1]+v[i1][j2]){
						cout<< "No" <<endl;
						return 0;
					}
				}
			}
		}
	}

	cout<< "Yes" << endl;
 
	return 0;
}