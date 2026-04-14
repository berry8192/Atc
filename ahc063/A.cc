#include <bits/stdc++.h>
using namespace std;

const int DR[] = {-1, 1, 0, 0};
const int DC[] = {0, 0, -1, 1};
const char DIRC[] = "UDLR";

int N, M, C;
vector<int> d;
vector<vector<int>> board;
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

    void apply(int dir, string &ans) {
        assert(can_move(dir));
        Pos next = {head().r + DR[dir], head().c + DC[dir]};
        ans += DIRC[dir];
        body.push_front(next);
        if (board[next.r][next.c] > 0) {
            colors.push_back(board[next.r][next.c]);
            board[next.r][next.c] = 0;
        } else {
            body.pop_back();
            for (int h = 1; h <= size() - 2; h++) {
                if (body[h] == next) {
                    for (int i = h + 1; i < size(); i++)
                        board[body[i].r][body[i].c] = colors[i];
                    body.resize(h + 1);
                    colors.resize(h + 1);
                    break;
                }
            }
        }
    }
};

// from→toへの最短経路。blocked内は通れない（toを除く）
vector<int> bfs_path(Pos from, Pos to, const set<Pos> &blocked) {
    if (from == to) return {};
    auto idx = [&](Pos p) { return p.r * N + p.c; };
    vector<int> prev(N * N, -1);
    vector<bool> vis(N * N, false);
    queue<Pos> q;
    vis[idx(from)] = true;
    q.push(from);
    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        for (int dir = 0; dir < 4; dir++) {
            Pos nxt = {cur.r + DR[dir], cur.c + DC[dir]};
            if (!nxt.in_bounds() || vis[idx(nxt)]) continue;
            if (blocked.count(nxt) && nxt != to) continue;
            vis[idx(nxt)] = true;
            prev[idx(nxt)] = dir;
            if (nxt == to) {
                vector<int> path;
                for (Pos c = to; c != from; ) {
                    int d = prev[idx(c)];
                    path.push_back(d);
                    c = {c.r - DR[d], c.c - DC[d]};
                }
                reverse(path.begin(), path.end());
                return path;
            }
            q.push(nxt);
        }
    }
    return {};
}

