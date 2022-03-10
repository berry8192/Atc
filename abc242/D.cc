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
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
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

string tob(LLi n, int lng=0, string fil="0")
{
	//if(n==0) return "0";
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

int main(){

	int q;
	LLi tmp, tmpd, ans;
	string s, abc="ABC", d;
	vector<string> r;
	vector<LLi> t, k;

	cin>> s >> q;
	t.resize(q);
	k.resize(q);

	rep(i, q) cin >> t[i] >> k[i];

	rep(i, q) {
		if(t[i]>=60) tmpd=1152921504606846976;
		else tmpd=(1LL<<t[i]);
		k[i]--;
		tmp=k[i]/tmpd;
		k[i]-=tmp*tmpd;
		//sのtmp文字目が必要
		//cout<< "#" << s[tmp] <<endl;
		ans=s[tmp]-'A';
		d=tob(k[i]);
		reverse(all(d));
		//cout<< d <<endl;
		rep(j, d.size()){
			if(d[j]=='1') ans+=2;
			else ans++;
			ans%=3;
		}
		tmp=t[i]-d.size();
		ans+=max(0LL, tmp);
		ans%=3;
		cout<< char('A'+ans) <<endl;
	}

	return 0;
}