#include <bits/stdc++.h>
using namespace std;

struct Step {
    char act; // 'L','R','F'
};

int N;
vector<string> wall_v, wall_h;

// 方向: 0=U,1=R,2=D,3=L
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool can_go(int x, int y, int d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= N || ny < 0 || ny >= N)
        return false;
    if (d == 0)
        return wall_h[nx][ny] == '0'; // 上
    if (d == 2)
        return wall_h[x][y] == '0'; // 下
    if (d == 1)
        return wall_v[x][y] == '0'; // 右
    if (d == 3)
        return wall_v[x][ny] == '0'; // 左
    return false;
}

// パスから方向転換数を数える
int count_turns(const vector<pair<int, int>>& path) {
    if (path.size() < 2) return 0;
    int turns = 0;
    int prev_d = -1;
    for (size_t i = 1; i < path.size(); i++) {
        auto [px, py] = path[i - 1];
        auto [cx, cy] = path[i];
        int d;
        if (cx == px - 1) d = 0;
        else if (cy == py + 1) d = 1;
        else if (cx == px + 1) d = 2;
        else d = 3;
        if (prev_d >= 0 && d != prev_d) turns++;
        prev_d = d;
    }
    return turns;
}

// 2×2ブロック法でハミルトン閉路を構成
// 戻り値: (0,0)始点の閉路パス（末尾も(0,0)）、失敗時は空
vector<pair<int, int>> block_hamiltonian_cycle() {
    if (N % 2 != 0) return {};
    int B = N / 2;

    // 全ブロックの4辺が壁なしか確認
    for (int bi = 0; bi < B; bi++)
        for (int bj = 0; bj < B; bj++) {
            int r = 2 * bi, c = 2 * bj;
            if (!can_go(r, c, 1) || !can_go(r, c + 1, 2) ||
                !can_go(r + 1, c + 1, 3) || !can_go(r + 1, c, 0))
                return {};
        }

    // ブロック隣接グラフ構築
    int TB = B * B;
    vector<vector<int>> adj(TB);
    for (int bi = 0; bi < B; bi++)
        for (int bj = 0; bj < B; bj++) {
            int id = bi * B + bj;
            // 右隣: 接続辺2本が壁なしか
            if (bj + 1 < B && can_go(2 * bi, 2 * bj + 1, 1) &&
                can_go(2 * bi + 1, 2 * bj + 1, 1)) {
                adj[id].push_back(id + 1);
                adj[id + 1].push_back(id);
            }
            // 下隣
            if (bi + 1 < B && can_go(2 * bi + 1, 2 * bj, 2) &&
                can_go(2 * bi + 1, 2 * bj + 1, 2)) {
                adj[id].push_back(id + B);
                adj[id + B].push_back(id);
            }
        }

    // 連結性チェック (BFS)
    vector<bool> vis(TB, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;
    int cnt = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
            if (!vis[v]) {
                vis[v] = true;
                cnt++;
                q.push(v);
            }
    }
    if (cnt != TB) return {};

    // BFS全域木
    vector<pair<int, int>> tree_edges;
    fill(vis.begin(), vis.end(), false);
    q.push(0);
    vis[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
            if (!vis[v]) {
                vis[v] = true;
                tree_edges.emplace_back(u, v);
                q.push(v);
            }
    }

    // HC辺の管理: hori[r][c] = (r,c)-(r,c+1), vert[r][c] = (r,c)-(r+1,c)
    vector<vector<bool>> hori(N, vector<bool>(N - 1, false));
    vector<vector<bool>> vert(N - 1, vector<bool>(N, false));

    // 各ブロックのミニサイクル初期化
    for (int bi = 0; bi < B; bi++)
        for (int bj = 0; bj < B; bj++) {
            int r = 2 * bi, c = 2 * bj;
            hori[r][c] = true;         // 上辺
            vert[r][c + 1] = true;     // 右辺
            hori[r + 1][c] = true;     // 下辺
            vert[r][c] = true;         // 左辺
        }

    // 全域木の辺に沿ってミニサイクルを合体
    for (auto [u, v] : tree_edges) {
        int bi_u = u / B, bj_u = u % B;
        int bi_v = v / B, bj_v = v % B;

        if (bi_u == bi_v) {
            // 水平合体
            int bi = bi_u, bj = min(bj_u, bj_v);
            // 左ブロック右辺・右ブロック左辺を除去
            vert[2 * bi][2 * bj + 1] = false;
            vert[2 * bi][2 * bj + 2] = false;
            // 接続辺を追加
            hori[2 * bi][2 * bj + 1] = true;
            hori[2 * bi + 1][2 * bj + 1] = true;
        } else {
            // 垂直合体
            int bi = min(bi_u, bi_v), bj = bj_u;
            // 上ブロック下辺・下ブロック上辺を除去
            hori[2 * bi + 1][2 * bj] = false;
            hori[2 * bi + 2][2 * bj] = false;
            // 接続辺を追加
            vert[2 * bi + 1][2 * bj] = true;
            vert[2 * bi + 1][2 * bj + 1] = true;
        }
    }

    // (0,0)から閉路をトレース
    vector<pair<int, int>> cycle;
    cycle.emplace_back(0, 0);
    int x = 0, y = 0, px = -1, py = -1;
    for (int step = 0; step < N * N; step++) {
        bool found = false;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (nx == px && ny == py) continue;
            bool in_hc = false;
            if (d == 1 && y < N - 1) in_hc = hori[x][y];
            else if (d == 3 && y > 0) in_hc = hori[x][y - 1];
            else if (d == 2 && x < N - 1) in_hc = vert[x][y];
            else if (d == 0 && x > 0) in_hc = vert[x - 1][y];
            if (in_hc) {
                cycle.emplace_back(nx, ny);
                px = x;
                py = y;
                x = nx;
                y = ny;
                found = true;
                break;
            }
        }
        if (!found) return {};
    }

    if (cycle.back() != make_pair(0, 0)) return {};
    return cycle;
}

