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

	int n, m, ans=0, pos=0, cnt;
	bool s0=false, s1=false, t0=false, t1=false;
	vector<int> s, t;

	cin>> n >> m;
	s.resize(n);
	t.resize(m);

	rep(i, n){
		cin >> s[i];
		if(s[i]==0) s0=true;
		if(s[i]==1) s1=true;
	}
	rep(i, m){
		cin >> t[i];
		if(t[i]==0) t0=true;
		if(t[i]==1) t1=true;
	}

	if(t0 && !s0){
		cout<< -1 <<endl;
		return 0;
	}

	if(t1 && !s1){
		cout<< -1 <<endl;
		return 0;
	}

	rep(i, m) {
		if (t[i]==s[pos]) ans++;
		else{
			cnt=0;
			while(1){
				cnt++;
				if(t[i]==s[(pos+cnt)%n]){
					pos=(pos+cnt)%n;
					ans+=cnt;
					break;
				}else if(t[i]==s[(pos-cnt+n)%n]){
					pos=(pos-cnt+n)%n;
					ans+=cnt;
					break;
				}
			}
			ans++;
		}
	}

	cout<< ans << endl;
 
	return 0;
}