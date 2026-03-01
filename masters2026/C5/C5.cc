#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> wall_v, wall_h;
int dx[4] = {-1, 0, 1, 0}; // U R D L
int dy[4] = {0, 1, 0, -1};
const char* dc = "URDL";

bool can_go(int x, int y, int d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= N || ny < 0 || ny >= N) return false;
    if (d == 0) return wall_h[nx][ny] == '0';
    if (d == 2) return wall_h[x][y] == '0';
    if (d == 1) return wall_v[x][y] == '0';
    if (d == 3) return wall_v[x][ny] == '0';
    return false;
}

// 操作種別
enum Op { RUN_R, RUN_L, TURN_R, TURN_L, STEP_F };

// 操作を適用: (x,y,dir) -> (nx,ny,nd)、visited更新、追加マス数を返す
int apply_op(int x, int y, int dir, Op op, int& nx, int& ny, int& nd,
             bitset<400>& visited) {
    int added = 0;
    if (op == RUN_R || op == RUN_L) {
        int cx = x, cy = y;
        while (can_go(cx, cy, dir)) {
            cx += dx[dir]; cy += dy[dir];
            int idx = cx * N + cy;
            if (!visited[idx]) { visited.set(idx); added++; }
        }
        nd = (op == RUN_R) ? (dir + 1) % 4 : (dir + 3) % 4;
        nx = cx; ny = cy;
    } else if (op == TURN_R) {
        nd = (dir + 1) % 4; nx = x; ny = y;
    } else if (op == TURN_L) {
        nd = (dir + 3) % 4; nx = x; ny = y;
    } else { // STEP_F
        nx = x + dx[dir]; ny = y + dy[dir]; nd = dir;
        int idx = nx * N + ny;
        if (!visited[idx]) { visited.set(idx); added++; }
    }
    return added;
}