// Warnsdorff法でハミルトン路を探索（始点固定、ランダムタイブレーク）
// 戻り値: 全マス訪問できたパス、失敗時は空
vector<pair<int, int>> warnsdorf_greedy(int sx, int sy, mt19937& rng) {
    int total = N * N;
    vector<vector<bool>> vis(N, vector<bool>(N, false));
    vector<pair<int, int>> path;
    path.reserve(total);

    int x = sx, y = sy;
    vis[x][y] = true;
    path.emplace_back(x, y);

    for (int step = 1; step < total; step++) {
        vector<pair<int, int>> candidates; // (degree, dir)
        for (int d = 0; d < 4; d++) {
            if (!can_go(x, y, d)) continue;
            int nx = x + dx[d], ny = y + dy[d];
            if (vis[nx][ny]) continue;
            int deg = 0;
            for (int dd = 0; dd < 4; dd++) {
                if (!can_go(nx, ny, dd)) continue;
                int nnx = nx + dx[dd], nny = ny + dy[dd];
                if (!vis[nnx][nny]) deg++;
            }
            candidates.emplace_back(deg, d);
        }
        if (candidates.empty()) return {};

        int min_deg = INT_MAX;
        for (auto& [deg, d] : candidates)
            min_deg = min(min_deg, deg);
        vector<int> best_dirs;
        for (auto& [deg, d] : candidates)
            if (deg == min_deg) best_dirs.push_back(d);

        int chosen = best_dirs[rng() % best_dirs.size()];
        x = x + dx[chosen];
        y = y + dy[chosen];
        vis[x][y] = true;
        path.emplace_back(x, y);
    }
    return path;
}

struct HamResult {
    vector<pair<int, int>> path; // 始点は(0,0)
    bool is_cycle = false;
};

// ハミルトン路/閉路を探索（(0,0)始点、10000 trial）
HamResult find_hamiltonian(mt19937& rng) {
    int total = N * N;

    vector<pair<int, int>> best_path;
    bool best_is_cycle = false;
    int best_turns = INT_MAX;

    for (int trial = 0; trial < 10000; trial++) {
        auto path = warnsdorf_greedy(0, 0, rng);
        if (path.empty()) continue;

        // 閉路判定
        auto [ex, ey] = path.back();
        bool is_cycle = false;
        for (int d = 0; d < 4; d++) {
            if (!can_go(ex, ey, d)) continue;
            int nx = ex + dx[d], ny = ey + dy[d];
            if (nx == 0 && ny == 0) { is_cycle = true; break; }
        }

        int turns = count_turns(path);

        bool update = false;
        if (best_path.empty()) update = true;
        else if (is_cycle && !best_is_cycle) update = true;
        else if (is_cycle == best_is_cycle && turns < best_turns) update = true;

        if (update) {
            best_path = path;
            best_is_cycle = is_cycle;
            best_turns = turns;
        }
    }

    return {best_path, best_is_cycle};
}

