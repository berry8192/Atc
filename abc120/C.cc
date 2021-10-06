#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){

	string s;
	int m=0;
	int c=0;

	cin>> s;

	for(int i=0;i<(int)s.size();i++){
    		if(s[i]=='0'){
			//red
			if(c<0) m+=2;
			c++;
		}else{
			//blue
			if(0<c) m+=2;
			c--;
		}
	}

	cout<< m << endl;

}
