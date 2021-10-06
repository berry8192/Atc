#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(){

	int n, lw, lb=0, rw=0, rb=0, mi, flag=2;
	string s;
	vector<int> fb, v;

	cin>> n;
	cin>> s;

	if(s[0]=='.') fb.emplace_back(0);

	for(int i=0;i<n;i++){
		if(s[i]=='#'){
			rb++;
			if(flag!=1) fb.emplace_back(i);
			flag=1;
		}else{
			rw++;
			if(flag!=0) fb.emplace_back(i);
			flag=0;
		}
	}

	/*cout<< rb << " " << rw << endl;
	for(int i=0;i<fb.size();i++) cout<< fb[i] << endl;
	cout<< endl;*/

	mi=min(rb, rw);
	if(!fb.empty()) lw=fb[0];
	rw-=lw;

	for(int i=0;i<fb.size()-1;i++){
		if(fb.size()<2) break;
		if(i%2==0){
			rb-=fb[i+1]-fb[i];
			lb+=fb[i+1]-fb[i];
		}else{
			
			rw-=fb[i+1]-fb[i];
			lw+=fb[i+1]-fb[i];
		}
		v.emplace_back(lb+rw);
		//cout<< v[i] << endl;
	}

	for(int i=0;i<v.size();i++){
		if(v.size()==0) break;
		mi=min(mi, v[i]);
	}

	cout<< mi << endl;


}
