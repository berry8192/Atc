#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  
  int n, k;
  long long int ans=0;
  vector<int> h;

  cin>> n >> k;

  h.resize(n);
  
  for(int i=0;i<n;i++) cin>> h[i];
  
  sort(h.begin(), h.end());
  
  for(int i=0;i<n-k;i++) ans+=h[i];
  
  cout<< ans <<endl;

  return 0;
}
