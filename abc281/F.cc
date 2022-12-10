#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

int main(){

	int n, ans=0, pos=29;
	cin>> n;
	vector<int> v(n), al(30);
	vector<bitset<150000>> seen(30);
	bitset<150000> inv;
	rep(i, 150000) inv.set(i);

	rep(i, n) cin >> v[i];

	for(int i=29;i>=0;i--){
		int tmp=(1<<i);
		// cout<< tmp <<endl;
		int cnt=0;
		rep(j, n){
			if(tmp&v[j]){
				cnt++;
				seen[i].set(j);
				cout<< i SP << j <<endl;
			}
		}
		if(cnt==0 || cnt==n){
			al[i]=1;
			continue;
		}
		for(int j=pos;j>i;j--){
			if(al[j]) continue;
			int flag=0;
			bitset<150000> bt=(seen[j]|seen[i]);
			if(bt.all()) flag=1;
			bt=((inv^seen[i])|seen[i]);
			if(bt.all()) flag=2;
			bt=(seen[j]|(inv^seen[i]));
			if(bt.all()) flag=3;
			bt=((inv^seen[i])|(inv^seen[i]));
			if(bt.all()) flag=4;
			if(flag){
				cout<< "flag: " << i SP << flag <<endl;
				pos=i;
				ans-=tmp;
				break;
			}
		}
		ans+=tmp;
	}

	cout<< ans << endl;
 
	return 0;
}