// Dijkstra: 間違い色の餌通過はコスト高
vector<int> dijkstra_to_food(const Snake &snake, Pos to, int target_color) {
    const int WRONG_COST = 10000;
    auto idx = [&](Pos p) { return p.r * N + p.c; };
    set<Pos> blocked(snake.body.begin() + 1, snake.body.end());

    vector<int> dist(N * N, INT_MAX);
    vector<int> prev(N * N, -1);
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
            if (board[nxt.r][nxt.c] > 0 && board[nxt.r][nxt.c] != target_color && nxt != to)
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

// 指定色の最近傍の到達可能な餌
Pos find_nearest_food(int color, const Snake &snake) {
    auto idx = [&](Pos p) { return p.r * N + p.c; };
    set<Pos> blocked(snake.body.begin() + 1, snake.body.end());

    vector<bool> vis(N * N, false);
    queue<Pos> q;
    Pos from = snake.head();
    vis[idx(from)] = true;
    q.push(from);
    while (!q.empty()) {
        Pos cur = q.front(); q.pop();
        if (board[cur.r][cur.c] == color && cur != from) return cur;
        for (int dir = 0; dir < 4; dir++) {
            Pos nxt = {cur.r + DR[dir], cur.c + DC[dir]};
            if (!nxt.in_bounds() || vis[idx(nxt)]) continue;
            if (blocked.count(nxt)) continue;
            vis[idx(nxt)] = true;
            q.push(nxt);
        }
    }
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    LOG.open("log.txt");

    cin >> N >> M >> C;
    d.resize(M);
    for (int i = 0; i < M; i++) cin >> d[i];
    board.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> board[i][j];

    LOG << "N=" << N << " M=" << M << " C=" << C << "\n";

    Snake snake;
    for (int i = 4; i >= 0; i--) {
        snake.body.push_back({i, 0});
        snake.colors.push_back(1);
    }

    string ans;
    int progress = 5;

    // body[progress-2]に移動 → h=progress-1で噛みちぎり → snake長さ=progress
    // 余分なbodyを放出する。food踏んでもOK（全部放出される）
    auto bite_to_restore = [&]() -> bool {
        if (snake.size() <= progress) return true;
        if (progress < 2) return false;

        const int MAX_MOVES = N * N * 4;
        for (int iter = 0; iter < MAX_MOVES; iter++) {
            if (snake.size() <= progress) return true;

            Pos bite_target = snake.body[progress - 2];

            // 直接隣接していれば移動
            for (int dir = 0; dir < 4; dir++) {
                if (!snake.can_move(dir)) continue;
                Pos next = {snake.head().r + DR[dir], snake.head().c + DC[dir]};
                if (next == bite_target) {
                    snake.apply(dir, ans);
                    return snake.size() <= progress;
                }
            }

            // BFS: body[1..progress-3]のみ避ける（food通過可）
            set<Pos> blocked;
            for (int i = 1; i <= progress - 3 && i < (int)snake.size() - 1; i++)
                blocked.insert(snake.body[i]);

            vector<int> path = bfs_path(snake.head(), bite_target, blocked);
            if (!path.empty()) {
                snake.apply(path[0], ans);
            } else {
                bool moved = false;
                for (int dir = 0; dir < 4; dir++) {
                    if (!snake.can_move(dir)) continue;
                    Pos next = {snake.head().r + DR[dir], snake.head().c + DC[dir]};
                    bool bad = false;
                    for (int i = 1; i <= progress - 3 && i < (int)snake.size() - 1; i++)
                        if (next == snake.body[i]) { bad = true; break; }
                    if (!bad) { snake.apply(dir, ans); moved = true; break; }
                }
                if (!moved) return false;
            }
        }
        return false;
    };

    while (progress < M && (int)ans.size() < 99000) {
        int tc = d[progress];
        Pos target = find_nearest_food(tc, snake);
        if (!target.valid()) {
            LOG << "[STUCK] progress=" << progress << " color=" << tc << "\n";
            break;
        }

        vector<int> path = dijkstra_to_food(snake, target, tc);
        if (path.empty()) {
            LOG << "[NO PATH] progress=" << progress << " color=" << tc << "\n";
            break;
        }

        for (int dir : path) snake.apply(dir, ans);

        // 余分な餌を食べた場合: bite_to_restoreでリカバリ後、再度d[progress]を食べる
        for (int retry = 0; retry < 2 && snake.size() != progress + 1; retry++) {
            if (snake.size() > progress + 1) {
                // 蛇が長すぎ → bite_to_restore
                LOG << "  [retry] extra=" << (snake.size() - progress - 1)
                    << " at progress=" << progress << "\n";
                if (!bite_to_restore()) {
                    LOG << "  [retry] bite failed\n";
                    break;
                }
            }
            if (snake.size() < progress + 1) {
                // bite後にd[progress]をまだ食べていない → 再度食べる
                target = find_nearest_food(tc, snake);
                if (!target.valid()) break;
                path = dijkstra_to_food(snake, target, tc);
                if (path.empty()) break;
                for (int dir : path) snake.apply(dir, ans);
            }
        }

        LOG << "d[" << progress << "]=" << tc
            << " turn=" << (int)ans.size()
            << " len=" << snake.size()
            << (snake.size() == progress + 1 ? "" : " [EXTRA]") << "\n";

        progress++;
    }

    LOG << "\n--- result ---\n";
    LOG << "progress=" << progress << "/" << M
        << " turns=" << (int)ans.size()
        << " snake_len=" << snake.size() << "\n";
    int E = 0;
    for (int i = 0; i < (int)snake.size() && i < M; i++)
        if (snake.colors[i] != d[i]) E++;
    int score = (int)ans.size() + 10000 * (E + 2 * max(0, M - (int)snake.size()));
    LOG << "E=" << E << " missing=" << max(0, M - (int)snake.size())
        << " score=" << score << "\n";

    for (char c : ans) cout << c << "\n";
    LOG.close();
    return 0;
}
