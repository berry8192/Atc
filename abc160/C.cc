#include <bits/stdc++.h>

using namespace std;

int main(){

	int k, n, mi=0;
	vector<int> v;

	cin>> k >> n;
	v.resize(n);
	for(int i=0;i<n;i++) cin>> v[i];

	v.emplace_back(v[0] + k);

	for (int i = 0;i < n;i++) {
		mi = max(mi, v[i + 1] - v[i]);
		//cout << v[i + 1] - v[i] << endl;
	}

	cout<< k-mi << endl;

	return 0;
}
