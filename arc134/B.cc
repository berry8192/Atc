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

	int n, l, r;
	vector<int> sl, sr;
	cin>> n;
	string s;
	cin>> s;
	l=0;
	r=n-1;

	for(int i=0;i<26;i++){
		if(l>=r) break;
		char tmp='a'+i;
		//cout<< tmp <<endl;
		sl.clear();
		sr.clear();
		for(int j=l;j<n;j++){
			if(s[j]>tmp){
				sl.push_back(j);
			}
		}
		for(int j=r;j>=0;j--){
			if(s[j]==tmp){
				sr.push_back(j);
			}
		}
		for(int j=0;j<min(sl.size(), sr.size());j++){
			if(sl[j]<sr[j]){
				// if(s[sl[j]]>s[sr[j]]){
				// 	//cout<< char('a'+i) <<endl;
				// 	return 0;
				// }
				swap(s[sl[j]], s[sr[j]]);
				l=sl[j]+1;
				r=sr[j]-1;
			}else{
				break;
			}
		}
	}

	cout<< s <<endl;
 
	return 0;
}