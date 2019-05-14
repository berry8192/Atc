#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

int calc(vector<int> v, int nu){
	v.erase(v.begin() + nu);

	for(int i=1;i<v.size();i++){
	//cout <<"EE "<< i << v.size() <<endl;
		v[i]=gcd(v[i], v[i-1]);
		if(v[i]==1) return 1;
	}

	return v[v.size()-1];
}

int main(){

	int n, ma=0;
	vector<int> v;

	cin>> n;
	v.resize(n);
	for(int i=0;i<n;i++) cin>> v[i];

	sort(v.begin(), v.end());

	for(int i=n-1;1<i;i--){
		if(v[i]==v[i-2]) v.erase(v.begin() + i-1);
	}

	if(v.size()==1){
		cout<< v[0] << endl;
		return 0;
	}

	if(v.size()==2){
		cout<< max(v[0], v[1]) << endl;
		return 0;
	}

	for(int i=0;i<v.size();i++){
		ma=max(ma, calc(v, i));
		//cout<<"cal"<<endl;
	}

	//for(int i=0;i<v.size();i++) cout<< v[i] << endl;

	cout<< ma << endl;
	//cout<< v[0] << " " << v[1] << endl;


}
