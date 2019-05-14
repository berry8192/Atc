#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cmath>
 
using namespace std;
 
int main(){
 
	int n, w=0, b=0, mi;
	string s;
	vector<int> v;
 
	cin>> n;
	cin>> s;
 
	v.resize(n);
 
	for(int i=0;i<n;i++){
		if(s[i]=='#'){
			b++;
			for(int j=0;j<=i;j++) v[j]++;
		}else{
			w++;
			for(int j=i;j<n;j++) v[j]++;
		}
	}
 
	mi=min(w, b);
	for(int i=0;i<n;i++){
		mi=min(mi, v[i]);
	}
 
	cout<< mi << endl;
 
 
}
