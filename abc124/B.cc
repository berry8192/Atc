#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int n, cnt=0, flag;
	vector<int> v;

	cin>> n;

	v.resize(n);
	for(int i=0;i<n;i++){
		cin>> v[i];
		flag=0;
		for(int j=0;j<i;j++){
			if(v[i]<v[j]){
				flag=1;
				break;
			}
		}
		if(flag==0) cnt++;
	}

	cout<< cnt << endl;


}
