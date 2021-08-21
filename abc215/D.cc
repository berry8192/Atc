#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

vector<LLi> pri={1, 2, 3};

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
vector<pair<long long, long long> > prime_factorize(long long N) {
    vector<pair<long long, long long> > res;
    for (long long a = 2; a * a <= N; ++a) {
        if (N % a != 0) continue;
        long long ex = 0; // 指数

        // 割れる限り割り続ける
        while (N % a == 0) {
            ++ex;
            N /= a;
        }

        // その結果を push
        res.push_back({a, ex});
    }

    // 最後に残った数について
    if (N != 1) res.push_back({N, 1});
    return res;
}

int main(){

	LLi n, m, ml, ans=0;
	vector<LLi> v, bo, bo2;

	cin>> n >> m;

	v.resize(n);
	bo.resize(100010);
	bo2.resize(100010);
	
	rep(i, n) cin>> v[i];

	//PVL(pri);//
	rep(i, n){
		const auto &mp = prime_factorize(v[i]);
		
		for (auto p : mp) {
			// auto key = p.first;
			// auto value = p.second;
			// cout<< key << "^" << value SP;//mpの内訳を表示
			bo[p.first]=1;
		}
		//cout<< endl;
	}
	//PVL(bo);

	for(int i=2;i<=m;i++){
		if(bo[i]){
			for(int j=i;j<=m;j+=i){
				bo2[j]=1;
			}
		}
	}
	//PVL(bo2);
	for(int i=1;i<=m;i++){
		if(bo2[i]==0) ans++;
	}
	cout<< ans <<endl;
	for(int i=1;i<=m;i++){
		if(bo2[i]==0) cout<< i <<endl;
	}

	return 0;
}