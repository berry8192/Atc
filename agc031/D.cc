#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>

using namespace std;

int main(){

	int n, k;
	vector<int> p, q, r;

	cin>> n >> k;
	p.resize(n);
	q.resize(n);
	r.resize(n);

	for(int i=0;i<n;i++) cin>> p[i];
	for(int i=0;i<n;i++) cin>> q[i];

	for(int i=2;i<k;i++){
		for(int j=0;j<n;j++){
			r[p[j]-1]=q[j];
		}

		for(int j=0;j<n;j++){
			//cout<< r[j] << q[j] << p[j] << endl;
			p[j]=q[j];
			q[j]=r[j];
		}

		//cout<< endl;
	}

	for(int i=0;i<n;i++) cout<< r[i] << " ";
	cout<< endl;

}
