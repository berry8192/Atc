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

int main(){

	int n, q, pos=0, l, r;
	vector< vector<int> > bo;
	vector<int> sn;
	queue<int> que;

	cin>> n >> q;
	bo.resize(n+1);
	sn.resize(n+1);

	rep(i, q){
		cin >> l >> r;
		l--;
		//r--;
		bo[l].push_back(r);
		bo[r].push_back(l);
	}

	que.push(0);
	while(!que.empty()){
		int tmp=que.front();
		que.pop();
		if(1){
		//if(sn[tmp]==0){
			sn[tmp]=1;
			rep(i, bo[tmp].size()){
				que.push(bo[tmp][i]);
			}
			bo[tmp].clear();
		}

	}

	if(sn[n]) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}