// BFS最短帰還路
vector<pair<int,int>> bfs_return_path(int sx, int sy, int gx, int gy) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    vector<vector<pair<int,int>>> prev(N, vector<pair<int,int>>(N, {-1,-1}));
    queue<pair<int,int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
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
    vector<pair<int,int>> ret;
    if (dist[gx][gy] < 0) return ret;
    int cx = gx, cy = gy;
    while (cx != sx || cy != sy) {
        ret.emplace_back(cx, cy);
        auto [px, py] = prev[cx][cy];
        cx = px; cy = py;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int AK, AM, AW;
    cin >> N >> AK >> AM >> AW;
    wall_v.resize(N);
    wall_h.resize(N - 1);
    for (int i = 0; i < N; i++) cin >> wall_v[i];
    for (int i = 0; i < N - 1; i++) cin >> wall_h[i];

    int N2 = N * N;
    const int BEAM_W = 100;
    mt19937 rng(42);
    auto t0 = chrono::steady_clock::now();

    struct BNode {
        int x, y, dir;
        bitset<400> visited;
        int num_visited;
    };

    // 帰還BFS: (x,y,dir)状態空間で最少操作数を返す
    auto encode = [&](int x, int y, int d) { return (x * N + y) * 4 + d; };
    int SS = N * N * 4;

    auto return_cost = [&](int fx, int fy, int fd, int gx, int gy, int gd) -> int {
        vector<int> dist_r(SS, -1);
        int start_s = encode(fx, fy, fd);
        int goal_s = encode(gx, gy, gd);
        if (start_s == goal_s) return 0;
        dist_r[start_s] = 0;
        queue<int> bq;
        bq.push(start_s);
        while (!bq.empty()) {
            int s = bq.front(); bq.pop();
            int bx = s / 4 / N, by = s / 4 % N, bd = s % 4;
            Op try_ops[] = {RUN_R, RUN_L, TURN_R, TURN_L, STEP_F};
            for (Op op : try_ops) {
                int nx, ny, nd;
                if (op == STEP_F && !can_go(bx, by, bd)) continue;
                if ((op == RUN_R || op == RUN_L) && !can_go(bx, by, bd)) continue;
                if (op == RUN_R || op == RUN_L) {
                    int cx = bx, cy = by;
                    while (can_go(cx, cy, bd)) { cx += dx[bd]; cy += dy[bd]; }
                    nd = (op == RUN_R) ? (bd+1)%4 : (bd+3)%4;
                    nx = cx; ny = cy;
                } else if (op == TURN_R) {
                    nx = bx; ny = by; nd = (bd+1)%4;
                } else if (op == TURN_L) {
                    nx = bx; ny = by; nd = (bd+3)%4;
                } else {
                    nx = bx + dx[bd]; ny = by + dy[bd]; nd = bd;
                }
                int ns = encode(nx, ny, nd);
                if (dist_r[ns] >= 0) continue;
                dist_r[ns] = dist_r[s] + 1;
                if (ns == goal_s) return dist_r[ns];
                bq.push(ns);
            }
        }
        return 9999;
    };

    auto return_path = [&](int fx, int fy, int fd, int gx, int gy, int gd) -> vector<Op> {
        vector<int> dist_r(SS, -1);
        vector<int> prev_r(SS, -1);
        vector<Op> prev_op(SS);
        int start_s = encode(fx, fy, fd);
        int goal_s = encode(gx, gy, gd);
        if (start_s == goal_s) return {};
        dist_r[start_s] = 0;
        queue<int> bq;
        bq.push(start_s);
        while (!bq.empty() && dist_r[goal_s] < 0) {
            int s = bq.front(); bq.pop();
            int bx = s / 4 / N, by = s / 4 % N, bd = s % 4;
            Op try_ops[] = {RUN_R, RUN_L, TURN_R, TURN_L, STEP_F};
            for (Op op : try_ops) {
                int nx, ny, nd;
                if (op == STEP_F && !can_go(bx, by, bd)) continue;
                if ((op == RUN_R || op == RUN_L) && !can_go(bx, by, bd)) continue;
                if (op == RUN_R || op == RUN_L) {
                    int cx = bx, cy = by;
                    while (can_go(cx, cy, bd)) { cx += dx[bd]; cy += dy[bd]; }
                    nd = (op == RUN_R) ? (bd+1)%4 : (bd+3)%4;
                    nx = cx; ny = cy;
                } else if (op == TURN_R) {
                    nx = bx; ny = by; nd = (bd+1)%4;
                } else if (op == TURN_L) {
                    nx = bx; ny = by; nd = (bd+3)%4;
                } else {
                    nx = bx + dx[bd]; ny = by + dy[bd]; nd = bd;
                }
                int ns = encode(nx, ny, nd);
                if (dist_r[ns] >= 0) continue;
                dist_r[ns] = dist_r[s] + 1;
                prev_r[ns] = s;
                prev_op[ns] = op;
                bq.push(ns);
            }
        }
        vector<Op> ret;
        int cs = goal_s;
        while (cs != start_s) {
            ret.push_back(prev_op[cs]);
            cs = prev_r[cs];
        }
        reverse(ret.begin(), ret.end());
        return ret;
    };

    // 開始点候補: 角→辺→ランダム
    vector<tuple<int,int,int>> starts;
    int corners[][2] = {{0,0},{0,N-1},{N-1,0},{N-1,N-1}};
    for (auto [cx,cy] : corners)
        for (int d = 0; d < 4; d++)
            starts.push_back({cx, cy, d});
    for (int i = 0; i < N; i++)
        for (int d = 0; d < 4; d++) {
            starts.push_back({0, i, d});
            starts.push_back({N-1, i, d});
            starts.push_back({i, 0, d});
            starts.push_back({i, N-1, d});
        }

    // Phase 1: 高速探索（経路復元なし）
    int best_total = INT_MAX;
    vector<Op> best_ops;
    int best_sx, best_sy, best_sd;

    auto run_beam = [&](int sx, int sy, int sd, bool find_only)
        -> pair<int, vector<Op>>
    {
        // find_only=true: ステップ数+帰還コストだけ返す（ops空）
        // find_only=false: 経路復元付きで返す

        struct Node {
            int x, y, dir;
            bitset<400> visited;
            int num_visited;
            int parent;
            Op op;
        };

        vector<Node> all_nodes;
        {
            Node root;
            root.x = sx; root.y = sy; root.dir = sd;
            root.visited.reset();
            root.visited.set(sx * N + sy);
            root.num_visited = 1;
            root.parent = -1;
            root.op = RUN_R;
            all_nodes.push_back(root);
        }

        vector<int> beam = {0};
        int found_idx = -1;

        for (int step = 0; step < 1500 && found_idx < 0; step++) {
            vector<Node> beam_nodes;
            beam_nodes.reserve(beam.size());
            for (int bi : beam) beam_nodes.push_back(all_nodes[bi]);

            vector<pair<int, int>> candidates;

            for (int b = 0; b < (int)beam.size(); b++) {
                auto& node = beam_nodes[b];
                int bi = beam[b];
                bool at_wall = !can_go(node.x, node.y, node.dir);
                bool parent_is_turn = (node.op == TURN_R || node.op == TURN_L);

                Op cand_ops[5];
                int n_ops = 0;
                if (at_wall) {
                    cand_ops[n_ops++] = TURN_R;
                    cand_ops[n_ops++] = TURN_L;
                } else {
                    cand_ops[n_ops++] = RUN_R;
                    cand_ops[n_ops++] = RUN_L;
                    {
                        if (!parent_is_turn) {
                            cand_ops[n_ops++] = TURN_R;
                            cand_ops[n_ops++] = TURN_L;
                        }
                        cand_ops[n_ops++] = STEP_F;
                    }
                }

                for (int oi = 0; oi < n_ops; oi++) {
                    Op op = cand_ops[oi];
                    Node child;
                    child.visited = node.visited;
                    child.num_visited = node.num_visited;
                    int nx, ny, nd;
                    int added = apply_op(node.x, node.y, node.dir, op,
                                         nx, ny, nd, child.visited);
                    child.x = nx; child.y = ny; child.dir = nd;
                    child.num_visited += added;
                    if (find_only) {
                        child.parent = -1; child.op = op;
                    } else {
                        child.parent = bi; child.op = op;
                    }
                    int idx = all_nodes.size();
                    all_nodes.push_back(child);
                    candidates.push_back({idx, child.num_visited});
                }
            }

            sort(candidates.begin(), candidates.end(),
                 [](auto& a, auto& b) { return a.second > b.second; });
            if ((int)candidates.size() > BEAM_W)
                candidates.resize(BEAM_W);

            beam.clear();
            // (x,y,dir)重複排除: 同じ状態は上位2個まで
            int state_cnt[1600] = {};
            for (auto& [idx, nv] : candidates) {
                if ((int)beam.size() >= BEAM_W) break;
                auto& nd = all_nodes[idx];
                int key = (nd.x * N + nd.y) * 4 + nd.dir;
                if (++state_cnt[key] > 2) continue;
                beam.push_back(idx);
                if (nd.num_visited == N2) { found_idx = idx; break; }
            }

            if (find_only && found_idx < 0) {
                // メモリ節約: 使わないノードをbeamだけ残す
                if ((int)all_nodes.size() > BEAM_W * 10) {
                    vector<Node> new_nodes;
                    map<int, int> remap;
                    for (int bi : beam) {
                        remap[bi] = new_nodes.size();
                        new_nodes.push_back(all_nodes[bi]);
                    }
                    all_nodes = move(new_nodes);
                    vector<int> new_beam;
                    for (int bi : beam) new_beam.push_back(remap[bi]);
                    beam = new_beam;
                }
            }
        }

        if (found_idx < 0) return {9999, {}};

        auto& fnode = all_nodes[found_idx];
        int rc = return_cost(fnode.x, fnode.y, fnode.dir, sx, sy, sd);

        if (find_only) {
            // ステップ数を数える（ノードの深さ）
            // found_idxのステップ数 = beamのstep+1だが、正確にはparent chainで数える
            // find_onlyではparent=-1にしたので数えられない → stepをトラック
            // 簡易: all_nodes.size()から推定は不正確
            // → found_idxのnum_visitedからは推定不能
            // → step数を別途返す必要がある
            // ここでは概算としてfound_idx直前のbeamステップ数を使う
            // 実際には再実行で正確に取得するので問題ない
            return {-1, {}}; // 特殊値: 成功を示す
        }

        // 経路復元
        vector<Op> ops;
        int ci = found_idx;
        while (all_nodes[ci].parent >= 0) {
            ops.push_back(all_nodes[ci].op);
            ci = all_nodes[ci].parent;
        }
        reverse(ops.begin(), ops.end());

        auto ret_ops = return_path(fnode.x, fnode.y, fnode.dir, sx, sy, sd);
        ops.insert(ops.end(), ret_ops.begin(), ret_ops.end());
        return {(int)ops.size(), ops};
    };

    // Phase 1 & 2 統合: 経路復元もやりつつ、メモリ圧縮で高速化
    for (int trial = 0; ; trial++) {
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - t0).count();
        if (elapsed > 1800) break;

        int sx, sy, sd;
        if (trial < (int)starts.size()) {
            auto [a, b, c] = starts[trial];
            sx = a; sy = b; sd = c;
        } else {
            sx = rng() % N; sy = rng() % N; sd = rng() % 4;
        }

        auto [total, ops] = run_beam(sx, sy, sd, false);
        if (total >= 9999) continue;

        if (total < best_total) {
            best_total = total;
            best_ops = ops;
            best_sx = sx; best_sy = sy; best_sd = sd;
            cerr << "trial=" << trial << " states=" << total << endl;
        }
    }

    cerr << "best_total=" << best_total << endl;

    if (best_total == INT_MAX) {
        // フォールバック: 全マスに1台
        cerr << "FALLBACK" << endl;
        cout << N * N << "\n";
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                cout << "1 " << i << " " << j << " U\n";
                cout << "R 0 R 0\n";
            }
    } else {
        int M = best_total;
        cout << 1 << "\n";
        cout << M << " " << best_sx << " " << best_sy << " " << dc[best_sd] << "\n";
        for (int i = 0; i < M; i++) {
            int nxt = (i + 1) % M;
            Op op = best_ops[i];
            if (op == RUN_R) {
                cout << "F " << i << " R " << nxt << "\n";
            } else if (op == RUN_L) {
                cout << "F " << i << " L " << nxt << "\n";
            } else if (op == TURN_R) {
                cout << "R " << nxt << " R " << nxt << "\n";
            } else if (op == TURN_L) {
                cout << "L " << nxt << " L " << nxt << "\n";
            } else { // STEP_F
                cout << "F " << nxt << " R " << nxt << "\n";
            }
        }
    }

    // 壁追加なし
    for (int i = 0; i < N; i++) cout << string(N - 1, '0') << "\n";
    for (int i = 0; i < N - 1; i++) cout << string(N, '0') << "\n";

    return 0;
}
