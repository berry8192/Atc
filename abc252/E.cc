#include <bits/stdc++.h>
using namespace std;
#define ll long long

//N 頂点
//M 辺
//S 始点
//AとBの間のコストがC
//dist 視点からの距離リスト

ll lmax=9223372036854775807;
ll N, M, S, A[500009], B[500009], C[500009];
ll dist[200009];
ll fro[200009];
vector<pair<ll, ll>> G[200009];
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> Q;
//N M ABC S
map<pair<ll, ll>, ll> mp;

int main() {
    // グラフを入力する
    cin>> N >> M;
    for (ll i = 1; i <= M; i++) {
        cin>> A[i] >> B[i] >> C[i];
        //scanf("%d%d", &A[i], &B[i]);
        G[A[i]].push_back(make_pair(B[i], C[i]));
        G[B[i]].push_back(make_pair(A[i], C[i]));
		mp[make_pair(A[i], B[i])]=i;
    }
    S=1;

    // 距離を初期化する
    for (ll i = 1; i <= N; i++) dist[i] = lmax;

    // 優先度付きキューには (距離, 頂点番号) の組を入れる
    Q.push(make_pair(0, S));
    dist[S] = 0;
    while (!Q.empty()) {
        ll pos = Q.top().second; Q.pop();
        for (ll i = 0; i < G[pos].size(); i++) {
            ll to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
				fro[to]=pos;
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }

    // 距離を出力する
    for (ll i = 2; i <= N; i++){
		cout<< mp[make_pair(min(fro[i], i), max(fro[i], i))] << " ";
    }
	cout<< endl;
    return 0;
}