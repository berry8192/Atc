#include <bits/stdc++.h>
#include <string>

using namespace std;

int main(){

	int max=0;
	int l=0;
	string s, str;
	cin>> s;

	for(int i=0;i<s.size();i++){
		str=s.substr(i, 1);
		if(str=="A" || str=="C" || str=="T" || str=="G"){
			l++;
		}else{
			if(max<l) max=l;
			l=0;
		}
	}

	if(max<l) max=l;

	cout<< max << endl;


}
