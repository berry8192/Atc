#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

int main(){

	string s, t, tmp, tmp2;
	vector<string> sc, tc;

	cin>> s >> t;

	for(int i=0;i<t.size();i++){
		for(int j=0;j<tc.size();j++){
			tmp=t[i];
			tmp2=tc[j];
			if(tmp==tmp2){
				tmp=sc[j];
				if(tmp!=tmp2){
					cout<< "No" << endl;
					return 0;
				}
			}else{
				tmp=sc[j];
				if(tmp!=tmp2){
					cout<< "No" << endl;
					return 0;
				}
				tc.emplace_back(t[i]);
				sc.emplace_back(s[i]);
				break;
			}
		}
	for(int i=0;i<sc.size();i++) cout<< sc[i];
	cout<< endl;
	for(int i=0;i<tc.size();i++) cout<< tc[i];
	cout<< endl;
	cout<< endl;
	}

	cout<< "Yes" << endl;


}
