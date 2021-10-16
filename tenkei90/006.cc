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

	int n, k, pos=0, cnt=0;
	string s, ans="";
	vector< vector<int> > v;

	cin>> n >> k;
	cin>> s;
	v.resize(26);
	rep(i, 26) v[i].resize(n+1);

	rep(i, n) {
		rep(j, 26){
			v[j][i+1]=v[j][i];
		}
		v[int(s[i]-'a')][i+1]++;
	}

	//rep(i, 26) PV(v[i]);

	rep(i, k){
		if(n-pos==k-cnt){
			//cout<< "syuryou" <<endl;
			ans+=s.substr(n-(k-cnt));
			break;
		}
		rep(i, 26){
			//cout<< char('a'+i) SP << v[i][pos] SP << v[i][n-(k-cnt)+1] <<endl;
			if(v[i][n-(k-cnt)+1]>v[i][pos]){
				auto lb = lower_bound(all(v[i]), v[i][pos]+1);
				int tmp=lb-v[i].begin();
				//cout<< tmp <<endl;
				cnt++;
				ans+='a'+i;
				pos=tmp;
				//cout<< s[pos-1] <<endl;
				break;
			}
		}
	}

	cout<< ans <<endl;
 
	return 0;
}