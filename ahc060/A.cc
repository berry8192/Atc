#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()

using namespace std;

// パラメータ定数
const int MAX_PATH_LENGTH = 20;
const int TIME_LIMIT_MS = 1200;

// 経路構造体
struct Route {
    int id, start, goal, length;
    vector<int> path;
    vector<int> ice_vertices;
    mutable unordered_map<int, string>
        ice_seq_cache; // 訪問済みパターンのみ保存

    // 現在の盤面状態からice_sequenceを取得（キャッシュ付き）
    string get_ice_seq(const vector<bool> &is_colored) const {
        // ビットマスク計算
        int mask = 0;
        for (int i = 0; i < ice_vertices.size(); i++) {
            if (is_colored[ice_vertices[i]]) {
                mask |= (1 << i);
            }
        }

        // キャッシュ確認
        auto it = ice_seq_cache.find(mask);
        if (it != ice_seq_cache.end()) {
            return it->second; // キャッシュヒット
        }

        // 初回のみ文字列生成
        string seq = "";
        seq.reserve(ice_vertices.size());
        for (int i = 0; i < ice_vertices.size(); i++) {
            seq += (mask & (1 << i)) ? 'R' : 'W';
        }
        ice_seq_cache[mask] = seq;
        return seq;
    }
};

struct Result {
    int score;
    vector<int> output;
};

