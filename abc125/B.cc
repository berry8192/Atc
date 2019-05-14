#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int n, sco=0;
	vector<int> v, c;

	cin>> n;
	v.resize(n);
	c.resize(n);

	for(int i=0;i<n;i++) cin>> v[i];
	for(int i=0;i<n;i++){
		cin>> c[i];
		if(c[i]<v[i]) sco+=v[i]-c[i];
	}

	cout<< sco << endl;

}
