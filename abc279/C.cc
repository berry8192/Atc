#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main(){
  int h, w;
  multiset<string> ss, tt;
  string s, t;
  cin>> h>>w;
vector<string> sss(w), ttt(w);
  
  for(int i=0;i<h;i++){
cin>> s;
for(int j=0;j<w;j++) sss[j]+=s[j];
}  
  for(int i=0;i<h;i++){
cin>> t;
for(int j=0;j<w;j++) ttt[j]+=t[j];
}

  for(int i=0;i<w;i++){
ss.insert(sss[i]);
}
  for(int i=0;i<w;i++){
tt.insert(ttt[i]);
}

  if(ss==tt) cout<< "Yes" <<endl;
  else cout<< "No" <<endl;

  return 0;
}


