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

	int n, ans=0, val;
	set<string> s, sd;
	string tmp, t2;

	cin>> n;

	rep(i, n){
		cin >> tmp;
		if(tmp[0]=='!'){
			t2=tmp.substr(1);
			decltype(s)::iterator it = s.find(t2);
			if (it != s.end()) {
    			// 発見した
    			cout << t2 << endl;
				return 0;
  			}
			sd.insert(t2);
		}else{
			decltype(sd)::iterator it = sd.find(tmp);
			if (it != sd.end()) {
    			// 発見した
    			cout << tmp << endl;
				return 0;
  			}
			s.insert(tmp);
		}
	}

	cout<< "satisfiable" << endl;
 
	return 0;
}