// BFS最短帰還路
vector<pair<int, int>> bfs_return_path(int sx, int sy, int gx, int gy) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    vector<vector<pair<int, int>>> prev(N, vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == gx && y == gy) break;
        for (int d = 0; d < 4; d++) {
            if (!can_go(x, y, d)) continue;
            int nx = x + dx[d], ny = y + dy[d];
            if (dist[nx][ny] >= 0) continue;
            dist[nx][ny] = dist[x][y] + 1;
            prev[nx][ny] = {x, y};
            q.push({nx, ny});
        }
    }

    vector<pair<int, int>> ret;
    int cx = gx, cy = gy;
    while (cx != sx || cy != sy) {
        ret.emplace_back(cx, cy);
        auto [px, py] = prev[cx][cy];
        cx = px;
        cy = py;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

// BFS距離（-1 = 到達不能）
int bfs_dist(int sx, int sy, int ex, int ey) {
    if (sx == ex && sy == ey) return 0;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            if (!can_go(x, y, d)) continue;
            int nx = x + dx[d], ny = y + dy[d];
            if (dist[nx][ny] >= 0) continue;
            dist[nx][ny] = dist[x][y] + 1;
            if (nx == ex && ny == ey) return dist[nx][ny];
            q.push({nx, ny});
        }
    }
    return -1;
}

// ツアーを焼きなまし的に短縮する
// tour: (0,0)始点・終点の閉路（全セル訪問）
vector<pair<int, int>> optimize_tour(vector<pair<int, int>> tour, mt19937& rng) {
    int N2 = N * N;

    // 訪問回数
    vector<vector<int>> vc(N, vector<int>(N, 0));
    for (auto& [x, y] : tour)
        vc[x][y]++;

    auto t0 = chrono::steady_clock::now();
    int improved = 0;

    while (true) {
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(
                            chrono::steady_clock::now() - t0)
                            .count();
        if (elapsed > 900) break;

        int sz = tour.size();
        if (sz <= N2 + 1) break; // 既にハミルトン閉路

        // ランダムにセグメントを選ぶ
        int L = 4 + rng() % min(40, sz - 4);
        int i = rng() % (sz - L);
        int j = i + L;

        // セグメント内の各セル訪問回数を数える
        map<pair<int, int>, int> seg_count;
        for (int k = i + 1; k < j; k++)
            seg_count[tour[k]]++;

        // 必須セル: セグメントを除去すると未訪問になるセル
        vector<pair<int, int>> req;
        for (auto& [cell, cnt] : seg_count) {
            if (vc[cell.first][cell.second] - cnt == 0)
                req.push_back(cell);
        }

        if ((int)req.size() > 6) continue; // 多すぎるのでスキップ

        // waypoints: tour[i] → req (何らかの順) → tour[j]
        // いくつかの順列を試して最短を探す
        int best_new_moves = L; // old segment length (moves)
        vector<pair<int, int>> best_new_path;

        int max_perm = ((int)req.size() <= 4) ? 24 : 10;
        // req.size()==0の場合もsort後1回試す
        sort(req.begin(), req.end());

        for (int perm_i = 0; perm_i < max_perm; perm_i++) {
            if (perm_i > 0) shuffle(req.begin(), req.end(), rng);

            // waypoints列
            vector<pair<int, int>> wps;
            wps.push_back(tour[i]);
            for (auto& r : req)
                wps.push_back(r);
            wps.push_back(tour[j]);

            // BFS距離の合計
            int total_moves = 0;
            bool ok = true;
            for (int w = 0; w + 1 < (int)wps.size(); w++) {
                int d = bfs_dist(wps[w].first, wps[w].second,
                                 wps[w + 1].first, wps[w + 1].second);
                if (d < 0) {
                    ok = false;
                    break;
                }
                total_moves += d;
            }

            if (ok && total_moves < best_new_moves) {
                best_new_moves = total_moves;
                // 実パスを構築
                best_new_path.clear();
                for (int w = 0; w + 1 < (int)wps.size(); w++) {
                    auto seg = bfs_return_path(wps[w].first, wps[w].second,
                                               wps[w + 1].first, wps[w + 1].second);
                    for (auto& c : seg)
                        best_new_path.push_back(c);
                }
            }

            if (req.empty()) break; // 順列なし
        }

        if (best_new_moves < L && !best_new_path.empty()) {
            // 古いセグメントのvcを減らす（tour[j]含む）
            for (int k = i + 1; k <= j; k++)
                vc[tour[k].first][tour[k].second]--;
            // 置換: [i+1, j]をnew_pathで置換（new_pathはtour[j]含む）
            tour.erase(tour.begin() + i + 1, tour.begin() + j + 1);
            tour.insert(tour.begin() + i + 1,
                        best_new_path.begin(), best_new_path.end());
            // 新しいセグメントのvcを増やす
            for (auto& [x, y] : best_new_path)
                vc[x][y]++;
            improved++;
        }
    }

    cerr << "optimize: " << improved << " improvements" << endl;
    return tour;
}

