#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

int ci(char s){

	if(s=='a') return 0;
	if(s=='b') return 1;
	if(s=='c') return 2;
	if(s=='d') return 3;
	if(s=='e') return 4;
	if(s=='f') return 5;
	if(s=='g') return 6;
	if(s=='h') return 7;
	if(s=='i') return 8;
	if(s=='j') return 9;
	if(s=='k') return 10;
	if(s=='l') return 11;
	if(s=='m') return 12;
	if(s=='n') return 13;
	if(s=='o') return 14;
	if(s=='p') return 15;
	if(s=='q') return 16;
	if(s=='r') return 17;
	if(s=='s') return 18;
	if(s=='t') return 19;
	if(s=='u') return 20;
	if(s=='v') return 21;
	if(s=='w') return 22;
	if(s=='x') return 23;
	if(s=='y') return 24;
	if(s=='z') return 25;

	cout<< "ci error" <<endl;
}

int main(){

	int tmpt, tmps;
	string s, t;
	vector<int> tc(26, 0), sc(26, 0);

	cin>> s >> t;

	for(int i=0;i<t.size();i++){
		tmpt=ci(t[i]);
		tmps=ci(s[i]);

		if(tc[tmpt]==0){
			tc[tmpt]=26+tmpt-ci(s[i]);
		}else{
			if(tc[tmpt]!=26+tmpt-ci(s[i])){
				cout<< "No" << endl;
				return 0;
			}
		}
		if(sc[tmps]==0){
			sc[tmps]=26+tmps-ci(t[i]);
		}else{
			if(sc[tmps]!=26+tmps-ci(t[i])){
				cout<< "No" << endl;
				return 0;
			}
		}
	}

	cout<< "Yes" << endl;


}
