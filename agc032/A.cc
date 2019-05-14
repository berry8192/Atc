#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int flag=0;
vector<int> b;

void sol(vector<int> a, vector<int> c, int j){
	if(flag==1) return;
	for(int i=j;i<a.size();i++) a[i]=a[i+1];
	a.pop_back();
	c.emplace_back(j);

	if(a.size()==1){
		for(int i=n-1;i>=0;i--) cout<< c[i] << endl;
		flag=1;
		return;
	}

	for(int i=1;i<n;i++){
		if(a[i]==i) sol(a, c, i);
	}
}

int main(){

	vector<int> a, c;

	cin>> n;
	a.resize(1);
	a[0]=0;
	b.resize(n);

	for(int i=1;i<=n;i++){
		cin>> b[i];
		if(b[i]>i){
			cout<< "-1" << endl;
			return 0;
		}
	}

	//a.insert(j, j);
	//a.erase();
	for(int i=1;i<=n;i++){
		if(b[i]==i) sol(b, c, i);
	}

}
