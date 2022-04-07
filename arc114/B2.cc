#include <bits/stdc++.h>
#include <atcoder/scc>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

// 強連結成分分解で閉路検出（未遂）
int main() {
    int n, m, sz=0;
	vector<int> f;
    cin>> n;
	m=n;
	f.resize(m);

    scc_graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
		u=i;
        cin>> v;
		v--;
		f[i]=v;
        g.add_edge(u, v);
    }

    auto scc = g.scc();

    // printf("%d\n", int(scc.size()));
    // for (auto v : scc) {
    //     printf("%d", int(v.size()));
    //     for (int x : v) {
    //         printf(" %d", x);
    //     }
    //     printf("\n");
    // }

    for (auto v : scc) {
        if(f[v[v.size()-1]]==v[0]) sz++;
		//cout<< f[v[v.size()-1]] SP << v[0] <<endl;
    }

	LLi ans=1;
	ans=modpow(2, sz);
	ans=(ans+mod-1)%mod;

	cout<< ans <<endl;

    return 0;
}
