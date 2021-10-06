#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	long long int a, b, c, k;
	cin>> a >> b >> c >> k;

	if(k<=a) cout<< k << endl;
	else if(k<=a+b) cout<< a << endl;
	else cout<< a-(k-a-b) <<endl;
 
	return 0;
}