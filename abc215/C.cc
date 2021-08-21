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

	int n, ans=0;
	string s, sv, tmp;
	vector<int> v;
	set<string> st;

	cin>> s >> n;

	rep(i, s.size()){
		v.push_back(i);
	}

	rep(i, s.size()){
		sv.push_back(s[i]);
	}
	sort(sv.begin(), sv.end());

	do {
		tmp="";
		rep(i, s.size()){
			tmp+=sv[v[i]];
		}
		//cout<< tmp <<endl;
		if(st.count("tmp")==0){
			st.insert(tmp);
			if(st.size()==n){
				cout<< tmp <<endl;
				return 0;
			}
		}
	} while (next_permutation(all(v)));

	return 0;
}