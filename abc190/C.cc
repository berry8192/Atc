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

	int n, m, k, tmp, ma=0;
	vector<int> a, b, c, d;

	cin>> n >> m;
	a.resize(m);
	b.resize(m);
	rep(i, m) cin >> a[i] >> b[i];
  cin>> k;

	c.resize(k);
	d.resize(k);
	rep(i, k) cin >> c[i] >> d[i];

  int sz=k;

	//1を左シフトして2^szが出せる
	for (int bit = 0; bit < (1<<sz); ++bit) {
        vector<int> S;
        S.clear();
        S.resize(n+1);
		tmp=0;
		//全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
              S[c[i]]=1;
            }else{
              S[d[i]]=1;
            }
        }
		//cout<< bit SP << tmp <<endl;
      for(int i=0;i<m;i++){
        if(S[a[i]] && S[b[i]]) tmp++;
      }
      ma=max(ma, tmp);
    }

    cout<< ma <<endl;
 
	return 0;
}