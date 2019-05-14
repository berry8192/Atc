#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, flag, sum;
	vector<int> o(3), oc(3), om(3, 10000);
	vector<int> l;

	cin>> n >> o[0] >> o[1] >> o[2];

	l.resize(n);

	for(int i=0;i<n;i++) cin>> l[i]; 

	sort(l.begin(), l.end());

	for(int j=0;j<3;j++){
		flag=0;
		for(int i=0;i<n;i++){
			if(abs(l[i]-o[j])<10){
				flag=1;
				if(abs(l[i]-o[j])<om[j]){
					om[j]=abs(l[i]-o[j]);
					oc[j]=i;
				}
			}
		}
		if(flag==1){
			l[oc[j]]=0;
			sum+=om[j];
		}
	}

	for(int j=0;j<3;j++){
		flag=0;
		for(int i=0;i<n;i++){
		for(int i2=0;i2<n;i++){
			if(abs(l[i]+l[i2]-o[j])<10){
				flag=1;
				if(abs(l[i]+l[i2]-o[j])<om[j]){
					om[j]=abs(l[i]+l[i2]-o[j]);
					oc[j]=i;
				}
			}
		}}
		if(flag==1){
			l[oc[j]]=0;
			sum+=om[j];
		}
	}

	cout<< sum << "\n";;

}
