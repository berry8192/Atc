#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
LLi n, b, ans=0;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

void dfs(string s, int nxt){
	if(s.size()==11){
		LLi d=stoll(s);
		//cout<< s <<endl;
		string ss=to_string(d);
		vector<int> v(10), w(10);
		LLi pr=1;
		rep(i, ss.size()){
			int tmp=int(ss[i]-'0');
			pr*=tmp;
			v[tmp]++;
		}
		string sss=to_string(pr+b);
		if(pr+b>n) return;
		rep(i, sss.size()){
			int tmp=int(sss[i]-'0');
			w[tmp]++;
		}
		int flag=1;
		rep(i, 10){
			if(v[i]!=w[i]) flag=0;
		}
		if(flag) ans++;
		return;
	}
	for(int i=nxt;i<=9;i++){
		string tmp=s;
		tmp+='0'+i;
		//cout<< i <<endl;
		dfs(tmp, i);
	}
}

int main(){

	cin>> n >> b;

	dfs("", 0);

	string V = to_string(b);
	bool flag = false;
	for (int i = 0; i < V.size(); i++) {
		if (V[i] == '0') flag = true;
	}
	if (flag == true && n >= b) ans += 1;

	cout<< ans << endl;
 
	return 0;
}