// DFSオイラーツアー（フォールバック用）
vector<pair<int, int>> dfs_euler_tour() {
    vector<vector<bool>> vis(N, vector<bool>(N, false));
    vector<pair<int, int>> path;
    path.emplace_back(0, 0);

    function<void(int, int)> dfs = [&](int x, int y) {
        vis[x][y] = true;
        for (int d = 0; d < 4; d++) {
            if (!can_go(x, y, d)) continue;
            int nx = x + dx[d], ny = y + dy[d];
            if (vis[nx][ny]) continue;
            path.emplace_back(nx, ny);
            dfs(nx, ny);
            path.emplace_back(x, y);
        }
    };
    dfs(0, 0);
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int AK, AM, AW;
    cin >> N >> AK >> AM >> AW;
    wall_v.resize(N);
    wall_h.resize(N - 1);
    for (int i = 0; i < N; i++)
        cin >> wall_v[i];
    for (int i = 0; i < N - 1; i++)
        cin >> wall_h[i];

    mt19937 rng(42);

    vector<pair<int, int>> tour;

    // 1. ブロック法でハミルトン閉路
    tour = block_hamiltonian_cycle();
    if (!tour.empty()) {
        cerr << "BLOCK" << endl;
    }

    // 2. Warnsdorff法
    if (tour.empty()) {
        auto result = find_hamiltonian(rng);
        if (!result.path.empty() && result.is_cycle) {
            tour = result.path;
            tour.emplace_back(0, 0);
            cerr << "CYCLE" << endl;
        } else if (!result.path.empty()) {
            tour = result.path;
            auto [ex, ey] = result.path.back();
            auto ret = bfs_return_path(ex, ey, 0, 0);
            for (auto& p : ret)
                tour.push_back(p);
            cerr << "PATH return=" << ret.size() << endl;
        } else {
            tour = dfs_euler_tour();
            cerr << "DFS" << endl;
        }
    }

    // ツアー最適化（ハミルトン閉路でなければ短縮を試みる）
    int N2 = N * N;
    if ((int)tour.size() > N2 + 1) {
        int before = tour.size();
        tour = optimize_tour(tour, rng);
        cerr << "tour: " << before << " -> " << tour.size() << endl;
    }

    // ステップ列生成
    vector<Step> steps;
    int dir = 1; // 初期向き R
    int x = 0, y = 0;

    auto turn = [&](int nd) {
        while (dir != nd) {
            if ((dir + 1) % 4 == nd) {
                steps.push_back({'R'});
                dir = (dir + 1) % 4;
            } else {
                steps.push_back({'L'});
                dir = (dir + 3) % 4;
            }
        }
    };

    for (size_t i = 1; i < tour.size(); i++) {
        auto [nx, ny] = tour[i];
        int nd;
        if (nx == x - 1)
            nd = 0;
        else if (ny == y + 1)
            nd = 1;
        else if (nx == x + 1)
            nd = 2;
        else
            nd = 3;

        turn(nd);
        steps.push_back({'F'});
        x = nx;
        y = ny;
    }

    // 初期方向(R=1)に戻す
    turn(1);

    int M = steps.size();

    // === 出力 ===
    cout << 1 << "\n";
    cout << M << " 0 0 R\n";

    for (int i = 0; i < M; i++) {
        char a = steps[i].act;
        int nxt = (i + 1) % M;
        char wall_a = (a == 'F') ? 'R' : a;
        cout << a << " " << nxt << " " << wall_a << " " << nxt << "\n";
    }

    // 壁追加なし
    for (int i = 0; i < N; i++)
        cout << string(N - 1, '0') << "\n";
    for (int i = 0; i < N - 1; i++)
        cout << string(N, '0') << "\n";

    return 0;
}
