#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, tmp, flag;
	vector<string> v;
	vector< vector<int> > bo;
	vector<char> s;

	cin>> n;
	v.resize(n);
	bo.resize(n);
	s.resize(n);
	rep(i, n) bo[i].resize(26);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		rep(j, n){
			tmp=(int)(v[i][j]-'a');
			bo[i][tmp]=1;
		}
	}

	rep(i, (n+1)/2){
		flag=0;
		rep(j, 26){
			//cout<< bo[i][j] << " " << bo[i][n-j-1] <<endl;
			if(bo[i][j]==1 && bo[n-i-1][j]==1){
				flag=1;
				s[i]=(char)(97+j);
				s[n-i-1]=(char)(97+j);
			}
		}
		if(flag==0){
			cout<< "-1" <<endl;
			return 0;
		}
	}

	rep(i, n) cout<< s[i];
	cout<< endl;
 
	return 0;
}