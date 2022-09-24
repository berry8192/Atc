#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, b;
  vector<int> v;

  cin>> n>>b;
  
  v.resize(n);

  cout<< (n|b) <<endl;

  return 0;
}
