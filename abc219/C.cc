#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, ans=0;
	string x;
	vector<string> v;
	vector< vector<int> > w;
	vector<int> pos(26);

	cin>> x;
	rep(i, 26) pos[int(x[i]-'a')]=i;
	//rep(i, 26) cout<< pos[i] SP;
	//cout<< endl;
	cin>> n;
	v.resize(n);
	w.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		rep(j, v[i].size()){
			w[i].push_back(pos[(int)(v[i][j]-'a')]);
		}
		//cout<< w[i] <<endl;
	}

	sort(w.begin(), w.end());

	rep(i, n){
		string tmp="";
		//cout<< i << "# " << w[i] <<endl;
		rep(j, w[i].size()){
			rep(k, 26){
				if(w[i][j]==pos[k]) tmp+='a'+k;
			}
		}
		cout<< tmp <<endl;
	}
 
	return 0;
}
/*
bcazyxwvutsrqponmlkjihgfed
5
a
ab
abc
ac
b
*/