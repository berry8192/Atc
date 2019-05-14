#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

int main(){

	int n, ab=0, a=0, b=0, ba=0, ans;
	string s;

	cin>> n;

	for(int i=0;i<n;i++){
		cin>> s;
		for(int j=0;j<s.size()-1;j++){
			if(s.substr(j, 2)=="AB") ab++;
		}

		if(s[0]=='B' && s[s.size()-1]=='A'){
			ba++;
		}else{
			if(s[s.size()-1]=='A') a++;
			if(s[0]=='B') b++;
		}
	}

	//cout<< ab << " " << a << " " << b << " " << ba << endl;

	ans=ab;
	ans+=max(0, ba-1);

	if(1<=ba){
		if(1<=a){
			ans++;
			a--;
		}
		if(1<=b){
			ans++;
			b--;
		}
	}

	ans+=min(a, b);	

	cout<< ans << endl;
/*
	for(int i=0;i<v.size();i++) cout<< v[i] << endl;

	cout<< n << endl;
	cout<< v[0] << " " << v[1] << endl;*/


}
