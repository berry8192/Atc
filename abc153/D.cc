#include <iostream>

using namespace std;

int main(){
  long long int h, n=1, ans=0;

  cin>> h;

  while(1){
    if(h>1){
      h/=2;
      ans+=n;
      n*=2;
    }else{
      ans+=n;
      break;
    }
  }

  cout<< ans <<endl;

  return 0;
}

