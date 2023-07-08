#include <bits/stdc++.h>
using namespace std;

//N 頂点
//M 辺
//S 始点
//AとBの間のコストがC
//dist 視点からの距離リスト

int imax=2147483647;
int N1, N2, M, S1, S2;
int dist[600009];
vector<pair<int, int>> G[600009];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
//N M ABC S

int main() {
    // グラフを入力する
    cin>> N1 >> N2 >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin>> a >> b;
        a--;
        b--;
        //scanf("%d%d", &A[i], &B[i]);
        G[a].push_back(make_pair(b, 1));
        G[b].push_back(make_pair(a, 1));
    }
    

    // 距離を初期化する
    for (int i = 0; i <= N1+N2; i++) dist[i] = imax;

    // 優先度付きキューには (距離, 頂点番号) の組を入れる
    Q.push(make_pair(0, 0));
    dist[0] = 0;
    while (!Q.empty()) {
        int pos = Q.top().second; Q.pop();
        for (int i = 0; i < G[pos].size(); i++) {
            int to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }
    Q.push(make_pair(0, N1+N2-1));
    dist[N1+N2-1] = 0;
    while (!Q.empty()) {
        int pos = Q.top().second; Q.pop();
        for (int i = 0; i < G[pos].size(); i++) {
            int to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }

    int ma1=0, ma2=0;
    // 距離を出力する
    for (int i = 0; i < N1; i++){
		ma1=max(ma1, dist[i]);
    }
    for (int i = N1; i < N1+N2; i++){
		ma2=max(ma2, dist[i]);
    }

    cout<< ma1+ma2+1 <<endl;

    return 0;
}