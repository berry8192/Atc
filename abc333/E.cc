#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n, hav=0, ma=0;
  vector<int> v, x, ans, por;

  cin>> n;
  
  v.resize(n);
  x.resize(n);
  por.resize(n);
  ans.resize(n);
  for(int i=0;i<n;i++){
  	cin>> v[i] >> x[i];
  	x[i]--;
  }

  reverse(v.begin(), v.end());
  reverse(x.begin(), x.end());
  
  for(int i=0;i<n;i++){
  	if(v[i]==1){
  		if(por[x[i]]>0){
  			ans[i]=1;
  			por[x[i]]--;
  			hav--;
  		}
  	}else{
  		por[x[i]]++;
  		hav++;
  		ma=max(ma, hav);
  	}
  }
  
  for(int i=0;i<n;i++){
  	if(por[i]>0){
  		cout<< -1 <<endl;
  		return 0;
  	}
  }
  
  reverse(v.begin(), v.end());
  reverse(ans.begin(), ans.end());
  
  cout<< ma <<endl;
  for(int i=0;i<n;i++){
  		if(v[i]==1) cout<< ans[i] <<endl;
  }

  return 0;
}
