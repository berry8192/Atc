#include <iostream>
#include <vector>
#include <string>

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

	int x1, x2, x, y;
	string s;
	cin>> s;

	x1=(int)(s[0]-'0');
	if(s[1]!='.'){
		x2=(int)(s[1]-'0');
		x=x1*10+x2;
	}else{
		x=x1;
	}
	y=(int)(s[s.size()-1]-'0');

	if(y<=2) cout<< x << "-" <<endl;
	else if(y<=6) cout<< x << endl;
	else cout<< x << "+" <<endl;
 
	return 0;
}