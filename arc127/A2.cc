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

	LLi n, sz, ans=0, ten;
	vector<LLi> tmp={0, 1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111, 11111111111, 111111111111, 1111111111111, 11111111111111, 111111111111111};
	cin>> n;

	sz=to_string(n).size();
	//先頭の1の個数
	for(int i=1;i<=15;i++){
		cout<< "i=" << i <<endl;
		//cout<< tmp[i] <<endl;
		//全体の桁数
		for(int j=i;j<=sz;j++){
			cout<< " k=" << sz-j <<endl;
			ten=1;
			rep(k, sz-j) ten*=10;
			cout<< "  n= " << (tmp[i]+1)*ten-1 SP << tmp[i]*ten <<endl;
			ans+=i*max(min((tmp[i]+1)*ten-1, n)-tmp[i]*ten+1, 0LL);
			cout<< "  ans=" << ans <<endl;

		}
	}
	
	cout<< ans << endl;
 
	return 0;
}