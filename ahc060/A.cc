#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

using namespace std;

int main() {
    int N, M, K, T;
    cin >> N >> M >> K >> T;

    // グラフの構築
    vector<vector<int>> graph(N);
    rep(i, M) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // 座標情報（使わないけど読み込む）
    rep(i, N) {
        int x, y;
        cin >> x >> y;
    }

    // 乱数の準備
    mt19937 mt(12345);

    // 現在位置と前の位置
    int current_pos = 0;
    int prev_pos = -1;

    // T回行動
    rep(step, T) {
        // 移動可能な頂点のリスト
        vector<int> candidates;
        for (int next : graph[current_pos]) {
            // 前回の移動元には戻れない
            if (next != prev_pos) {
                candidates.push_back(next);
            }
        }

        // ランダムに次の頂点を選択
        if (!candidates.empty()) {
            int idx = mt() % candidates.size();
            int next_pos = candidates[idx];

            cout << next_pos << endl;

            // 位置を更新
            prev_pos = current_pos;
            current_pos = next_pos;
        } else {
            // 念のため（基本的には起こらない）
            break;
        }
    }

    return 0;
}
