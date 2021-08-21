#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int bat(int x, int y){
	if((x+1)%3==y) return x;
	else return y;
}

int main(){

	int n, k;
	char tmp;
	string te="RSP";
	vector< vector<int> > v;

	cin>> n >> k;
	v.resize(k+1);
	v[0].resize(n);

	rep(i, n){
		cin >> tmp;
		if(tmp=='R') v[0][i]=0;
		else if(tmp=='S') v[0][i]=1;
		else v[0][i]=2;
	}

	//rep(j, n) cout<< v[0][j] <<" ";
	//cout<< endl;

	rep(i, k) {
		for(int j=0;j<n*n;j+=2){
			v[i+1].push_back(bat(v[i][j%n], v[i][(j+1)%n]));
		}
		//rep(j, (int)v[i].size()) cout<< v[i+1][j] <<" ";
		//cout<< endl;
	}

	cout<< te[v[k][0]] << endl;
 
	return 0;
}