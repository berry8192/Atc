#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, mi=1999999999, sig=0;
	long long int su=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	for(int i=0;i<n;i++){
		cin>> v[i];
		if(v[i]<0) sig++;
		v[i]=abs(v[i]);
		mi=min(mi, v[i]);
		su+=v[i];
	}

	if(sig%2==1) su=su-2*mi;

	cout<< su << endl;

}
