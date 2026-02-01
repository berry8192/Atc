#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

using namespace std;

const int MAX_PATH_LENGTH = 15;

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

    // 店から店への経路を列
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

    // 経路ベースの移動
    int current_shop = 0; // 現在いる店
    int prev_vertex = -1; // 前の経路の最後から2番目の頂点
    int turn = 0;         // 使用したターン数

    while (turn < T) {
        // 現在の店から行ける経路を探す
        vector<pair<int, vector<int>>> candidates; // {経路長, 経路}

        rep(goal, K) {
            if (goal == current_shop)
                continue; // 同じ店には行けない

            // この店への経路から最短のものを選ぶ
            if (!paths[current_shop][goal].empty()) {
                int min_len = INT_MAX;
                vector<int> best_path;
                for (const auto &path : paths[current_shop][goal]) {
                    // 経路の2番目の頂点が前の経路の最後から2番目と同じならダメ
                    if (prev_vertex != -1 && path.size() >= 2 &&
                        path[1] == prev_vertex) {
                        continue;
                    }

                    if (path.size() < min_len) {
                        min_len = path.size();
                        best_path = path;
                    }
                }

                if (!best_path.empty()) {
                    candidates.push_back({min_len, best_path});
                }
            }
        }

        if (candidates.empty()) {
            // 行ける経路がない場合は終了
            cerr << "No valid path found at turn " << turn << endl;
            break;
        }

        // 最短の経路を選択
        sort(all(candidates));
        vector<int> chosen_path = candidates[0].second;

        // 経路に沿って移動（開始点以外を出力）
        for (int i = 1; i < chosen_path.size() && turn < T; i++) {
            cout << chosen_path[i] << endl;
            turn++;
        }

        // 次の経路のために、この経路の最後から2番目の頂点を記録
        if (chosen_path.size() >= 2) {
            prev_vertex = chosen_path[chosen_path.size() - 2];
        }

        // 次の店に移動
        current_shop = chosen_path.back();
    }

    return 0;
}
