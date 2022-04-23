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

	int a, b, c, d, e, f, x;
	int p1=0, p2=0;
	cin>> a >> b >> c >> d >> e >> f >> x;

	rep(t, x){
		if(t%(a+c)<a) p1+=b;
		if(t%(d+f)<d) p2+=e;
	}

	if(p1<p2){
		cout<< "Aoki" <<endl;
	}else if(p2<p1){
		cout<< "Takahashi" <<endl;
	}else{
		cout<< "Draw" <<endl;
	}
 
	return 0;
}