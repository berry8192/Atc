#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

using namespace std;

const int MAX_PATH_LENGTH = 20;

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

    // 店から店への経路を列挙（BFSで経路長10未満のみ）
    // paths[出発店][ゴール店] = {経路1, 経路2, ...}
    // 各経路は頂点番号の列
    vector<vector<vector<vector<int>>>> paths(K,
                                              vector<vector<vector<int>>>(K));

    rep(start, K) {
        // 開始店からBFSで経路を探索
        queue<vector<int>> q;
        q.push({start});

        while (!q.empty()) {
            vector<int> path = q.front();
            q.pop();

            int current = path.back();

            // 経路長が上限以上なら打ち切り
            if (path.size() >= MAX_PATH_LENGTH)
                continue;

            // 隣接頂点を探索
            for (int next : graph[current]) {
                // 直前の頂点には戻らない（経路に2つ以上頂点がある場合）
                if (path.size() >= 2 && next == path[path.size() - 2])
                    continue;

                vector<int> new_path = path;
                new_path.push_back(next);

                // nextが店なら経路として保存（ただし探索は続けない）
                if (next < K && next != start) {
                    paths[start][next].push_back(new_path);
                    // 店に到達したらそこで探索終了（キューに入れない）
                } else {
                    // 木のマスなら探索を続ける
                    q.push(new_path);
                }
            }
        }
    }

    // デバッグ出力（経路数を確認）
    cerr << "Path enumeration done:" << endl;
    int total_paths = 0;
    rep(i, K) {
        int sum_from_i = 0;
        rep(j, K) {
            if (i != j) {
                int cnt = paths[i][j].size();
                cerr << "Shop " << i << " -> Shop " << j << ": " << cnt
                     << " paths" << endl;
                sum_from_i += cnt;
            }
        }
        cerr << "From Shop " << i << " total: " << sum_from_i << " paths"
             << endl;
        total_paths += sum_from_i;
    }
    cerr << "Total paths: " << total_paths << endl;

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
