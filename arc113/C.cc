#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int tmp;
	LLi ans=0;
	string s;
	vector< vector<int> > alp(26);

	cin>> s;
	s+="0";
	reverse(s.begin(), s.end());
	rep(i, 26) alp[i].resize(s.size(), 0);

	//cout<< s <<endl;

	for(int i=1;i<s.size();i++){
		tmp=(int)(s[i]-'a');
		if(s[i]==s[i-1]){
			ans+=i-alp[tmp][i-1]-1;
			rep(j, 26){
				alp[j][i]=0;
			}
			alp[tmp][i]=i;
		}else{
			rep(j, 26){
				alp[j][i]=alp[j][i-1];
			}
			alp[tmp][i]++;
		}
		
		/*rep(j, 26){
			cout<< alp[i][j] SP;
		}
		cout<< endl;*/
	}

	cout<< ans << endl;
 
	return 0;
}