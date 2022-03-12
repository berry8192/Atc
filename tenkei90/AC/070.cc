#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n, a, b;
  long long ans=0;
  vector<int> x, y;

  cin>> n;
  
  x.resize(n);
  y.resize(n);
  for(int i=0;i<n;i++){
  	cin>> x[i] >> y[i];
  }

 sort(x.begin(), x.end());
 sort(y.begin(), y.end());
  
  auto itx=x.begin()+(n/2);
  auto ity=y.begin()+(n/2);
  a=*itx;
  b=*ity;
  
  for(int i=0;i<n;i++){
  	ans+=abs(x[i]-a);
  	ans+=abs(y[i]-b);
  }
  
  cout<< ans <<endl;

  return 0;
}
