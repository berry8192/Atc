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

	int n, m, q, tmp, a, b, ans;
	vector<int> v;
	vector< vector<int> >s;

	cin>> n >> m >> q;
	v.resize(m+1, n);
	s.resize(n+1);

	rep(i, q){
		cin>> tmp;
		if(tmp==1){
			cin>> a;
			ans=0;
			for(int j=0;j<s[a].size();j++){
				ans+=v[s[a][j]];
			}
			cout<< ans <<endl;

		}else{
			cin>> a >> b;
			s[a].push_back(b);
			if(v[b]>0) v[b]--;
		}
	}
 
	return 0;
}