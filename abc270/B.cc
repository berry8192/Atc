#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n,y,z,ans=99999999;
  vector<int> v;

  cin>> n>>y>>z;
  
  if(n*y>0){
  	if(abs(n)<abs(y)){
  		ans=abs(n);
  	}else{
  		if(z*y>0){
  			if(abs(z)<abs(y)){
  				ans=abs(n);
  			}else{
  				ans=-1;
  			}
  		}else{
  			ans=abs(z)*2+abs(n);
  		}
  	}
  }else{
  	ans=abs(n);
  }
  
  cout<< ans <<endl;

  return 0;
}
