#include <iostream>
#include <vector>

using namespace std;

int main(){
  int t;
  cin>> t;
  int n;

  for(int lp=0;lp<t;lp++){
  	cin>> n;
  	vector<int> v(n);
  	for(int i=0;i<n;i++){
	  cin>> v[i];
  		v[i]--;
  	}
  	
  	int ans=0;
  	for(int i=0;i<n;i++){
  		int flag=1;
  		for(int j=i+1;j<n;j++){
  			if(v[i]>v[j]) flag=0;
  		}
  		if(flag) ans++;
  	}

  	cout<< ans <<endl;
  	}
  		

  return 0;
}
