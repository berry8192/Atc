#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

int main(){

	int n, lt, mi=9999;
	vector<int> c, t;

	cin>> n >> lt;
	c.resize(n);
	t.resize(n);

	for(int i=0;i<n;i++){
		cin>> c[i] >> t[i];
		if(t[i]<=lt) mi=min(mi, c[i]);
	}

	if(mi==9999){
		cout<< "TLE" << endl;
	}else{
		cout<< mi << endl;
	}


}
