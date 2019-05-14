#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int a, b, c;
int mi=10000;
vector<int> l;

int cal(vector<int> v, int i, int n){
cout<< "        cal" << "\n";
	int mini=10000;

	for(int j1=0;j1<=v.size()-i;j1++){
	if(1<i){
	for(int j2=j1;j2<=v.size()-i;j2++){		
	if(2<i){
	for(int j3=j2;j3<=v.size()-i;j3++){
	if(3<i){
	for(int j4=j3;j4<=v.size()-i;j4++){
	if(4<i){
	for(int j5=j4;j5<=v.size()-i;j5++){
	if(5<i){
	for(int j6=j5;j6<=v.size()-i;j6++){
		if(abs(n-v[j1]-v[j2]-v[j3]-v[j4]-v[j5]-v[j6])+50<mini) mini=abs(n-v[j1]-v[j2]-v[j3]-v[j4]-v[j5]-v[j6])+50;
	}
	}else{
		if(abs(n-v[j1]-v[j2]-v[j3]-v[j4]-v[j5])+40<mini) mini=abs(n-v[j1]-v[j2]-v[j3]-v[j4]-v[j5])+40;
	}}
	}else{
		if(abs(n-v[j1]-v[j2]-v[j3]-v[j4])+30<mini) mini=abs(n-v[j1]-v[j2]-v[j3]-v[j4])+30;
	}}
	}else{
		if(abs(n-v[j1]-v[j2]-v[j3])+20<mini) mini=abs(n-v[j1]-v[j2]-v[j3])+20;
	}}
	}else{
		if(abs(n-v[j1]-v[j2])+10<mini) mini=abs(n-v[j1]-v[j2])+10;
	}}
	}else{
		if(abs(n-v[j1])<mini) mini=abs(n-v[j1]);
	}}

	return mini;
}

void judge(vector<int> aa, vector<int> bb, vector<int> cc){
cout<< "    judge" << "\n";
	int mina=10000;
	int minb=10000;
	int minc=10000;
	int calc;

	for(int i=1;i<=aa.size();i++){
		calc=cal(aa, i, a);
		if(calc<mina) mina=calc;
	}

	for(int i=1;i<=bb.size();i++){
		calc=cal(bb, i, b);
		if(calc<minb) minb=calc;
	}

	for(int i=1;i<=cc.size();i++){
		calc=cal(cc, i, c);
		if(calc<minc) minc=calc;
	}

	if(mina+minb+minc<mi) mi=mina+minb+minc;
}

void sol(int dep, vector<int> aa, vector<int> bb, vector<int> cc){
cout<< "sol " << dep << "\n";
	if(dep==0){
		if(aa.size()!=0 && bb.size()!=0 && cc.size()!=0) judge(aa, bb, cc);
	}else{
		sol(dep-1, aa, bb, cc);
		aa.emplace_back(l[dep-1]);
		sol(dep-1, aa, bb, cc);
		aa.erase(aa.end());
		bb.emplace_back(l[dep-1]);
		sol(dep-1, aa, bb, cc);
		bb.erase(bb.end());
		cc.emplace_back(l[dep-1]);
		sol(dep-1, aa, bb, cc);
	}
}

int main(){

	int n;
	vector<int> aa, bb, cc;

	cin>> n >> a >> b >> c;

	l.resize(n);

	for(int i=0;i<n;i++) cin>> l[i];

	sol(n, aa, bb, cc);
	
	cout<< mi << "\n";;

}
