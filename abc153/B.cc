#include <iostream>

using namespace std;

int main(){
  int h, n, a=0, tmp;

  cin>> h >> n;
  
  for(int i=0;i<n;i++){
    cin>> tmp;
    a+=tmp;
  }

  if(h<=a) cout<< "Yes" <<endl;
  else cout<< "No" <<endl;
  
  return 0;
}



