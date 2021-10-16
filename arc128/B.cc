#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	vector<int> v(3);
	LLi ans, tmp, t;

	cin>> t;

	rep(i, t){
		cin>> v[0] >> v[1] >> v[2];
		sort(all(v));
		ans=0;

		if((v[1]-v[0])%3==0){
			
		}else if((v[2]-v[1])%3==0){
			tmp=v[0];
			v[0]=v[1];
			v[1]=v[2];
			v[2]=v[0];
		}else if((v[2]-v[0])%3==0){
			//cout<< "#" ;
			swap(v[1], v[2]);
		}else{
			cout<< -1 <<endl;
			continue;
		}
		ans+=(v[1]-v[0])/3;
		tmp=v[0]+ans*2;
		ans+=tmp;

		cout<< ans <<endl;
	}
 
	return 0;
}