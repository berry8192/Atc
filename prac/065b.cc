#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main(){

	int n, p;
	int count=1;
	int flag=0;
	vector<int> a;

	cin>> n;
	a.resize(n+1);
	a[0]=1;

	for(int i=1;i<n+1;i++) cin>> a[i];

	p=0;
	for(int i=0;i<100002;i++){
		//cout<< p << " " << a[p] << endl;
		p=a[p];
		if(i==100001){
			count=-1;
			flag=1;
		}else if(a[p]==2) flag=1;
		if(flag==1) break;
		count++;
		//a[p]=-1;
	}

	cout<< count << endl;

}
