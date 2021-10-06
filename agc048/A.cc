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

	int t, mi;
	cin>> t;
	string s, atc="atcoder";
	vector<int> v(26);

	rep(i, t){
		//cout<< i << " ";
		rep(j, 26) v[j]=0;
		mi=999999;

		cin>> s;
		rep(j, s.size()){
			v[(int)(s[j]-'a')]++;
		}

		if(v[0]==s.size()){
			cout<< -1 <<endl;
			continue;
		}

		if("atcoder"<s){
			cout<< 0 <<endl;
			continue;
		}

		rep(j, s.size()){
			if(s[j]!='a') mi=min(mi, j);
			if(s[j]>'t') mi=min(mi, j-1);
		}

		/*rep(j, s.size()){
			for(int k=0;k<min(7, j);k++){
				if(s[j]<=atc[k]) continue;
				mi=min(mi, j);
			}
		}*/
		/*rep(j, s.size()){
			if(s[j]>atc[j]){
				mi=0;
				flag=1;
				break;
			}
			if(s[j]==atc[j]){
				continue;
			}
			if(s[j]<atc[j])
			}
			s
		}
		if(s[0]!='a') */
		cout<< mi <<endl;
	}

	return 0;
}