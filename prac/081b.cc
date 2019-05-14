#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

int main(){

	int n, flag;
	int sum=0;
	vector<int> a;

	cin>> n;

	a.resize(n);

	for(int i=0;i<n;i++) cin>> a[i];

	while(1){
		flag=0;
		//for(int j=0;j<n;j++) cout<< a[j] << " " << endl;
		for(int i=0;i<n;i++){
			if(a[i]%2==0)	{
				a[i]/=2;
			}else{
				flag=1;
				break;
			}
		}
		if(flag==0){
			sum++;
			continue;
		}
		break;
	}

	cout<< sum << endl;

}
/*
struct xxxx{
	int x;
	int y;
	int num;

	bool operator<(const xxxx &in) const{
		return num<in.num;
	};
};
*/