// シミュレーション実行
Result run_simulation(int N, int M, int K, int T,
                      const vector<vector<int>> &graph,
                      const vector<Route> &all_routes,
                      const vector<vector<int>> &route_ids_by_sg,
                      const vector<vector<int>> &shortest_route_id,
                      const vector<vector<int>> &vertex_to_route_ids,
                      int MAX_PATHS_PER_START, int MAX_SKIP,
                      int COLOR_START_TURN, int COLOR_INTERVAL, mt19937 &mt) {
    Result result;
    result.score = 0;

    // 使用済み経路を管理（IDで管理）
    set<int> used_route_ids;

    // 木の着色状態（true: ストロベリー味に変更済み）
    vector<bool> is_colored(N, false);

    // 各ショップの在庫集合（納品済みのアイスの順列）
    vector<set<string>> shop_inventory(K);

    // 経路ベースの移動
    int current_shop = 0; // 現在いる店
    int prev_vertex = -1; // 前の経路の最後から2番目の頂点
    int turn = 0;         // 使用したターン数

    while (turn < T) {
        // 現在の店から行ける経路を探す（priority_queue使用）
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            pq; // {経路長, route_id}（小さい順）

        rep(goal, K) {
            if (goal == current_shop)
                continue;

            // この店への未使用経路を全て追加
            int sg_idx = current_shop * K + goal;
            for (int rid : route_ids_by_sg[sg_idx]) {
                const Route &route = all_routes[rid];

                // 使用済みならスキップ
                if (used_route_ids.count(rid))
                    continue;

                // 経路の2番目の頂点が前の経路の最後から2番目と同じならダメ
                if (prev_vertex != -1 && route.path.size() >= 2 &&
                    route.path[1] == prev_vertex) {
                    continue;
                }

                // この経路でのアイスの順列を計算
                string ice_seq = route.get_ice_seq(is_colored);
                // 目的地のショップに既に同じアイスがあればスキップ
                if (shop_inventory[goal].count(ice_seq)) {
                    continue;
                }

                pq.push({route.length, rid});
            }
        }

        int chosen_rid = -1;
        int skip_count = 0;

        // priority_queueから経路を取り出して検証
        while (!pq.empty() && skip_count < MAX_SKIP) {
            auto candidate = pq.top();
            pq.pop();

            // 使用済みでないかチェック（二重チェック）
            if (!used_route_ids.count(candidate.second)) {
                chosen_rid = candidate.second;
                used_route_ids.insert(chosen_rid);
                break;
            }
            skip_count++;
        }

        // MAX_SKIP回連続でスキップした場合、強制的に使う
        if (chosen_rid == -1 && !pq.empty()) {
            chosen_rid = pq.top().second;
            used_route_ids.insert(chosen_rid);
        }

        // それでも経路がない場合：現在の店の経路を復活させる
        if (chosen_rid == -1) {
            // 現在の店から出る経路を復活
            rep(goal, K) {
                if (goal == current_shop)
                    continue;
                int sg_idx = current_shop * K + goal;
                for (int rid : route_ids_by_sg[sg_idx]) {
                    used_route_ids.erase(rid);
                }
            }

            // 再度経路探索（復活させた経路から選択）
            priority_queue<pair<int, int>, vector<pair<int, int>>,
                           greater<pair<int, int>>>
                pq2;

            rep(goal, K) {
                if (goal == current_shop)
                    continue;

                int sg_idx = current_shop * K + goal;
                for (int rid : route_ids_by_sg[sg_idx]) {
                    const Route &route = all_routes[rid];
                    if (prev_vertex != -1 && route.path.size() >= 2 &&
                        route.path[1] == prev_vertex) {
                        continue;
                    }
                    pq2.push({route.length, rid});
                }
            }

            if (!pq2.empty()) {
                chosen_rid = pq2.top().second;
            } else {
                // 最終フォールバック：最短経路を使用
                int min_len = INT_MAX;

                rep(goal, K) {
                    if (goal == current_shop)
                        continue;
                    int sid = shortest_route_id[current_shop][goal];
                    if (sid == -1)
                        continue;

                    const Route &route = all_routes[sid];
                    if (prev_vertex != -1 && route.path.size() >= 2 &&
                        route.path[1] == prev_vertex) {
                        continue;
                    }

                    if (route.length < min_len) {
                        min_len = route.length;
                        chosen_rid = sid;
                    }
                }

                // 戻り制約でも見つからない場合は、制約を緩めて再探索
                if (chosen_rid == -1) {
                    rep(goal, K) {
                        if (goal == current_shop)
                            continue;
                        int sid = shortest_route_id[current_shop][goal];
                        if (sid == -1)
                            continue;

                        const Route &route = all_routes[sid];
                        if (route.length < min_len) {
                            min_len = route.length;
                            chosen_rid = sid;
                        }
                    }
                }

                if (chosen_rid == -1) {
                    break;
                }
            }
        }

        const Route &chosen_route = all_routes[chosen_rid];

        // 経路に沿って移動（開始点以外を出力）
        for (int i = 1; i < chosen_route.path.size() && turn < T; i++) {
            result.output.push_back(chosen_route.path[i]);
            turn++;

            // COLOR_START_TURN以降、COLOR_INTERVALの倍数のターン数で着色処理
            if (turn >= COLOR_START_TURN && turn % COLOR_INTERVAL == 0) {
                int current_pos = chosen_route.path[i];
                // 現在位置がアイスの木（K以上）で、未着色の場合
                if (current_pos >= K && !is_colored[current_pos]) {
                    result.output.push_back(-1);
                    is_colored[current_pos] = true;
                    turn++;

                    // この頂点を含む経路を復活させる
                    for (int rid : vertex_to_route_ids[current_pos]) {
                        used_route_ids.erase(rid);
                    }

                    if (turn >= T)
                        break;
                }
            }
        }

        // この経路で集めたアイスの順列を計算して在庫に追加
        string ice_seq = chosen_route.get_ice_seq(is_colored);
        int goal_shop = chosen_route.goal;
        shop_inventory[goal_shop].insert(ice_seq);

        // 次の経路のために、この経路の最後から2番目の頂点を記録
        if (chosen_route.path.size() >= 2) {
            prev_vertex = chosen_route.path[chosen_route.path.size() - 2];
        }

        // 次の店に移動
        current_shop = chosen_route.goal;
    }

    // スコア計算
    rep(i, K) { result.score += shop_inventory[i].size(); }

    return result;
}

