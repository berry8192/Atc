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

// 先頭から何色一致しているか（最大到達点）
int prefix_match(const Snake &snake) {
    int k = 0;
    while (k < (int)snake.size() && k < M && snake.colors[k] == d[k]) k++;
    return k;
}

const int BEAM_WIDTH = 100;
const int BEAM_DEPTH = 60;

struct BeamState {
    Snake snake;
    vector<vector<int>> brd;
    vector<int8_t> path; // 今エピソードの先頭からの手順
    int eval_val;        // 現在のprefix_match
    int max_eval;        // パス中の最大prefix_match（評価キー）
};

// 間違い色を高コストとするDijkstraで target_color食べ物への経路を求める
vector<int> dijkstra_to_food(const Snake &snake, const vector<vector<int>> &brd,
                              Pos to, int target_color) {
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
        auto [d, ci] = pq.top(); pq.pop();
        if (d > dist[ci]) continue;
        Pos cur = {ci / N, ci % N};
        if (cur == to) break;
        for (int dir = 0; dir < 4; dir++) {
            Pos nxt = {cur.r + DR[dir], cur.c + DC[dir]};
            if (!nxt.in_bounds() || blocked.count(nxt)) continue;
            int cost = 1;
            if (brd[nxt.r][nxt.c] > 0 && brd[nxt.r][nxt.c] != target_color && nxt != to)
                cost = WRONG_COST;
            int nd = d + cost;
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
        int d = prev[idx(c)];
        path.push_back(d);
        c = {c.r - DR[d], c.c - DC[d]};
    }
    reverse(path.begin(), path.end());
    return path;
}

// BFSで蛇の頭から全マスへの距離を計算
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

// target_colorの食べ物を選ぶ（BFS距離 + 次の目標色への近さで評価）
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

    // 初期蛇: (4,0)(3,0)(2,0)(1,0)(0,0) 色はすべて1
    Snake init_snake;
    for (int i = 4; i >= 0; i--) {
        init_snake.body.push_back({i, 0});
        init_snake.colors.push_back(1);
    }

    string ans;
    Snake cur_snake = init_snake;
    vector<vector<int>> cur_board = init_board;

    auto time_limit = steady_clock::now() + milliseconds(1800);

    int stuck_rounds = 0;
    while ((int)ans.size() < 99000) {
        if (steady_clock::now() >= time_limit) break;

        int cur_progress = prefix_match(cur_snake);
        if (cur_progress >= M) break;
        if (stuck_rounds > 200) break; // 200エピソード進歩なし→諦め

        // ビームを初期化（現在状態1つ）
        vector<BeamState> beam(1);
        beam[0].snake    = cur_snake;
        beam[0].brd      = cur_board;
        beam[0].eval_val = cur_progress;
        beam[0].max_eval = cur_progress;

        for (int depth = 0; depth < BEAM_DEPTH; depth++) {
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
                    next_beam.push_back(move(ns));
                }
            }
            if (next_beam.empty()) break;
            int keep = min((int)next_beam.size(), BEAM_WIDTH);
            // max_eval優先 → eval_val → 蛇の短さ
            partial_sort(next_beam.begin(), next_beam.begin() + keep, next_beam.end(),
                [](const BeamState &a, const BeamState &b) {
                    if (a.max_eval != b.max_eval) return a.max_eval > b.max_eval;
                    if (a.eval_val != b.eval_val) return a.eval_val > b.eval_val;
                    return a.snake.size() < b.snake.size();
                });
            next_beam.resize(keep);
            beam = move(next_beam);
        }

        if (beam.empty()) break;

        // ベスト経路をmax_eval到達ステップまで実行（それ以降は捨てる）
        const auto &best = beam[0];
        if (best.path.empty()) break;

        // パスを再シミュレートしてmax到達点を特定
        {
            Snake tmp = cur_snake;
            vector<vector<int>> tmp_brd = cur_board;
            int peak = cur_progress;
            int commit_steps = 0;
            for (int s = 0; s < (int)best.path.size(); s++) {
                tmp.apply(best.path[s], tmp_brd);
                int p = prefix_match(tmp);
                if (p > peak) {
                    peak = p;
                    commit_steps = s + 1;
                }
            }

            if (commit_steps > 0) {
                // 進歩あり: max到達点までコミット
                stuck_rounds = 0;
                for (int s = 0; s < commit_steps; s++) {
                    cur_snake.apply(best.path[s], cur_board);
                    ans += DIRC[(int)best.path[s]];
                }
            } else {
                // 進歩なし
                stuck_rounds++;

                if (stuck_rounds >= 10) {
                    // Dijkstraフォールバック: 間違い色を避けて目標食べ物へフル経路
                    int tc = (cur_progress < M) ? d[cur_progress] : 0;
                    int nc = (cur_progress + 1 < M) ? d[cur_progress + 1] : 0;
                    Pos target = find_best_food(tc, nc, cur_snake, cur_board);
                    if (target.valid()) {
                        auto path = dijkstra_to_food(cur_snake, cur_board, target, tc);
                        if (!path.empty()) {
                            for (int dir : path) {
                                cur_snake.apply(dir, cur_board);
                                ans += DIRC[dir];
                            }
                            stuck_rounds = 0;
                            LOG << "  [dijkstra fallback] steps=" << path.size()
                                << " target=(" << target.r << "," << target.c << ")\n";
                            goto next_episode;
                        }
                    }
                }

                // フォールバックも失敗 or stuck_rounds < 10: ベスト経路を全手コミット
                for (int dir : best.path) {
                    cur_snake.apply(dir, cur_board);
                    ans += DIRC[(int)dir];
                }
            }
            next_episode:;
        }

        LOG << "progress=" << prefix_match(cur_snake)
            << "/" << M << " turns=" << (int)ans.size() << "\n";
    }

    // 結果ログ
    LOG << "\n--- result ---\n";
    LOG << "turns=" << (int)ans.size()
        << " snake_len=" << cur_snake.size() << "\n";
    int E = 0;
    for (int i = 0; i < (int)cur_snake.size() && i < M; i++)
        if (cur_snake.colors[i] != d[i]) E++;
    int score = (int)ans.size() + 10000 * (E + 2 * max(0, M - (int)cur_snake.size()));
    LOG << "E=" << E << " missing=" << max(0, M - (int)cur_snake.size())
        << " score=" << score << "\n";
    cerr << score << "\n";

    for (char c : ans) cout << c << "\n";
    LOG.close();
    return 0;
}
