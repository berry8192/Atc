#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(){

	int n, w=0, b=0, mi, flag=2, fc;
	string s;
	vector<int> fb, v;

	cin>> n;
	cin>> s;

	if(s[0]=='#'){
		fc=1;
	}else{
		fc=0;
	}

	for(int i=0;i<n;i++){
		if(s[i]=='#'){
			b++;
			if(flag!=1) fb.emplace_back(i);
			flag=1;
		}else{
			w++;
			if(flag!=0) fb.emplace_back(i);
			flag=0;
		}
	}

	v.resize(fb.size());
	v[0]=w;

	if(fc==1){
		for(int i=1;i<fb.size();i+=2){
			v[i]=v[i-1]-(fb[i]-fb[i-1]);
		}
	}else{
		for(int i=2;i<fb.size();i+=2){
			v[i]=v[i-1]-(fb[i]-fb[i-1]);
		}
	}

	mi=min(w, b);
	for(int i=0;i<v.size();i++){
		mi=min(mi, v[i]);
	}

	cout<< mi << endl;


}
