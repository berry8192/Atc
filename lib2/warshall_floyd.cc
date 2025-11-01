// ワーシャルフロイド warshall_floyd 全点対最短経路 O(V^3)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========== ライブラリ本体 ==========

// ワーシャルフロイド法
// 全点対最短経路を求める
template<typename T>
vector<vector<T>> warshall_floyd(int n, vector<vector<T>>& dist) {
    const T INF = numeric_limits<T>::max() / 2;

    // 経由点kを順に試す
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    return dist;
}

// 経路復元付きワーシャルフロイド
template<typename T>
pair<vector<vector<T>>, vector<vector<int>>> warshall_floyd_with_path(int n, vector<vector<T>>& dist) {
    const T INF = numeric_limits<T>::max() / 2;
    vector<vector<int>> next(n, vector<int>(n, -1));

    // 初期化
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] != INF) {
                next[i][j] = j;
            }
        }
    }

    // ワーシャルフロイド
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }

    return {dist, next};
}

// 経路復元
vector<int> restore_path_wf(const vector<vector<int>>& next, int start, int goal) {
    if (next[start][goal] == -1) return {};

    vector<int> path;
    path.push_back(start);

    int cur = start;
    while (cur != goal) {
        cur = next[cur][goal];
        path.push_back(cur);
    }

    return path;
}

// 負閉路検出付きワーシャルフロイド
template<typename T>
pair<vector<vector<T>>, bool> warshall_floyd_negative(int n, vector<vector<T>>& dist) {
    const T INF = numeric_limits<T>::max() / 2;

    // 通常のワーシャルフロイド
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // 負閉路検出（対角成分が負なら負閉路あり）
    bool has_negative_cycle = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            has_negative_cycle = true;
            break;
        }
    }

    return {dist, has_negative_cycle};
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なワーシャルフロイド
    cout << "例1: 基本的なワーシャルフロイド" << endl;
    int n1 = 4;
    const long long INF = 1e18;
    vector<vector<long long>> dist1(n1, vector<long long>(n1, INF));

    // 自己ループは0
    for (int i = 0; i < n1; i++) dist1[i][i] = 0;

    // 辺の追加
    dist1[0][1] = 1;
    dist1[0][2] = 5;
    dist1[1][2] = 2;
    dist1[1][3] = 4;
    dist1[2][3] = 1;
    dist1[3][2] = 7;

    warshall_floyd(n1, dist1);

    cout << "全点対最短距離:" << endl;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            if (dist1[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist1[i][j] << "   ";
            }
        }
        cout << endl;
    }
    cout << endl;

    // 例2: 経路復元
    cout << "例2: 経路復元付き" << endl;
    vector<vector<long long>> dist2(n1, vector<long long>(n1, INF));
    for (int i = 0; i < n1; i++) dist2[i][i] = 0;

    dist2[0][1] = 1;
    dist2[0][2] = 5;
    dist2[1][2] = 2;
    dist2[1][3] = 4;
    dist2[2][3] = 1;
    dist2[3][2] = 7;

    auto [dist_result, next] = warshall_floyd_with_path(n1, dist2);

    cout << "頂点0から頂点3への最短経路:" << endl;
    vector<int> path = restore_path_wf(next, 0, 3);
    cout << "  経路: ";
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << path[i];
    }
    cout << endl;
    cout << "  距離: " << dist_result[0][3] << endl;
    cout << endl;

    // 例3: 負閉路検出
    cout << "例3: 負閉路検出" << endl;
    int n3 = 3;
    vector<vector<long long>> dist3(n3, vector<long long>(n3, INF));
    for (int i = 0; i < n3; i++) dist3[i][i] = 0;

    dist3[0][1] = 1;
    dist3[1][2] = -3;
    dist3[2][0] = 1;

    auto [dist_neg, has_negative] = warshall_floyd_negative(n3, dist3);

    if (has_negative) {
        cout << "負閉路が存在します" << endl;
    } else {
        cout << "負閉路は存在しません" << endl;
    }

    return 0;
}