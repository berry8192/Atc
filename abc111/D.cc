#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n;
	vector<int> v;

	cin>> n;
	v.resize(n);
	for(int i=0;i<n;i++) cin>> v[i];

	for(int i=0;i<n.end();i++) cout<< v[i] << endl;

	cout<< n << endl;
	cout<< v[0] << " " << v[1] << endl;


}
