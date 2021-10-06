#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n;
	int sco=0;
	vector<int> a;

	cin>> n;
	a.resize(n);

	for(int i=0;i<n;i++) cin>> a[i];

	sort(a.begin(), a.end());

	for(int i=0;i<n;i++){
		if(i%2==(n+1)%2){
			sco+=a[i];
		}else{
			sco-=a[i];
		}
	}

	cout<< sco << endl;


}
