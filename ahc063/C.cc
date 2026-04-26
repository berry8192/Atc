#include <bits/stdc++.h>
using namespace std;
using chrono::steady_clock;
using chrono::milliseconds;

const int DR[] = {-1, 1, 0, 0};
const int DC[] = {0, 0, -1, 1};
const char DIRC[] = "UDLR";

int N, M, C;
vector<int> d;
ofstream LOG;

struct Pos {
    int r, c;
    Pos() : r(-1), c(-1) {}
    Pos(int r, int c) : r(r), c(c) {}
    bool operator==(const Pos &o) const { return r == o.r && c == o.c; }
    bool operator!=(const Pos &o) const { return !(*this == o); }
    bool operator<(const Pos &o) const { return r != o.r ? r < o.r : c < o.c; }
    bool valid() const { return r >= 0; }
    bool in_bounds() const { return 0 <= r && r < N && 0 <= c && c < N; }
};

struct Snake {
    deque<Pos> body;
    deque<int> colors;
    int size() const { return (int)body.size(); }
    Pos head() const { return body[0]; }

    bool can_move(int dir) const {
        Pos next = {head().r + DR[dir], head().c + DC[dir]};
        if (!next.in_bounds()) return false;
        if (size() >= 2 && next == body[1]) return false;
        return true;
    }

    void apply(int dir, vector<vector<int>> &brd) {
        Pos next = {head().r + DR[dir], head().c + DC[dir]};
        body.push_front(next);
        if (brd[next.r][next.c] > 0) {
            colors.push_back(brd[next.r][next.c]);
            brd[next.r][next.c] = 0;
        } else {
            body.pop_back();
            for (int h = 1; h <= size() - 2; h++) {
                if (body[h] == next) {
                    for (int i = h + 1; i < size(); i++)
                        brd[body[i].r][body[i].c] = colors[i];
                    body.resize(h + 1);
                    colors.resize(h + 1);
                    break;
                }
            }
        }
    }
};

int prefix_match(const Snake &snake) {
    int k = 0;
    while (k < (int)snake.size() && k < M && snake.colors[k] == d[k]) k++;
    return k;
}

// 蛇の頭から全マスへのBFS距離
vector<int> bfs_all_dist(const Snake &snake) {
    auto idx = [](Pos p) { return p.r * N + p.c; };
    set<Pos> blocked(snake.body.begin() + 1, snake.body.end());
    vector<int> dist(N * N, INT_MAX);
    queue<Pos> q;
    dist[idx(snake.head())] = 0;
    q.push(snake.head());
    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        for (int dir = 0; dir < 4; dir++) {
            Pos nxt = {cur.r + DR[dir], cur.c + DC[dir]};
            if (!nxt.in_bounds() || dist[idx(nxt)] != INT_MAX || blocked.count(nxt)) continue;
            dist[idx(nxt)] = dist[idx(cur)] + 1;
            q.push(nxt);
        }
    }
    return dist;
}

// target_color の餌を選ぶ
Pos find_best_food(int color, int next_color, const Snake &snake, const vector<vector<int>> &brd) {
    auto idx = [](Pos p) { return p.r * N + p.c; };
    auto head_dists = bfs_all_dist(snake);
    Pos best;
    int best_score = INT_MAX;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (brd[r][c] != color) continue;
            int d1 = head_dists[idx({r, c})];
            if (d1 == INT_MAX) continue;
            int d2 = 0;
            if (next_color > 0) {
                int min_d2 = INT_MAX;
                for (int r2 = 0; r2 < N; r2++)
                    for (int c2 = 0; c2 < N; c2++)
                        if (brd[r2][c2] == next_color)
                            min_d2 = min(min_d2, abs(r2 - r) + abs(c2 - c));
                d2 = (min_d2 == INT_MAX) ? 0 : min_d2;
            }
            int score = d1 * 2 + d2;
            if (score < best_score) { best_score = score; best = {r, c}; }
        }
    }
    return best;
}

