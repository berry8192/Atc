#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n;
	vector<string> v;

	cin>> n;
	v.resize(n);
	for(int i=0;i<n;i++) cin>> v[i];

	for(int i=1;i<v.size();i++){
		for(int j=0;j<i;j++){
			if(v[j]==v[i]){
				cout<< "No" << endl;
				return 0;
			}
		}
				
		//cout<< v[i-1][v[i-1].size()-1] << " " << v[i][0] << endl;
		if(v[i-1][v[i-1].size()-1]!=v[i][0]){
			cout<< "No" << endl;
			return 0;
		}
	}

	cout<< "Yes" << endl;


}
