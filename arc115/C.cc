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

	int n, tmp;
	vector<int> v={1};

	cin>> n;

	rep(i, n-1){
		tmp=i+2;
		int fsz;
		vector<LLi> f;
		set<int> st;
		for(LLi j=1;j*j<tmp;j++){
			if(tmp%j==0){
				f.push_back(j);
			}
		}
		fsz=f.size();
		if((int)sqrt(tmp)*(int)sqrt(tmp)==tmp) f.push_back((int)sqrt(tmp));//平方根が約数の場合
		rep(j, fsz) f.push_back(tmp/f[fsz-1-j]);
		rep(j, f.size()-1) st.insert(v[f[j]-1]);
		v.push_back(*st.rbegin()+1);
	}

	PV(v);
 
	return 0;
}