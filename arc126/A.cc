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

	LLi t, a, b, c, ans, tmp;
	cin>> t;

	rep(i, t){
		cin>> a >> b >> c;
		ans=0;
		//a=2, b=6, c=4
		b/=2;

		//6and4
		tmp=min(b, c);
		ans+=tmp;
		b-=tmp;
		c-=tmp;
		//cout<< "b " << b << "c " << c <<endl;

		//6and2
		tmp=min(b, a/2);
		ans+=tmp;
		a-=tmp*2;
		//cout<< "b " << b << "a " << a <<endl;

		//4and2
		tmp=min(c/2, a);
		ans+=tmp;
		a-=tmp;
		c-=tmp*2;
		//cout<< "c " << c << "a " << a <<endl;

		//4and2
		if(c==1 && a>=3){
			ans+=1;
			a-=3;
		}

		//2
		//cout<< "a " << a <<endl;
		ans+=a/5;

		cout<< ans <<endl;
	}
 
	return 0;
}