// BFS経路探索（食べ物も通過可能）
vector<int> bfs_to(const Snake &snake, Pos to) {
    auto idx = [](Pos p) { return p.r * N + p.c; };
    set<Pos> blocked(snake.body.begin() + 1, snake.body.end());
    vector<int> dist(N * N, INT_MAX);
    vector<int> prev(N * N, -1);
    queue<Pos> q;
    dist[idx(snake.head())] = 0;
    q.push(snake.head());
    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        if (cur == to) break;
        for (int dir = 0; dir < 4; dir++) {
            Pos nxt = {cur.r + DR[dir], cur.c + DC[dir]};
            if (!nxt.in_bounds() || dist[idx(nxt)] != INT_MAX || blocked.count(nxt)) continue;
            dist[idx(nxt)] = dist[idx(cur)] + 1;
            prev[idx(nxt)] = dir;
            q.push(nxt);
        }
    }
    if (dist[idx(to)] == INT_MAX) return {};
    vector<int> path;
    for (Pos c = to; c != snake.head(); ) {
        int dir = prev[idx(c)];
        path.push_back(dir);
        c = {c.r - DR[dir], c.c - DC[dir]};
    }
    reverse(path.begin(), path.end());
    return path;
}

// Dijkstra経路探索
vector<int> dijkstra_to_food(const Snake &snake, const vector<vector<int>> &brd,
                              Pos to, int target_color, bool strict) {
    const int WRONG_COST = 1000;
    auto idx = [](Pos p) { return p.r * N + p.c; };
    set<Pos> blocked(snake.body.begin() + 1, snake.body.end());

    int sz = N * N;
    vector<int> dist(sz, INT_MAX);
    vector<int> prev(sz, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    dist[idx(snake.head())] = 0;
    pq.push({0, idx(snake.head())});

    while (!pq.empty()) {
        auto [d_, ci] = pq.top(); pq.pop();
        if (d_ > dist[ci]) continue;
        Pos cur = {ci / N, ci % N};
        if (cur == to) break;
        for (int dir = 0; dir < 4; dir++) {
            Pos nxt = {cur.r + DR[dir], cur.c + DC[dir]};
            if (!nxt.in_bounds() || blocked.count(nxt)) continue;
            bool is_wrong = (brd[nxt.r][nxt.c] > 0 && brd[nxt.r][nxt.c] != target_color && nxt != to);
            if (strict && is_wrong) continue;
            int cost = is_wrong ? WRONG_COST : 1;
            int nd = d_ + cost;
            if (nd < dist[idx(nxt)]) {
                dist[idx(nxt)] = nd;
                prev[idx(nxt)] = dir;
                pq.push({nd, idx(nxt)});
            }
        }
    }
    if (dist[idx(to)] == INT_MAX) return {};
    vector<int> path;
    for (Pos c = to; c != snake.head(); ) {
        int dir = prev[idx(c)];
        path.push_back(dir);
        c = {c.r - DR[dir], c.c - DC[dir]};
    }
    reverse(path.begin(), path.end());
    return path;
}

// 経路を安全に適用（can_moveチェックつき）
int apply_path_safe(const vector<int> &path, Snake &snake, vector<vector<int>> &brd, string &ans) {
    int applied = 0;
    for (int dir : path) {
        if (!snake.can_move(dir)) break;
        snake.apply(dir, brd);
        ans += DIRC[dir];
        applied++;
    }
    return applied;
}

// 残り全食べ物を貪欲に食べる（順番問わず、miss=0確保用）
void eat_all_greedy(Snake &snake, vector<vector<int>> &brd, string &ans, int max_turns,
                    const steady_clock::time_point &time_limit) {
    int no_progress_steps = 0; // 食べ物が見つからない連続ステップ数
    while ((int)ans.size() < max_turns) {
        if (steady_clock::now() >= time_limit) break;
        if (no_progress_steps > 300) break; // 食べ物が取れない → 諦め

        auto dists = bfs_all_dist(snake);
        auto idx = [](Pos p) { return p.r * N + p.c; };
        Pos nearest;
        int min_d = INT_MAX;
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                if (brd[r][c] > 0 && dists[idx({r,c})] < min_d) {
                    min_d = dists[idx({r,c})];
                    nearest = {r, c};
                }
        if (!nearest.valid() || min_d == INT_MAX) {
            // 食べ物が見つからない → 自己噛みちぎりを避けつつ1歩移動
            bool moved = false;
            // まず噛みちぎりが起きない方向を優先
            set<Pos> body_set(snake.body.begin() + 2, snake.body.end());
            for (int dir = 0; dir < 4; dir++) {
                if (!snake.can_move(dir)) continue;
                Pos nxt = {snake.head().r + DR[dir], snake.head().c + DC[dir]};
                if (!body_set.count(nxt)) { // 体に当たらない
                    snake.apply(dir, brd);
                    ans += DIRC[dir];
                    moved = true;
                    no_progress_steps++;
                    break;
                }
            }
            if (!moved) {
                // 仕方なく噛みちぎり（しっぽ側=高いhを優先して進捗損失を最小化）
                int best_h = -1, best_dir = -1;
                for (int dir = 0; dir < 4; dir++) {
                    if (!snake.can_move(dir)) continue;
                    Pos nxt = {snake.head().r + DR[dir], snake.head().c + DC[dir]};
                    for (int h = (int)snake.size() - 2; h >= 2; h--) {
                        if (snake.body[h] == nxt) {
                            if (h > best_h) { best_h = h; best_dir = dir; }
                            break;
                        }
                    }
                }
                if (best_dir >= 0) {
                    snake.apply(best_dir, brd);
                    ans += DIRC[best_dir];
                    moved = true;
                    no_progress_steps++;
                }
            }
            if (!moved) break;
            continue;
        }

        auto path = bfs_to(snake, nearest);
        if (path.empty()) {
            no_progress_steps++;
            // パスが見つからない場合も噛みちぎりを避けて1歩移動
            set<Pos> body_set2(snake.body.begin() + 2, snake.body.end());
            for (int dir = 0; dir < 4; dir++) {
                if (!snake.can_move(dir)) continue;
                Pos nxt = {snake.head().r + DR[dir], snake.head().c + DC[dir]};
                if (!body_set2.count(nxt)) {
                    snake.apply(dir, brd);
                    ans += DIRC[dir];
                    break;
                }
            }
            continue;
        }
        no_progress_steps = 0;
        int applied = apply_path_safe(path, snake, brd, ans);
        if (applied == 0) break;
    }
}

int BEAM_WIDTH = 100;
int BEAM_DEPTH = 90;

struct BeamState {
    Snake snake;
    vector<vector<int>> brd;
    vector<int8_t> path;
    int eval_val;
    int max_eval;
    int target_dist;
    int wrong_eaten;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    LOG.open("log_c.txt");

    cin >> N >> M >> C;
    d.resize(M);
    for (int i = 0; i < M; i++) cin >> d[i];
    vector<vector<int>> init_board(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> init_board[i][j];

    LOG << "N=" << N << " M=" << M << " C=" << C << "\n";

    // Nに応じてビームパラメータを調整（大きいNでは軽くする）
    if (N >= 15) { BEAM_DEPTH = 50; BEAM_WIDTH = 60; }
    else if (N >= 13) { BEAM_DEPTH = 70; BEAM_WIDTH = 80; }
    LOG << "BEAM_DEPTH=" << BEAM_DEPTH << " BEAM_WIDTH=" << BEAM_WIDTH << "\n";

    Snake init_snake;
    for (int i = 4; i >= 0; i--) {
        init_snake.body.push_back({i, 0});
        init_snake.colors.push_back(1);
    }

    string best_ans;
    int best_progress = -1;
    bool best_complete = false;
    auto time_limit = steady_clock::now() + milliseconds(1800);

    while (steady_clock::now() < time_limit) {
    string ans;
    Snake cur_snake = init_snake;
    vector<vector<int>> cur_board = init_board;

    int stuck_rounds = 0;
    int max_progress_ever = prefix_match(init_snake); // 新しい最高値を達成したときのみリセット

    while ((int)ans.size() < 99000) {
        if (steady_clock::now() >= time_limit) break;

        int cur_progress = prefix_match(cur_snake);
        if (cur_progress >= M) {
            if (!best_complete || (int)ans.size() < (int)best_ans.size()) {
                best_ans = ans;
                best_complete = true;
                best_progress = M;
            }
            break;
        }

        // 長時間スタックまたは残り時間僅少: 残り全食べ物を貪欲に食べる
        auto remaining_ms = chrono::duration_cast<milliseconds>(
            time_limit - steady_clock::now()).count();
        if (stuck_rounds > 200 || remaining_ms < 500) {
            LOG << "  [eat-all-mode] progress=" << cur_progress
                << " max_ever=" << max_progress_ever
                << " remaining_ms=" << remaining_ms << "\n";
            eat_all_greedy(cur_snake, cur_board, ans, 99000, time_limit);
            int final_prog = prefix_match(cur_snake);
            LOG << "  [eat-all-done] progress=" << final_prog
                << " len=" << cur_snake.size() << "\n";
            break;
        }

        int tc = d[cur_progress];
        int nc = (cur_progress + 1 < M) ? d[cur_progress + 1] : 0;
        Pos target = find_best_food(tc, nc, cur_snake, cur_board);

        // ビームサーチ
        vector<BeamState> beam(1);
        {
            int td = target.valid()
                ? abs(cur_snake.head().r - target.r) + abs(cur_snake.head().c - target.c)
                : 0;
            beam[0] = {cur_snake, cur_board, {}, cur_progress, cur_progress, td, 0};
        }

        for (int dep = 0; dep < BEAM_DEPTH; dep++) {
            vector<BeamState> next_beam;
            next_beam.reserve(beam.size() * 4);
            for (auto &st : beam) {
                for (int dir = 0; dir < 4; dir++) {
                    if (!st.snake.can_move(dir)) continue;
                    BeamState ns;
                    ns.snake = st.snake;
                    ns.brd   = st.brd;
                    ns.path  = st.path;
                    ns.snake.apply(dir, ns.brd);
                    ns.path.push_back((int8_t)dir);
                    ns.eval_val = prefix_match(ns.snake);
                    ns.max_eval = max(st.max_eval, ns.eval_val);
                    ns.target_dist = target.valid()
                        ? abs(ns.snake.head().r - target.r) + abs(ns.snake.head().c - target.c)
                        : 0;
                    bool ate_food = (ns.snake.size() > st.snake.size());
                    int expected_pos = ns.snake.size() - 1;
                    bool ate_wrong = ate_food && (expected_pos < M)
                                     && (ns.snake.colors.back() != d[expected_pos]);
                    ns.wrong_eaten = st.wrong_eaten + (ate_wrong ? 1 : 0);
                    next_beam.push_back(move(ns));
                }
            }
            if (next_beam.empty()) break;
            int keep = min((int)next_beam.size(), BEAM_WIDTH);
            partial_sort(next_beam.begin(), next_beam.begin() + keep, next_beam.end(),
                [](const BeamState &a, const BeamState &b) {
                    if (a.max_eval != b.max_eval) return a.max_eval > b.max_eval;
                    if (a.wrong_eaten != b.wrong_eaten) return a.wrong_eaten < b.wrong_eaten;
                    if (a.eval_val != b.eval_val) return a.eval_val > b.eval_val;
                    if (a.target_dist != b.target_dist) return a.target_dist < b.target_dist;
                    return a.snake.size() < b.snake.size();
                });
            next_beam.resize(keep);
            beam = move(next_beam);
        }

        if (beam.empty()) { stuck_rounds++; goto next_episode; }

        // max到達点を特定してコミット
        {
            const auto &best = beam[0];
            if (best.path.empty()) { stuck_rounds++; goto next_episode; }
            Snake tmp = cur_snake;
            vector<vector<int>> tmp_brd = cur_board;
            int peak = cur_progress;
            int commit_steps = 0;
            for (int s = 0; s < (int)best.path.size(); s++) {
                tmp.apply(best.path[s], tmp_brd);
                int p = prefix_match(tmp);
                if (p > peak) { peak = p; commit_steps = s + 1; }
            }

            if (commit_steps > 0) {
                // 進歩あり: max到達点まで適用
                for (int s = 0; s < commit_steps; s++) {
                    if (!cur_snake.can_move(best.path[s])) break;
                    cur_snake.apply(best.path[s], cur_board);
                    ans += DIRC[(int)best.path[s]];
                }
                int new_prog = prefix_match(cur_snake);
                if (new_prog > max_progress_ever) {
                    max_progress_ever = new_prog;
                    stuck_rounds = 0; // 新しい最高値のみリセット
                } else {
                    stuck_rounds++; // 同じかそれ以下: スタックカウント
                }
            } else {
                // 進歩なし
                stuck_rounds++;

                if (stuck_rounds >= 10 && target.valid()) {
                    // フォールバック1: 厳格Dijkstra
                    auto path = dijkstra_to_food(cur_snake, cur_board, target, tc, true);
                    if (!path.empty()) {
                        int prev_prog = cur_progress;
                        apply_path_safe(path, cur_snake, cur_board, ans);
                        int new_prog = prefix_match(cur_snake);
                        LOG << "  [strict-dijk] " << prev_prog << "->" << new_prog << "\n";
                        if (new_prog > max_progress_ever) { max_progress_ever = new_prog; stuck_rounds = 0; }
                        goto next_episode;
                    }

                    // フォールバック2: 許容Dijkstra（進歩しなければstuck_rounds増加）
                    path = dijkstra_to_food(cur_snake, cur_board, target, tc, false);
                    if (!path.empty()) {
                        int prev_prog = cur_progress;
                        apply_path_safe(path, cur_snake, cur_board, ans);
                        int new_prog = prefix_match(cur_snake);
                        LOG << "  [perm-dijk] " << prev_prog << "->" << new_prog << "\n";
                        if (new_prog > max_progress_ever) { max_progress_ever = new_prog; stuck_rounds = 0; }
                        goto next_episode;
                    }
                }

                // フォールバック失敗: ベスト経路を prefix_match が落ちない範囲で適用
                {
                    Snake tmp2 = cur_snake;
                    vector<vector<int>> tmp2_brd = cur_board;
                    int safe_steps = 0;
                    for (int s = 0; s < (int)best.path.size(); s++) {
                        if (!tmp2.can_move(best.path[s])) break;
                        tmp2.apply(best.path[s], tmp2_brd);
                        if (prefix_match(tmp2) >= cur_progress) {
                            safe_steps = s + 1;
                        }
                    }
                    // 1歩も安全でなければ最初の1歩だけ進む（停止を防ぐ）
                    if (safe_steps == 0 && !best.path.empty()) safe_steps = 1;
                    for (int s = 0; s < safe_steps; s++) {
                        if (!cur_snake.can_move(best.path[s])) break;
                        cur_snake.apply(best.path[s], cur_board);
                        ans += DIRC[(int)best.path[s]];
                    }
                }
            }
        }
        next_episode:;

        LOG << "progress=" << prefix_match(cur_snake)
            << "/" << M << " turns=" << (int)ans.size()
            << " len=" << cur_snake.size()
            << " stuck=" << stuck_rounds << "\n";
    }

    {
        int cur_prog = prefix_match(cur_snake);
        if (!best_complete) {
            if (cur_prog > best_progress ||
                (cur_prog == best_progress && (int)ans.size() < (int)best_ans.size())) {
                best_ans = ans;
                best_progress = cur_prog;
            }
        }
    }
    break; // 決定論的なのでリスタート不要

    } // リスタートループ終了

    Snake final_snake = init_snake;
    vector<vector<int>> final_board = init_board;
    for (char c : best_ans) {
        int dir = string("UDLR").find(c);
        final_snake.apply(dir, final_board);
    }
    LOG << "\n--- result ---\n";
    LOG << "turns=" << (int)best_ans.size()
        << " snake_len=" << final_snake.size() << "\n";
    int E = 0;
    for (int i = 0; i < (int)final_snake.size() && i < M; i++)
        if (final_snake.colors[i] != d[i]) E++;
    int score = (int)best_ans.size() + 10000 * (E + 2 * max(0, M - (int)final_snake.size()));
    LOG << "E=" << E << " missing=" << max(0, M - (int)final_snake.size())
        << " score=" << score << "\n";
    cerr << score << "\n";

    for (char c : best_ans) cout << c << "\n";
    LOG.close();
    return 0;
}
