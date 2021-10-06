#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, l, k, bl, br, bm;
  vector<int> v, w;

  cin>> n >> l >> k;
  
  v.resize(n+2);
  w.resize(n+2);
  for(int i=1;i<=n;i++){
  	cin>> v[i];
  }
  v[0]=0;
  v[n+1]=l;
  for(int i=0;i<n+1;i++){
  	w[i]=v[i+1]-v[i];
  	//cout<< w[i] <<endl;
  }
  
  br=1000000001;
  bl=0;
  while(br-bl>1){
  	bm=(br+bl)/2;
  	int sep=0, tmp=0;
  	for(int i=0;i<=n;i++){
  		tmp+=w[i];
  		if(bm<=tmp){
  			sep++;
  			tmp=0;
  		}
  	}
  		if(k<sep) bl=bm;
  		else br=bm;
  }

  cout<< bl <<endl;

  return 0;
}
