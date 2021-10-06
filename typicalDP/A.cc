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
	set<int> st{0};
	vector<int> v;

	cin>> n;

	rep(i, n){
		cin >> tmp;

		v.clear();
		for(auto itr = st.begin(); itr != st.end(); ++itr) {
        	v.push_back(*itr+tmp);
		}

		for(int j=0;j<v.size();j++) st.insert(v[j]);
	}

	cout<< st.size() << endl;
 
	/*for(auto itr = st.begin(); itr != st.end(); ++itr) {
        cout<< *itr <<endl;
	}*/

	return 0;
}