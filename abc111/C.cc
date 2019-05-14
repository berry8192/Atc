#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, ofi=0, efi=0, oma=0, ema=0, oma2=0, ema2=0;
	vector<int> v, vo(100002, 0), ve(100002, 0);

	cin>> n;
	v.resize(n);
	for(int i=0;i<n;i++){
		cin>> v[i];
		if(i%2==1){
			ve[v[i]]++;
		}else{
			vo[v[i]]++;
		}
	}

	for(int i=0;i<100002;i++){
		if(oma<=vo[i]){
			oma2=oma;
			oma=vo[i];
			ofi=i;
		}else if(oma2<=vo[i]){
			oma2=vo[i];
		}

		if(ema<=ve[i]){
			ema2=ema;
			ema=ve[i];
			efi=i;
		}else if(ema2<=ve[i]){
			ema2=ve[i];
		}
	}

	//cout<< oma2 << " " << oma << " " << ofi2 << " " << ofi << endl;
	//cout<< ema2 << " " << ema << " " << efi2 << " " << efi << endl;

	if(ofi!=efi){
		cout<< n-oma-ema << endl;
	}else{
		cout<< min(n-oma-ema2, n-oma2-ema) << endl;
	}

}
