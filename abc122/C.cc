#include <bits/stdc++.h>
#include <string>
#include <vector>

using namespace std;

int main(){

	int n, q, cnt;
	int max=0;
	vector<int> x, l, r;
	string s, che;

	cin>> n >> q;
	cin>> s;

	x.resize(s.size()-1);
	l.resize(q);
	r.resize(q);

	for(int i=0;i<q;i++) cin>> l[i] >> r[i];

	for(int i=0;i<s.size()-1;i++){
		che=s.substr(i, 2);
		if(che=="AC"){
			x[i]=1;
			max++;
		}else{
			x[i]=0;
			//if(che.substr(1, 1)!="A") i++;
		}
	}

	/*for(int i=0;i<x.size();i++) cout<< x[i];
	cout<< endl;*/

	for(int i=0;i<q;i++){
		cnt=0;

		if(r[i]-l[i]>50000){
			cnt=max;
			for(int j=0;j<l[i]-1;j++) cnt-=x[j];
			for(int j=r[i]-1;j<x.size();j++) cnt-=x[j];
		}else{
			for(int j=l[i]-1;j<r[i]-1;j++){
				cnt+=x[j];
				//cout<< x[j];
			}
		}

		cout<< cnt << endl;
	}

}
