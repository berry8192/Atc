#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int a, b;
	string s, t;
	cin>> s >> t;

	if(s.size()+1==t.size()){
		t.pop_back();
		if(s==t){
			cout<< "Yes" << endl;
			return 0;
		}
	}

	cout<< "No" << endl;
 
	return 0;
}