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

	int t, r, c;
	cin>> t;
	rep(lp, t){
		cin>> r >> c;
		vector<string> s={"..+", "..|", "+-+"};
		rep(i, c-1) s[0]+="-+";
		rep(i, c-1) s[1]+=".|";
		rep(i, c-1) s[2]+="-+";
		string tmp1="+";
		rep(i, c) tmp1+="-+";
		string tmp2="|";
		rep(i, c) tmp2+=".|";
		rep(i, r-1){
			s.push_back(tmp2);
			s.push_back(tmp1);
		}
		cout<< "Case #" << lp+1 << ":" <<endl;
		rep(i, s.size()){
			rep(j, s[i].size()){
				cout<< s[i][j];
			}
			cout<< endl;
		}
	}

	return 0;
}