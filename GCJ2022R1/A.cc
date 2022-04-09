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
cout<<('0'<'A')<<endl;
	int t;
	cin>> t;
	rep(lp, t){
		string s, t;
		cin>> s;
		s+='0';
		int cnt=1;
		rep(i, s.size()){
			if(s[i]<s[i+1]){
				rep(j, cnt*2) t+=s[i];
				cnt=1;
			}else if(s[i]>s[i+1]){
				rep(j, cnt) t+=s[i];
				cnt=1;
			}else{
				cnt++;
			}
		}

		cout<< "Case #" << lp+1 << ": " << t <<endl;
	}

	return 0;
}