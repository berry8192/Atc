#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int main(){

	int a, b, q;
	long long int sb, sn, tb, tn;
	vector<long long int> mi(6);
	vector<long long int> s, t, x;

	cin>> a >> b >> q;

	s.resize(a);
	t.resize(b);
	x.resize(q);

	for(int i=0;i<a;i++) cin>> s[i];
	for(int i=0;i<b;i++) cin>> t[i];
	for(int i=0;i<q;i++) cin>> x[i];

for(int p=1;p<=q;p++){

	for(int i=1;i<a;i++){
		if(x[p]<s[0]){
			sb=-1000000000000;
			sn=s[0];
		}
		if(s[a-1]<x[p]){
			sn=1000000000000;
			sb=s[a-1];
		}
		if((s[i]-x[p])*(s[i-1]-x[p])<=0){
			sb=s[i-1];
			sn=s[i];
			if((s[i]-x[p])*(s[i-1]-x[p])==0) sb=s[i];
			i=a;
		}
	}

	for(int i=1;i<b;i++){
		if(x[p]<t[0]){
			tb=-1000000000000;
			tn=t[0];
		}
		if(t[b-1]<x[p]){
			tn=1000000000000;
			tb=t[b-1];
		}
		if((t[i]-x[p])*(t[i-1]-x[p])<=0){
			tb=t[i-1];
			tn=t[i];
			if((t[i]-x[p])*(t[i-1]-x[p])==0) tb=t[i];
			i=b;
		}
	}

	if(tb<=sb) mi[0]=abs(x[p]-tb);
	if(sb<tb) mi[0]=abs(x[p]-sb);
	if(tn<=sn) mi[1]=abs(x[p]-sn);
	if(sn<tn) mi[1]=abs(x[p]-tn);
	mi[2]=abs(x[p]-tb)*2+abs(x[p]-sn);
	mi[3]=abs(x[p]-sb)*2+abs(x[p]-tn);
	mi[4]=abs(x[p]-tn)*2+abs(x[p]-sb);
	mi[5]=abs(x[p]-sn)*2+abs(x[p]-tb);

	sort(mi.begin(), mi.end());

	cout<< mi[0] << "\n";

}

}
