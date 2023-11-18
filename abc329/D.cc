#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
  int n, m, tmp, ma=1;
  cin>> n >> m;
  vector<set<int>> v(m+1);
  vector<int> inv(n+1);
  
  for(int i=0;i<m;i++){
  	cin>> tmp;
  	v[inv[tmp]].erase(tmp);
  	inv[tmp]++;
  	v[inv[tmp]].insert(tmp);
  	ma=max(ma, inv[tmp]);
  	cout<< *v[ma].begin() <<endl;
  	}
  return 0;
}
