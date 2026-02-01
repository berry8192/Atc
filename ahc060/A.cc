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

    // 店から店への経路を列
    // paths[出発店][ゴール店] = {経路1, 経路2, ...}
    // 各経路は頂点番号の列
    vector<vector<vector<vector<int>>>> paths(K,
                                              vector<vector<vector<int>>>(K));

    rep(start, K) {
        // 開始店からBFSで経路を探索
        queue<vector<int>> q;
        q.push({start});

        int path_count = 0; // この出発点から見つけた経路数
        const int MAX_PATHS_PER_START = 1000;

        while (!q.empty() && path_count < MAX_PATHS_PER_START) {
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
                    path_count++;
                    if (path_count >= MAX_PATHS_PER_START)
                        break;
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

    // フォールバック用：店間の最短経路を1つずつ保持（BFS）
    vector<vector<vector<int>>> shortest_path(K, vector<vector<int>>(K));
    rep(start, K) {
        // BFSで最短経路を求める
        queue<vector<int>> q;
        vector<bool> visited(N, false);
        q.push({start});
        visited[start] = true;

        while (!q.empty()) {
            vector<int> path = q.front();
            q.pop();
            int current = path.back();

            // 店に到達したら記録
            if (current < K && current != start &&
                shortest_path[start][current].empty()) {
                shortest_path[start][current] = path;
            }

            for (int next : graph[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    vector<int> new_path = path;
                    new_path.push_back(next);
                    q.push(new_path);
                }
            }
        }
    }

    // 使用済み経路を管理するためのセット
    set<vector<int>> used_paths;

    // 木の着色状態（true: ストロベリー味に変更済み）
    vector<bool> is_colored(N, false);

    // 各ショップの在庫集合（納品済みのアイスの順列）
    vector<set<string>> shop_inventory(K);

    // 各頂点を含む経路のリスト（頂点K~N-1について）
    vector<vector<vector<int>>> vertex_to_paths(N);

    // 経路を列挙して、各頂点を含む経路を記録
    rep(start, K) {
        rep(goal, K) {
            if (start == goal)
                continue;
            for (const auto &path : paths[start][goal]) {
                // この経路に含まれるアイスの木（K~N-1）を記録
                for (int v : path) {
                    if (v >= K) {
                        vertex_to_paths[v].push_back(path);
                    }
                }
            }
        }
    }

    // 経路を辿った場合のアイスの順列を計算する関数
    auto get_ice_sequence = [&](const vector<int> &path) -> string {
        string result = "";
        for (int i = 1; i < path.size() - 1; i++) { // 開始店と終了店は除く
            int vertex = path[i];
            if (vertex >= K) { // アイスの木の場合
                if (is_colored[vertex]) {
                    result += 'R';
                } else {
                    result += 'W';
                }
            }
        }
        return result;
    };

    // 乱数の準備
    mt19937 mt(12345);

    // 経路ベースの移動
    int current_shop = 0; // 現在いる店
    int prev_vertex = -1; // 前の経路の最後から2番目の頂点
    int turn = 0;         // 使用したターン数

    while (turn < T) {
        // 現在の店から行ける経路を探す（priority_queue使用）
        priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>,
                       greater<pair<int, vector<int>>>>
            pq; // {経路長, 経路}（小さい順）

        rep(goal, K) {
            if (goal == current_shop)
                continue; // 同じ店には行けない

            // この店への未使用経路を全て追加
            if (!paths[current_shop][goal].empty()) {
                for (const auto &path : paths[current_shop][goal]) {
                    // 使用済みならスキップ
                    if (used_paths.count(path))
                        continue;

                    // 経路の2番目の頂点が前の経路の最後から2番目と同じならダメ
                    if (prev_vertex != -1 && path.size() >= 2 &&
                        path[1] == prev_vertex) {
                        continue;
                    }

                    // この経路でのアイスの順列を計算
                    string ice_seq = get_ice_sequence(path);
                    // 目的地のショップに既に同じアイスがあればスキップ
                    if (shop_inventory[goal].count(ice_seq)) {
                        continue;
                    }

                    pq.push({path.size(), path});
                }
            }
        }

        vector<int> chosen_path;
        int skip_count = 0;
        const int MAX_SKIP = 10;

        // priority_queueから経路を取り出して検証
        while (!pq.empty() && skip_count < MAX_SKIP) {
            auto candidate = pq.top();
            pq.pop();

            // 使用済みでないかチェック（二重チェック）
            if (!used_paths.count(candidate.second)) {
                chosen_path = candidate.second;
                used_paths.insert(chosen_path);
                break;
            }
            skip_count++;
        }

        // 100回連続でスキップした場合、強制的に使う
        if (chosen_path.empty() && !pq.empty()) {
            cerr << "Force using path at turn " << turn << " after "
                 << skip_count << " skips" << endl;
            chosen_path = pq.top().second;
            used_paths.insert(chosen_path);
        }

        // それでも経路がない場合：現在の店の経路を復活させる
        if (chosen_path.empty()) {
            cerr << "Reviving paths from shop " << current_shop << " at turn "
                 << turn << endl;

            // 現在の店から出る経路を復活
            rep(goal, K) {
                if (goal == current_shop)
                    continue;
                if (!paths[current_shop][goal].empty()) {
                    for (const auto &path : paths[current_shop][goal]) {
                        used_paths.erase(path);
                    }
                }
            }

            // 再度経路探索（復活させた経路から選択）
            priority_queue<pair<int, vector<int>>,
                           vector<pair<int, vector<int>>>,
                           greater<pair<int, vector<int>>>>
                pq2;

            rep(goal, K) {
                if (goal == current_shop)
                    continue;

                if (!paths[current_shop][goal].empty()) {
                    for (const auto &path : paths[current_shop][goal]) {
                        if (prev_vertex != -1 && path.size() >= 2 &&
                            path[1] == prev_vertex) {
                            continue;
                        }
                        pq2.push({path.size(), path});
                    }
                }
            }

            if (!pq2.empty()) {
                chosen_path = pq2.top().second;
                used_paths.insert(chosen_path);
            } else {
                // 最終フォールバック：最短経路を使用
                cerr << "Final fallback at turn " << turn << endl;
                int min_len = INT_MAX;

                rep(goal, K) {
                    if (goal == current_shop)
                        continue;
                    if (shortest_path[current_shop][goal].empty())
                        continue;

                    auto &path = shortest_path[current_shop][goal];
                    if (prev_vertex != -1 && path.size() >= 2 &&
                        path[1] == prev_vertex) {
                        continue;
                    }

                    if (path.size() < min_len) {
                        min_len = path.size();
                        chosen_path = path;
                    }
                }

                // 戻り制約でも見つからない場合は、制約を緩めて再探索
                if (chosen_path.empty()) {
                    cerr << "Relaxing constraints at turn " << turn << endl;
                    rep(goal, K) {
                        if (goal == current_shop)
                            continue;
                        if (shortest_path[current_shop][goal].empty())
                            continue;

                        auto &path = shortest_path[current_shop][goal];
                        if (path.size() < min_len) {
                            min_len = path.size();
                            chosen_path = path;
                        }
                    }
                }

                if (chosen_path.empty()) {
                    cerr << "No valid path found at turn " << turn << endl;
                    break;
                }
            }
        }

        // 経路に沿って移動（開始点以外を出力）
        for (int i = 1; i < chosen_path.size() && turn < T; i++) {
            cout << chosen_path[i] << endl;
            turn++;

            // 1000ターン以降、99の倍数のターン数で着色処理
            if (turn >= 1000 && turn % 99 == 0) {
                int current_pos = chosen_path[i];
                // 現在位置がアイスの木（K以上）で、未着色の場合
                if (current_pos >= K && !is_colored[current_pos]) {
                    cout << -1 << endl;
                    is_colored[current_pos] = true;
                    turn++;

                    // この頂点を含む経路を復活させる
                    cerr << "Colored vertex " << current_pos << ", reviving "
                         << vertex_to_paths[current_pos].size() << " paths"
                         << endl;
                    for (const auto &path : vertex_to_paths[current_pos]) {
                        used_paths.erase(path);
                    }

                    if (turn >= T)
                        break;
                }
            }
        }

        // この経路で集めたアイスの順列を計算して在庫に追加
        string ice_seq = get_ice_sequence(chosen_path);
        int goal_shop = chosen_path.back();
        shop_inventory[goal_shop].insert(ice_seq);

        // 次の経路のために、この経路の最後から2番目の頂点を記録
        if (chosen_path.size() >= 2) {
            prev_vertex = chosen_path[chosen_path.size() - 2];
        }

        // 次の店に移動
        current_shop = chosen_path.back();
    }

    // 最終スコアを出力
    int total_score = 0;
    rep(i, K) { total_score += shop_inventory[i].size(); }
    cerr << "Final score: " << total_score << endl;

    return 0;
}
