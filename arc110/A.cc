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

void ac(string s){
	cout<< s <<endl;
	exit(0);
}

LLi gcdi(LLi a, LLi b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

LLi lcmi(LLi a, LLi b) {
    return a/gcdi(a, b)*b;
}

int main(){

	LLi n, ans=2;
	cin>> n;

	for(LLi i=1;i<=n;i++){
		ans=lcmi(ans, i);
	}
	ans++;

	cout<< ans <<endl;
 
	return 0;
}