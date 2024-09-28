#include <atcoder/scc>
#include <bits/stdc++.h>
#include <cstdio>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<long long> u(m), v(m), w(m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--;
        v--;
    }

    auto scc = g.scc();

    printf("%d\n", int(scc.size()));
    for (auto v : scc) {
        printf("%d", int(v.size()));
        for (int x : v) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}