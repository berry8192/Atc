#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, m, ans=0;
  cin>> n >> m;
  vector<string> a(n);
  
  for(int i=0;i<n;i++) cin>> a[i];
  for(int i=0;i<n;i++){
  	for(int j=i+1;j<n;j++){
  	  int flag=1;
  	  for(int k=0;k<m;k++){
  	  	flag*=(a[i][k]=='o')+(a[j][k]=='o');
  	  }
  	  if(flag) ans++;
  	}
  }

  cout<<ans<<endl;

  return 0;
}
