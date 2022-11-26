#include <iostream>
#include <string>

using namespace std;

int main(){
  int n=0;
  string s;

  cin>> s;
  
  for(int i=0;i<s.size();i++){
  	n+=int(s[i]-'u');
  }

  cout<< n <<endl;

  return 0;
}
