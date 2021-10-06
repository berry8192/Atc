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

	int n, sz, tmp, flag;
	cin>> n;
	sz=n;
	if(n%2){
		return 0;
	}

	for (int bit = 0; bit < (1<<sz); ++bit) {
        vector<int> S;
		string s="";
		//全ての桁に対する処理
        for (int i = sz-1; i >=0; --i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)) s+=")";
			else s+="(";
        }
		tmp=0;
		flag=1;
		for(int i=0;i<n;i++){
			if(s[i]=='(') tmp++;
			else tmp--;
			//cout<< tmp <<endl;
			if(tmp<0){
				flag=0;
				break;
			}
		}
		if(tmp==0) cout<< s <<endl;
    }
 
	return 0;
}