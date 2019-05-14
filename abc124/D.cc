#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(){

	int n, k, sz, flag=0;
	vector<int> p, l;
	string s;

	cin>> n >> k;

	cin>> s;

	sz=s.size();

	for(int i=0;i<=sz;i++){
		if(s.substr(i, 1)=="0"){
			if(flag!=1){
				p.emplace_back(i);
				flag=1;
			}
		}else{
			flag=0;
		}
	}
		//for(int i=0;i<p.size();i++) cout<< p[i] << endl;

	if(p.size()<=k){
		cout<< sz << endl;
		return 0;
	}

	p.insert(p.begin(), 0);
	p.insert(p.end(), 0);

	int len, ma=0;
	
	for(int i=1;i<p.size()-k+1;i++){
		len=p[i+k+1]-p[i];
		ma=max(ma, len);
	}

	//cout<< s.substr(i, 1) <<endl;
	//cout<< cnt << " " << sz << " " << sz-cnt << endl;

	cout<< ma << endl;


}
