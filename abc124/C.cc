#include <bits/stdc++.h>
#include <string>
#include <cmath>

using namespace std;

int main(){

	int cnt=0, sz;
	string s;

	cin>> s;

	sz=s.size();

	for(int i=0;i<sz;i++){
		if(i%2==0){
			if(s.substr(i, 1)=="0") cnt++;
		}else{
			if(s.substr(i, 1)=="1") cnt++;
		}
	//cout<< s.substr(i, 1) <<endl;
	}

	//cout<< cnt << " " << sz << " " << sz-cnt << endl;

	cnt=min(sz-cnt, cnt);

	cout<< cnt << endl;


}
