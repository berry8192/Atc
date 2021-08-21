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

	LLi k, ans=0, sz;
	string s;
	vector< vector<int> > v;

	cin>> s >> k;

	sz=s.size();

	v.resize(sz+1);
	rep(i, sz+1) v[i].resize(26, -1);

	rep(i, sz) {
		int tmp=(int)(s[i+1]-'a');
		v[i+1][tmp]=i+1;
		for(int j=i;j>=0;j--){
			if(v[j][tmp]!=-1) break;
			v[j][tmp]=i+1;
		}
	}

	/*rep(i, sz+1){
		rep(j, 26){
			cout<< v[i][j] << " ";
		}
		cout<< endl;
	}*/

	cout<< "No" << endl;
 
	return 0;
}