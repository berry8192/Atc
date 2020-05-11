#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int a, b, c;
	cin>> a >> b >> c;
	string s;
	cin>> s;

	if(s=="ABC") cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}