#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
  int n, ans=0;
  string s;

  cin>> n;
  cin>> s;
  vector<int> ma(26), len(26);
  
  for(int i=0;i<n;i++){
  	for(int j=0;j<26;j++){
  	  if(s[i]=='a'+j) len[j]++;
  	  else len[j]=0;
  	  ma[j]=max(ma[j], len[j]);
  	}
  }
  for(int i=0;i<26;i++) ans+=ma[i];

  cout<< ans <<endl;

  return 0;
}
