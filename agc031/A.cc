#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){

	int n, count;
	int ma=0;
	string s;
	vector<string> al;
	vector<int> p(1, 0), q(27, 0);

	cin>> n;
	cin>> s;
	al.resize(n);

	for(int i=0;i<n;i++) al[i]=s.substr(i, 1);

	sort(al.begin(), al.end());

	for(int i=1;i<n;i++){
		p[ma]++;
		if(al[i-1]!=al[i]){
			ma++;
			p.emplace_back(0);
		}
	}
	p[ma]++;

	q[1]=p.size();
	count=n;

	for(int i=2;i<p.size();i++){
		

	for(int i=0;i<n;i++) cout<< al[i];
	cout<< endl;
	for(int i=0;i<p.size();i++) cout<< p[i] << " ";
	cout<< endl;


}
