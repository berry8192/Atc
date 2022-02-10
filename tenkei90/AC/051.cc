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

int main(){

	LLi n, k, p, tmp, cnt, ans=0, sz;
	vector<LLi> v, w, x;
	vector< vector<LLi> > a(21), b(21);

	cin>> n >> k >> p;

	rep(i, n){
		cin >> tmp;
		if(i%2) v.push_back(tmp);
		else w.push_back(tmp);
	}

	sz=v.size();
	for (int bit = 0; bit < (1<<sz); ++bit) {
		tmp=0;
		cnt=0;
		//全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				tmp+=v[i];
				cnt++;
			}
        }
		//cout<< bit SP << tmp <<endl;
		a[cnt].push_back(tmp);
    }
	sz=w.size();
	for (int bit = 0; bit < (1<<sz); ++bit) {
		tmp=0;
		cnt=0;
		//全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				tmp+=w[i];
				cnt++;
			}
        }
		//cout<< bit SP << tmp <<endl;
		b[cnt].push_back(tmp);
    }
	rep(i, 21) sort(all(a[i]));

	rep(i, 21){
		rep(j, 21){
			if(i+j==k){
				vector<LLi> x=a[k-i];
				rep(l, b[i].size()){
					tmp=p-b[i][l];
					auto lb = upper_bound(all(x), tmp);
					ans+=(lb-x.begin());
				}
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}