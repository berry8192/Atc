#include <iostream>
#include <string>

using namespace std;

int main(){
  int n, f=1;
  cin>> n;
  string s;
  cin>> s;
  
  for(int i=0;i<n;i++){
  	if(s[i]=='"'){
  		f=1-f;
  	}
  	if(f && s[i]==','){
  		s[i]='.';
  	}
  }

  cout<<s<<endl;

  return 0;
}