int main() {
    auto start_time = chrono::high_resolution_clock::now();
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
    uniform_int_distribution<> dist_paths(2500, 3000);
    uniform_int_distribution<> dist_skip(10, 20);
    uniform_int_distribution<> dist_color_start(500, 2000);
    uniform_int_distribution<> dist_color_interval(60, 91);

    Result best_result;
    best_result.score = 0;

    int iteration = 0;
    while (true) {
        auto current_time = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(
                           current_time - start_time)
                           .count();
        if (elapsed >= TIME_LIMIT_MS)
            break;

        iteration++;

        // パラメータをランダム化
        int MAX_PATHS_PER_START = dist_paths(mt);
        int MAX_SKIP = dist_skip(mt);
        int COLOR_START_TURN = dist_color_start(mt);
        int COLOR_INTERVAL = dist_color_interval(mt);

        cerr << "Iteration " << iteration << ": PATHS=" << MAX_PATHS_PER_START
             << " SKIP=" << MAX_SKIP << " START=" << COLOR_START_TURN
             << " INTERVAL=" << COLOR_INTERVAL << endl;

        // 店から店への経路を列挙
        vector<vector<vector<vector<int>>>> paths(
            K, vector<vector<vector<int>>>(K));

        rep(start, K) {
            // 開始店からBFSで経路を探索
            queue<vector<int>> q;
            q.push({start});

            int path_count = 0; // この出発点から見つけた経路数

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

        // 経路をID化して管理
        vector<Route> all_routes;
        vector<vector<int>> route_ids_by_sg(K *
                                            K); // [start*K+goal] = route_ids

        int route_id = 0;
        rep(start, K) {
            rep(goal, K) {
                if (start == goal)
                    continue;

                // 経路長でソート
                sort(all(paths[start][goal]), [](const auto &a, const auto &b) {
                    return a.size() < b.size();
                });

                for (const auto &path : paths[start][goal]) {
                    Route r;
                    r.id = route_id++;
                    r.start = start;
                    r.goal = goal;
                    r.path = path;
                    r.length = path.size() - 1;

                    // アイスの木のみ抽出
                    for (int i = 1; i < path.size() - 1; i++) {
                        if (path[i] >= K) {
                            r.ice_vertices.push_back(path[i]);
                        }
                    }

                    all_routes.push_back(r);
                    route_ids_by_sg[start * K + goal].push_back(r.id);
                }
            }
        }

        // フォールバック用：店間の最短経路を1つずつ保持（BFS）
        vector<vector<int>> shortest_route_id(K, vector<int>(K, -1));
        rep(start, K) {
            rep(goal, K) {
                if (start != goal &&
                    !route_ids_by_sg[start * K + goal].empty()) {
                    shortest_route_id[start][goal] =
                        route_ids_by_sg[start * K + goal][0];
                }
            }
        }

        // 各頂点を含む経路のIDリスト
        vector<vector<int>> vertex_to_route_ids(N);

        // 経路を列挙して、各頂点を含む経路を記録
        for (const auto &route : all_routes) {
            for (int v : route.ice_vertices) {
                vertex_to_route_ids[v].push_back(route.id);
            }
        }

        // シミュレーション実行
        Result result = run_simulation(
            N, M, K, T, graph, all_routes, route_ids_by_sg, shortest_route_id,
            vertex_to_route_ids, MAX_PATHS_PER_START, MAX_SKIP,
            COLOR_START_TURN, COLOR_INTERVAL, mt);

        cerr << "  Score: " << result.score << endl;

        if (result.score > best_result.score) {
            best_result = result;
            cerr << "  New best!" << endl;
        }
    }

    cerr << "Total iterations: " << iteration << endl;
    cerr << "Best score: " << best_result.score << endl;

    // 最良の結果を出力
    for (int v : best_result.output) {
        cout << v << endl;
    }

    return 0;
}
