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

// 蛇の頭から全マスへのBFS距離（ボディを障害物として）
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

// 次に食べる目標餌を選ぶ（BFS距離 + 1手先の距離で簡易評価）
Pos choose_target_food(const Snake &snake, const vector<vector<int>> &brd, int progress) {
    if (progress >= M) return {};
    int tc = d[progress];
    auto idx = [](Pos p) { return p.r * N + p.c; };
    auto head_dists = bfs_all_dist(snake);

    Pos best;
    int best_score = INT_MAX;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (brd[r][c] != tc) continue;
            Pos food = {r, c};
            int d1 = head_dists[idx(food)];
            if (d1 == INT_MAX) continue;

            // 次の目標色への最近傍距離（マンハッタン近似）
            int d2 = 0;
            if (progress + 1 < M) {
                int nc = d[progress + 1];
                int min_d2 = INT_MAX;
                for (int r2 = 0; r2 < N; r2++)
                    for (int c2 = 0; c2 < N; c2++)
                        if (brd[r2][c2] == nc)
                            min_d2 = min(min_d2, abs(r2 - r) + abs(c2 - c));
                d2 = (min_d2 == INT_MAX) ? 0 : min_d2;
            }

            int score = d1 * 2 + d2;
            if (score < best_score) { best_score = score; best = food; }
        }
    }
    return best;
}

const int BEAM_WIDTH = 100;
const int BEAM_DEPTH = 30;

struct BeamState {
    Snake snake;
    vector<vector<int>> brd;
    vector<int8_t> path;
    int eval_val;
    int max_eval;
    int target_dist; // 目標餌への距離（小さいほど良い）
};

// Dijkstraフォールバック用
vector<int> dijkstra_to_food(const Snake &snake, const vector<vector<int>> &brd,
                              Pos to, int target_color) {
    const int WRONG_COST = 1000;
    auto idx = [](Pos p) { return p.r * N + p.c; };
    set<Pos> blocked(snake.body.begin() + 1, snake.body.end());
    vector<int> dist(N * N, INT_MAX);
    vector<int> prev(N * N, -1);
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
            int cost = 1;
            if (brd[nxt.r][nxt.c] > 0 && brd[nxt.r][nxt.c] != target_color && nxt != to)
                cost = WRONG_COST;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    LOG.open("log_d.txt");

    cin >> N >> M >> C;
    d.resize(M);
    for (int i = 0; i < M; i++) cin >> d[i];
    vector<vector<int>> init_board(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> init_board[i][j];

    LOG << "N=" << N << " M=" << M << " C=" << C << "\n";

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
        if (stuck_rounds > 200) break;

        // 目標餌を選択（食べ物レベルの選択）
        Pos target = choose_target_food(cur_snake, cur_board, cur_progress);

        // ムーブレベルのビームサーチ（C.ccと同じ構造、目標距離を評価に追加）
        vector<BeamState> beam(1);
        {
            auto dists = target.valid() ? bfs_all_dist(cur_snake) : vector<int>();
            auto idx = [](Pos p) { return p.r * N + p.c; };
            int td = (target.valid() && !dists.empty()) ? dists[idx(target)] : 0;
            if (td == INT_MAX) td = 999;
            beam[0] = {cur_snake, cur_board, {}, cur_progress, cur_progress, td};
        }

        for (int depth = 0; depth < BEAM_DEPTH; depth++) {
            vector<BeamState> next_beam;
            next_beam.reserve(beam.size() * 4);
            auto idx = [](Pos p) { return p.r * N + p.c; };
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
                    // 目標への距離（BFSは重いので蛇の頭からのマンハッタン近似）
                    if (target.valid()) {
                        int dr = abs(ns.snake.head().r - target.r);
                        int dc = abs(ns.snake.head().c - target.c);
                        ns.target_dist = dr + dc;
                    } else {
                        ns.target_dist = 0;
                    }
                    next_beam.push_back(move(ns));
                }
            }
            if (next_beam.empty()) break;
            int keep = min((int)next_beam.size(), BEAM_WIDTH);
            partial_sort(next_beam.begin(), next_beam.begin() + keep, next_beam.end(),
                [](const BeamState &a, const BeamState &b) {
                    if (a.max_eval != b.max_eval) return a.max_eval > b.max_eval;
                    if (a.eval_val != b.eval_val) return a.eval_val > b.eval_val;
                    if (a.target_dist != b.target_dist) return a.target_dist < b.target_dist;
                    return a.snake.size() < b.snake.size();
                });
            next_beam.resize(keep);
            beam = move(next_beam);
        }

        if (beam.empty()) break;
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
                if (p > peak) { peak = p; commit_steps = s + 1; }
            }

            if (commit_steps > 0) {
                stuck_rounds = 0;
                for (int s = 0; s < commit_steps; s++) {
                    cur_snake.apply(best.path[s], cur_board);
                    ans += DIRC[(int)best.path[s]];
                }
            } else {
                stuck_rounds++;

                if (stuck_rounds >= 10) {
                    // Dijkstraフォールバック
                    int tc = d[cur_progress];
                    if (target.valid()) {
                        auto path = dijkstra_to_food(cur_snake, cur_board, target, tc);
                        if (!path.empty()) {
                            for (int dir : path) {
                                cur_snake.apply(dir, cur_board);
                                ans += DIRC[dir];
                            }
                            stuck_rounds = 0;
                            goto next_episode;
                        }
                    }
                }

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

    LOG << "\n--- result ---\n";
    LOG << "turns=" << (int)ans.size() << " snake_len=" << cur_snake.size() << "\n";
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
