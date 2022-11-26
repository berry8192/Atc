#include <iostream>
#include <string>

using namespace std;

int main(){
  string s, t;
  cin>> s>>t;
  
  if(t.size()>s.size()){
    cout<< "No"<<endl;
    return 0;
  }
  for(int i=0;i<s.size();i++){
  	if(s.substr(i, t.size())==t){
      cout<< "Yes" <<endl;
      return 0;
    }
  }

  cout<< "No" <<endl;

  return 0;
}


