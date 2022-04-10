#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*  divisor(n)
    入力：整数 n
    出力：nのすべての約数
    計算量：O(√n)
*/
vector<long long> divisor(long long n) {
    vector<long long> ret;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    sort(ret.begin(), ret.end()); // 昇順に並べる
    return ret;
}

int main(){
  long long n, ans=0;
  vector<long long> v;

  cin>> n;
  
  v=divisor(n);
  //for(int i=0;i<v.size();i++) cout<< v[i] <<endl;

  for(int i=0;i<v.size();i++){
  	for(int j=i;j<v.size();j++){
  		if(n/v[i]/v[j]==0) continue;
  		if(v[j]>n/v[i]/v[j]) continue;
  		if(v[i]*v[j]*(n/v[i]/v[j])!=n) continue;
  		
  		auto lb=lower_bound(v.begin(), v.end(), v[i]*v[j]);
  		auto ub=upper_bound(v.begin(), v.end(), v[i]*v[j]);
  		if(ub-lb==0) continue;
  		
  		lb=lower_bound(v.begin(), v.end(), v[i]*n/v[i]/v[j]);
  		ub=upper_bound(v.begin(), v.end(), v[i]*n/v[i]/v[j]);
  		if(ub-lb==0) continue;
  		
  		lb=lower_bound(v.begin(), v.end(), n/v[i]/v[j]*v[j]);
  		ub=upper_bound(v.begin(), v.end(), n/v[i]/v[j]*v[j]);
  		if(ub-lb==0) continue;
  		
  		//cout<< v[i] << " " << v[j] << " " << n/v[i]/v[j] <<endl;
  		ans++;
  	}
  }
  
  cout<< ans <<endl;

  return 0;
}
