#include <iostream>
#include <vector>

using namespace std;


int fn(int n){
	if(n%2==0){
		return n/2;
	}else{
		return 3*n+1;
	}
}

int main(){

	int s;
	int flag=0;
	vector<int> a(1);

	cin>> s;
	a[0]=s;

	for(int i=1;i<1000000;i++){
		a.emplace_back(fn(a[i-1]));
		//cout<< a[i-1] << "\n";
		for(int j=0;j<i;j++){
			if(a[i]==a[j]){
				cout<< i+1 << "\n";
				flag=1;
				break;
			}
		}

		if(flag==1) break;
	}

}
