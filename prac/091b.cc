#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, m;
	int max=0;
	int count=1;
	vector<string> s, t;

	cin>> n;
	s.resize(n);
	for(int i=0;i<n;i++) cin>> s[i];
	cin>> m;
	t.resize(m);
	for(int i=0;i<m;i++) cin>> t[i];

	sort(s.begin(), s.end());
	sort(t.begin(), t.end());

	s.emplace_back("1");

	//for(int i=0;i<n+1;i++) cout<< "  " << s[i] << endl;

	for(int i=0;i<n;i++){
		if(s[i]==s[i+1]){
			count++;
		}else{
			for(int j=0;j<m;j++){
				if(s[i]==t[j]) count--;
			}
			if(max<count) max=count;
			count=1;
		}
	}

	cout<< max << endl;


}
