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

string tob(LLi n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    return r;
}

int main(){

	LLi n, l, r, tmp, ans=0, al, ar;
	string s;
	cin>> n >> l >> r;

	s=tob(n);
	//cout<< s <<endl;

	for(LLi i=s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			tmp=1LL<<i;
			//cout<< i SP << tmp <<endl;
			al=tmp;
			ar=tmp-1+tmp;
			ans+=max(0LL, min(r, ar)-max(l, al)+1);
			//cout<< ans <<endl;
		}
	}

	cout<< ans <<endl;

	return 0;
}