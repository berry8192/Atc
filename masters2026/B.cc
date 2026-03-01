#include <bits/stdc++.h>
using namespace std;

static const int N = 20;

// ---------------------------------------------------------------------------
// Direction
// ---------------------------------------------------------------------------
enum Dir { DIR_U = 0, DIR_D = 1, DIR_L = 2, DIR_R = 3 };

Dir turn_right(Dir d) {
    static const Dir tbl[] = {DIR_R, DIR_L, DIR_U, DIR_D};
    return tbl[d];
}

Dir turn_left(Dir d) {
    static const Dir tbl[] = {DIR_L, DIR_R, DIR_D, DIR_U};
    return tbl[d];
}

pair<int, int> dir_delta(Dir d) {
    static const int dr[] = {-1, 1, 0, 0};
    static const int dc[] = {0, 0, -1, 1};
    return {dr[d], dc[d]};
}

char dir_to_char(Dir d) {
    static const char c[] = "UDLR";
    return c[d];
}

// ---------------------------------------------------------------------------
// Action
// ---------------------------------------------------------------------------
enum Action { ACT_F = 0, ACT_R = 1, ACT_L = 2 };

char action_to_char(Action a) {
    static const char c[] = "FRL";
    return c[a];
}

// ---------------------------------------------------------------------------
// Transition
// ---------------------------------------------------------------------------
struct Transition {
    Action action_open;
    int next_open;
    Action action_wall;
    int next_wall;
};

// ---------------------------------------------------------------------------
// Robot
// ---------------------------------------------------------------------------
struct Robot {
    vector<Transition> transitions;
    int row, col;
    Dir dir;
};

// ---------------------------------------------------------------------------
// Input
// ---------------------------------------------------------------------------
struct Input {
    int a_k, a_m, a_w;
    vector<vector<bool>> wall_v; // N rows x (N-1) cols
    vector<vector<bool>> wall_h; // (N-1) rows x N cols
};

// ---------------------------------------------------------------------------
// Output
// ---------------------------------------------------------------------------
struct Output {
    vector<Robot> robots;
    vector<vector<bool>> added_wall_v; // N rows x (N-1) cols
    vector<vector<bool>> added_wall_h; // (N-1) rows x N cols
};

vector<vector<bool>> empty_wall_v() {
    return vector<vector<bool>>(N, vector<bool>(N - 1, false));
}

vector<vector<bool>> empty_wall_h() {
    return vector<vector<bool>>(N - 1, vector<bool>(N, false));
}

// ---------------------------------------------------------------------------
// WallEdge
// ---------------------------------------------------------------------------
struct WallEdge {
    bool is_h; // true = H(i,j), false = V(i,j)
    int i, j;
};

// ---------------------------------------------------------------------------
// Grid
// ---------------------------------------------------------------------------
struct Grid {
    vector<vector<bool>> wall_v, wall_h;

    static Grid from_merged(const Input &inp, const vector<vector<bool>> &av,
                            const vector<vector<bool>> &ah) {
        Grid g;
        g.wall_v.resize(N, vector<bool>(N - 1));
        g.wall_h.resize(N - 1, vector<bool>(N));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N - 1; j++)
                g.wall_v[i][j] = inp.wall_v[i][j] || av[i][j];
        for (int i = 0; i < N - 1; i++)
            for (int j = 0; j < N; j++)
                g.wall_h[i][j] = inp.wall_h[i][j] || ah[i][j];
        return g;
    }

    static Grid from_input(const Input &inp) {
        Grid g;
        g.wall_v = inp.wall_v;
        g.wall_h = inp.wall_h;
        return g;
    }

    static Grid make(const Input &inp, const Output &out) {
        return from_merged(inp, out.added_wall_v, out.added_wall_h);
    }

    bool has_wall(int row, int col, Dir d) const {
        switch (d) {
        case DIR_U:
            return row == 0 || wall_h[row - 1][col];
        case DIR_D:
            return row >= N - 1 || wall_h[row][col];
        case DIR_L:
            return col == 0 || wall_v[row][col - 1];
        case DIR_R:
            return col >= N - 1 || wall_v[row][col];
        }
        return false;
    }

    void set_wall(const WallEdge &w, bool val) {
        if (w.is_h)
            wall_h[w.i][w.j] = val;
        else
            wall_v[w.i][w.j] = val;
    }

    void toggle_wall(const WallEdge &w) {
        if (w.is_h)
            wall_h[w.i][w.j] = !wall_h[w.i][w.j];
        else
            wall_v[w.i][w.j] = !wall_v[w.i][w.j];
    }
};

// ---------------------------------------------------------------------------
// parse_input
// ---------------------------------------------------------------------------
Input parse_input() {
    Input inp;
    int n;
    scanf("%d %d %d %d", &n, &inp.a_k, &inp.a_m, &inp.a_w);

    inp.wall_v.resize(N, vector<bool>(N - 1));
    for (int i = 0; i < N; i++) {
        char buf[32];
        scanf("%s", buf);
        for (int j = 0; j < N - 1; j++)
            inp.wall_v[i][j] = buf[j] == '1';
    }

    inp.wall_h.resize(N - 1, vector<bool>(N));
    for (int i = 0; i < N - 1; i++) {
        char buf[32];
        scanf("%s", buf);
        for (int j = 0; j < N; j++)
            inp.wall_h[i][j] = buf[j] == '1';
    }

    return inp;
}

// ---------------------------------------------------------------------------
// simulate_cells: 周期軌道上のユニークなセル一覧を返す
// ---------------------------------------------------------------------------
vector<pair<int, int>> simulate_cells(const Robot &robot, const Grid &grid) {
    int num_states = (int)robot.transitions.size();
    int config_size = N * N * 4 * num_states;
    vector<uint32_t> visited(config_size, 0);
    vector<pair<int, int>> path;
    path.reserve(config_size + 1);

    int row = robot.row, col = robot.col;
    Dir dir = robot.dir;
    int state = 0;

    int max_steps = config_size;
    for (int step = 0; step <= max_steps; step++) {
        int config_idx = ((row * N + col) * 4 + dir) * num_states + state;
        if (visited[config_idx] != 0) {
            int cycle_start = (int)visited[config_idx] - 1;
            bool cell_seen[N][N] = {};
            vector<pair<int, int>> cells;
            for (int k = cycle_start; k < (int)path.size(); k++) {
                auto [r, c] = path[k];
                if (!cell_seen[r][c]) {
                    cell_seen[r][c] = true;
                    cells.push_back({r, c});
                }
            }
            return cells;
        }
        visited[config_idx] = (uint32_t)(step + 1);
        path.push_back({row, col});

        bool wall_ahead = grid.has_wall(row, col, dir);
        const auto &trans = robot.transitions[state];
        Action action;
        int next_state;
        if (wall_ahead) {
            action = trans.action_wall;
            next_state = trans.next_wall;
        } else {
            action = trans.action_open;
            next_state = trans.next_open;
        }

        if (action == ACT_F) {
            auto [dr, dc] = dir_delta(dir);
            row += dr;
            col += dc;
        } else if (action == ACT_R) {
            dir = turn_right(dir);
        } else {
            dir = turn_left(dir);
        }
        state = next_state;
    }

    bool cell_seen[N][N] = {};
    vector<pair<int, int>> cells;
    for (auto [r, c] : path) {
        if (!cell_seen[r][c]) {
            cell_seen[r][c] = true;
            cells.push_back({r, c});
        }
    }
    return cells;
}

// ---------------------------------------------------------------------------
// simulate_count_fast: 配列ベースの高速シミュレーション（カバレッジ数のみ返す）
// ---------------------------------------------------------------------------
int simulate_count_fast(const Robot &robot, const Grid &grid,
                        vector<uint32_t> &visited,
                        vector<pair<int, int>> &path_buf) {
    int num_states = (int)robot.transitions.size();
    int max_steps = N * N * 4 * num_states;

    fill(visited.begin(), visited.end(), 0);
    path_buf.clear();

    int row = robot.row, col = robot.col;
    Dir dir = robot.dir;
    int state = 0;

    for (int step = 0; step <= max_steps; step++) {
        int config_idx = ((row * N + col) * 4 + dir) * num_states + state;
        if (visited[config_idx] != 0) {
            int cycle_start = (int)visited[config_idx] - 1;
            bool cell_seen[N][N] = {};
            int count = 0;
            for (int k = cycle_start; k < (int)path_buf.size(); k++) {
                auto [r, c] = path_buf[k];
                if (!cell_seen[r][c]) {
                    cell_seen[r][c] = true;
                    count++;
                }
            }
            return count;
        }
        visited[config_idx] = (uint32_t)(step + 1);
        path_buf.push_back({row, col});

        bool wall_ahead = grid.has_wall(row, col, dir);
        const auto &trans = robot.transitions[state];
        Action action;
        int next_state;
        if (wall_ahead) {
            action = trans.action_wall;
            next_state = trans.next_wall;
        } else {
            action = trans.action_open;
            next_state = trans.next_open;
        }

        if (action == ACT_F) {
            auto [dr, dc] = dir_delta(dir);
            row += dr;
            col += dc;
        } else if (action == ACT_R) {
            dir = turn_right(dir);
        } else {
            dir = turn_left(dir);
        }
        state = next_state;
    }

    bool cell_seen[N][N] = {};
    int count = 0;
    for (auto [r, c] : path_buf) {
        if (!cell_seen[r][c]) {
            cell_seen[r][c] = true;
            count++;
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// Robot factory functions
// ---------------------------------------------------------------------------

Robot make_spinner(int row, int col) {
    return Robot{{{ACT_R, 0, ACT_R, 0}}, row, col, DIR_U};
}

Robot make_boundary_tracer(int row, int col, Dir dir) {
    return Robot{{{ACT_F, 0, ACT_R, 0}}, row, col, dir};
}

Robot make_uturn(int row, int col, Dir dir) {
    return Robot{{{ACT_F, 0, ACT_R, 1}, {ACT_R, 0, ACT_R, 0}}, row, col, dir};
}

Robot make_zigzag(int row, int col, Dir dir) {
    return Robot{{
                     {ACT_F, 0, ACT_R, 1}, // S0
                     {ACT_F, 2, ACT_R, 1}, // S1
                     {ACT_R, 3, ACT_R, 3}, // S2
                     {ACT_F, 3, ACT_L, 4}, // S3
                     {ACT_F, 5, ACT_L, 4}, // S4
                     {ACT_L, 0, ACT_L, 0}, // S5
                 },
                 row,
                 col,
                 dir};
}

Robot make_boundary_tracer_left(int row, int col, Dir dir) {
    return Robot{{{ACT_F, 0, ACT_L, 0}}, row, col, dir};
}

Robot make_wall_follower(int row, int col, Dir dir) {
    return Robot{{
                     {ACT_R, 1, ACT_R, 1}, // S0
                     {ACT_F, 0, ACT_L, 2}, // S1
                     {ACT_F, 0, ACT_L, 3}, // S2
                     {ACT_F, 0, ACT_L, 4}, // S3
                     {ACT_F, 0, ACT_R, 4}, // S4
                 },
                 row,
                 col,
                 dir};
}

Robot make_left_wall_follower(int row, int col, Dir dir) {
    return Robot{{
                     {ACT_L, 1, ACT_L, 1}, // S0
                     {ACT_F, 0, ACT_R, 2}, // S1
                     {ACT_F, 0, ACT_R, 3}, // S2
                     {ACT_F, 0, ACT_R, 4}, // S3
                     {ACT_F, 0, ACT_L, 4}, // S4
                 },
                 row,
                 col,
                 dir};
}

// ---------------------------------------------------------------------------
// Union-Find
// ---------------------------------------------------------------------------
struct UnionFind {
    vector<int> parent, rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry)
            return false;
        if (rank_[rx] < rank_[ry])
            swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry])
            rank_[rx]++;
        return true;
    }
};

// ---------------------------------------------------------------------------
// build_corridors_with_boundaries
// ---------------------------------------------------------------------------
pair<vector<vector<bool>>, vector<vector<bool>>>
build_corridors_with_boundaries(const Input &inp,
                                const vector<int> &boundary_rows) {
    auto av = empty_wall_v();
    auto ah = empty_wall_h();

    for (int br : boundary_rows)
        for (int j = 0; j < N; j++)
            if (!inp.wall_h[br][j])
                ah[br][j] = true;

    UnionFind uf(N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 1; j++)
            if (!inp.wall_v[i][j])
                uf.unite(i * N + j, i * N + j + 1);

    for (int i = 0; i < N - 1; i++) {
        bool is_boundary = false;
        for (int br : boundary_rows)
            if (br == i) {
                is_boundary = true;
                break;
            }
        if (is_boundary)
            continue;
        for (int j = 0; j < N; j++)
            if (!inp.wall_h[i][j])
                uf.unite(i * N + j, (i + 1) * N + j);
    }

    for (int br : boundary_rows)
        for (int j = 0; j < N; j++) {
            if (inp.wall_h[br][j])
                continue;
            int u = br * N + j, v = (br + 1) * N + j;
            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                ah[br][j] = false;
            }
        }

    return {av, ah};
}

// ---------------------------------------------------------------------------
// build_corridors_vertical
// ---------------------------------------------------------------------------
pair<vector<vector<bool>>, vector<vector<bool>>>
build_corridors_vertical(const Input &inp, const vector<int> &boundary_cols) {
    auto av = empty_wall_v();
    auto ah = empty_wall_h();

    for (int bc : boundary_cols)
        for (int i = 0; i < N; i++)
            if (!inp.wall_v[i][bc])
                av[i][bc] = true;

    UnionFind uf(N * N);
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N; j++)
            if (!inp.wall_h[i][j])
                uf.unite(i * N + j, (i + 1) * N + j);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 1; j++) {
            bool is_boundary = false;
            for (int bc : boundary_cols)
                if (bc == j) {
                    is_boundary = true;
                    break;
                }
            if (is_boundary)
                continue;
            if (!inp.wall_v[i][j])
                uf.unite(i * N + j, i * N + j + 1);
        }

    for (int bc : boundary_cols)
        for (int i = 0; i < N; i++) {
            if (inp.wall_v[i][bc])
                continue;
            int u = i * N + bc, v = i * N + bc + 1;
            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                av[i][bc] = false;
            }
        }

    return {av, ah};
}

// ---------------------------------------------------------------------------
// Rng (xorshift64)
// ---------------------------------------------------------------------------
struct Rng {
    uint64_t state;
    Rng(uint64_t seed) : state(max(seed, (uint64_t)1)) {}
    uint64_t next() {
        state ^= state << 13;
        state ^= state >> 7;
        state ^= state << 17;
        return state;
    }
    template <class T> void shuffle(vector<T> &v) {
        for (int i = (int)v.size() - 1; i >= 1; i--) {
            int j = next() % (i + 1);
            swap(v[i], v[j]);
        }
    }
};

// ---------------------------------------------------------------------------
// count_added_walls
// ---------------------------------------------------------------------------
int count_added_walls(const vector<vector<bool>> &av,
                      const vector<vector<bool>> &ah) {
    int cnt = 0;
    for (auto &row : av)
        for (bool b : row)
            cnt += b;
    for (auto &row : ah)
        for (bool b : row)
            cnt += b;
    return cnt;
}

// ---------------------------------------------------------------------------
// optimize_walls: 壁除去を繰り返し実行（収束するまで）
// ---------------------------------------------------------------------------
void optimize_walls(const Input &inp, vector<vector<bool>> &av,
                    vector<vector<bool>> &ah, const Robot &robot,
                    uint64_t seed) {
    int num_states = (int)robot.transitions.size();
    int config_size = N * N * 4 * num_states;
    vector<uint32_t> visited_buf(config_size);
    vector<pair<int, int>> path_buf;
    path_buf.reserve(config_size + 1);
    Rng rng(seed);

    Grid grid = Grid::from_merged(inp, av, ah);

    for (;;) {
        vector<WallEdge> walls;
        for (int i = 0; i < N - 1; i++)
            for (int j = 0; j < N; j++)
                if (ah[i][j])
                    walls.push_back({true, i, j});
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N - 1; j++)
                if (av[i][j])
                    walls.push_back({false, i, j});

        rng.shuffle(walls);

        int removed = 0;
        for (auto &w : walls) {
            grid.set_wall(w, false);
            int cov = simulate_count_fast(robot, grid, visited_buf, path_buf);
            if (cov == N * N) {
                if (w.is_h)
                    ah[w.i][w.j] = false;
                else
                    av[w.i][w.j] = false;
                removed++;
            } else {
                grid.set_wall(w, true);
            }
        }
        if (removed == 0)
            break;
    }
}

// ---------------------------------------------------------------------------
// Timer
// ---------------------------------------------------------------------------
struct Timer {
    chrono::high_resolution_clock::time_point start;
    Timer() : start(chrono::high_resolution_clock::now()) {}
    long long elapsed_ms() const {
        return chrono::duration_cast<chrono::milliseconds>(
                   chrono::high_resolution_clock::now() - start)
            .count();
    }
};

// ---------------------------------------------------------------------------
// finalize_zigzag
// ---------------------------------------------------------------------------
Output *finalize_zigzag(const Input &inp, const Robot &robot,
                        const vector<WallEdge> &wall_candidates,
                        const vector<bool> &added, const Timer &timer) {
    auto av = empty_wall_v();
    auto ah = empty_wall_h();
    for (int idx = 0; idx < (int)added.size(); idx++) {
        if (added[idx]) {
            auto &w = wall_candidates[idx];
            if (w.is_h)
                ah[w.i][w.j] = true;
            else
                av[w.i][w.j] = true;
        }
    }

    optimize_walls(inp, av, ah, robot, 42);
    int w = count_added_walls(av, ah);
    fprintf(stderr, "Zigzag: W=%d, Time=%lldms\n", w, timer.elapsed_ms());

    auto *out = new Output{};
    out->robots.push_back(robot);
    out->added_wall_v = move(av);
    out->added_wall_h = move(ah);
    return out;
}

// ---------------------------------------------------------------------------
// solve_b_zigzag
// ---------------------------------------------------------------------------
Output *solve_b_zigzag(const Input &inp, long long deadline_ms) {
    Timer timer;

    vector<WallEdge> wall_candidates;
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N; j++)
            if (!inp.wall_h[i][j])
                wall_candidates.push_back({true, i, j});
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N - 1; j++)
            if (!inp.wall_v[i][j])
                wall_candidates.push_back({false, i, j});
    int num_candidates = (int)wall_candidates.size();

    // セル→近傍壁候補インデックス
    vector<vector<int>> cell_nearby_walls(N * N);
    for (int idx = 0; idx < num_candidates; idx++) {
        auto &w = wall_candidates[idx];
        pair<int, int> touched[2];
        if (w.is_h) {
            touched[0] = {w.i, w.j};
            touched[1] = {w.i + 1, w.j};
        } else {
            touched[0] = {w.i, w.j};
            touched[1] = {w.i, w.j + 1};
        }
        for (auto &[cr, cc] : touched) {
            if (cr >= N || cc >= N)
                continue;
            static const int dd[][2] = {
                {0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto &d : dd) {
                int nr = cr + d[0], nc = cc + d[1];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N)
                    cell_nearby_walls[nr * N + nc].push_back(idx);
            }
        }
    }
    for (auto &list : cell_nearby_walls) {
        sort(list.begin(), list.end());
        list.erase(unique(list.begin(), list.end()), list.end());
    }

    // Phase 0: マルチスタート
    int num_states = 6;
    int config_size = N * N * 4 * num_states;
    vector<uint32_t> visited_buf(config_size);
    vector<pair<int, int>> path_buf;
    path_buf.reserve(config_size + 1);
    Rng rng(42);

    Grid grid_input = Grid::from_input(inp);
    Robot best_robot = make_zigzag(0, 0, DIR_R);
    int best_init_cov = 0;

    Dir dirs[] = {DIR_U, DIR_D, DIR_L, DIR_R};
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            for (Dir d : dirs) {
                Robot robot = make_zigzag(r, c, d);
                int cov = simulate_count_fast(robot, grid_input, visited_buf,
                                              path_buf);
                if (cov > best_init_cov) {
                    best_init_cov = cov;
                    best_robot = robot;
                }
            }

    if (best_init_cov == N * N) {
        vector<bool> added(num_candidates, false);
        return finalize_zigzag(inp, best_robot, wall_candidates, added, timer);
    }

    fprintf(stderr, "Zigzag best start: (%d,%d) %c, cov=%d/%d\n",
            best_robot.row, best_robot.col, dir_to_char(best_robot.dir),
            best_init_cov, N * N);

    Robot robot = best_robot;

    vector<bool> added(num_candidates, false);
    Grid grid;
    grid.wall_v = inp.wall_v;
    grid.wall_h = inp.wall_h;
    int current_cov = best_init_cov;
    int current_walls = 0;

    // Phase 1: 貪欲フェーズ
    long long greedy_deadline = deadline_ms / 5;
    while (current_cov < N * N && timer.elapsed_ms() < greedy_deadline) {
        int best_idx = -1;
        int best_cov = current_cov;
        for (int idx = 0; idx < num_candidates; idx++) {
            if (added[idx])
                continue;
            grid.set_wall(wall_candidates[idx], true);
            int cov = simulate_count_fast(robot, grid, visited_buf, path_buf);
            if (cov > best_cov) {
                best_cov = cov;
                best_idx = idx;
            }
            grid.set_wall(wall_candidates[idx], false);
        }
        if (best_idx < 0)
            break;
        added[best_idx] = true;
        grid.set_wall(wall_candidates[best_idx], true);
        current_walls++;
        current_cov = best_cov;
    }

    if (current_cov == N * N) {
        return finalize_zigzag(inp, robot, wall_candidates, added, timer);
    }

    // Phase 2: 焼きなまし法
    int best_full_cov_walls = INT_MAX;
    vector<bool> best_full_cov_added;

    auto sa_score = [](int cov, int walls) -> double {
        return cov * 100.0 - walls;
    };
    double current_score = sa_score(current_cov, current_walls);

    // 未カバーセルを計算
    vector<int> uncovered;
    {
        auto cells = simulate_cells(robot, grid);
        bool covered[N * N] = {};
        for (auto [r, c] : cells)
            covered[r * N + c] = true;
        for (int i = 0; i < N * N; i++)
            if (!covered[i])
                uncovered.push_back(i);
    }

    double t_start = 200.0, t_end = 0.5;
    long long sa_start_ms = timer.elapsed_ms();

    uint64_t iterations = 0;
    while (timer.elapsed_ms() < deadline_ms) {
        iterations++;

        long long elapsed_ms = timer.elapsed_ms();
        double progress = (deadline_ms > sa_start_ms)
                              ? (double)(elapsed_ms - sa_start_ms) /
                                    (deadline_ms - sa_start_ms)
                              : 1.0;
        double temperature = t_start + (t_end - t_start) * min(progress, 1.0);

        int idx;
        if (!uncovered.empty() && rng.next() % 100 < 70) {
            int cell = uncovered[rng.next() % uncovered.size()];
            auto &nearby = cell_nearby_walls[cell];
            if (nearby.empty())
                idx = rng.next() % num_candidates;
            else
                idx = nearby[rng.next() % nearby.size()];
        } else {
            idx = rng.next() % num_candidates;
        }

        auto &wall = wall_candidates[idx];
        bool was_added = added[idx];
        grid.toggle_wall(wall);

        int new_cov = simulate_count_fast(robot, grid, visited_buf, path_buf);
        int new_walls = was_added ? current_walls - 1 : current_walls + 1;
        double new_score = sa_score(new_cov, new_walls);

        double delta = new_score - current_score;
        bool accept;
        if (delta >= 0)
            accept = true;
        else
            accept = ((double)(rng.next()) / (double)UINT64_MAX) <
                     exp(delta / temperature);

        if (accept) {
            added[idx] = !was_added;
            current_walls = new_walls;
            current_cov = new_cov;
            current_score = new_score;

            if (current_cov == N * N && current_walls < best_full_cov_walls) {
                best_full_cov_walls = current_walls;
                best_full_cov_added = added;
            }
        } else {
            grid.toggle_wall(wall);
        }

        if (iterations % 500 == 0) {
            uncovered.clear();
            auto cells = simulate_cells(robot, grid);
            bool covered_arr[N * N] = {};
            for (auto [r, c] : cells)
                covered_arr[r * N + c] = true;
            for (int i = 0; i < N * N; i++)
                if (!covered_arr[i])
                    uncovered.push_back(i);
        }
    }

    fprintf(stderr, "Zigzag SA: %llu iters, best_walls=%s, time=%lldms\n",
            (unsigned long long)iterations,
            best_full_cov_added.empty()
                ? "N/A"
                : to_string(best_full_cov_walls).c_str(),
            timer.elapsed_ms());

    if (!best_full_cov_added.empty()) {
        return finalize_zigzag(inp, robot, wall_candidates, best_full_cov_added,
                               timer);
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// solve_b_corridor
// ---------------------------------------------------------------------------
Output solve_b_corridor(const Input &inp, long long deadline_ms) {
    Robot robot = make_wall_follower(0, 0, DIR_R);
    Timer timer;

    struct CorridorConfig {
        bool is_horizontal;
        vector<int> boundaries;
    };
    vector<CorridorConfig> configs;
    {
        vector<int> v1, v2, v3, v4;
        for (int p = 0; p < N / 2 - 1; p++)
            v1.push_back(p * 2 + 1);
        for (int p = 0; p < N / 2; p++)
            v2.push_back(p * 2);
        for (int p = 0; p < N / 2 - 1; p++)
            v3.push_back(p * 2 + 1);
        for (int p = 0; p < N / 2; p++)
            v4.push_back(p * 2);
        configs.push_back({true, v1});
        configs.push_back({true, v2});
        configs.push_back({false, v3});
        configs.push_back({false, v4});
    }

    int num_states = (int)robot.transitions.size();
    int config_size = N * N * 4 * num_states;
    vector<uint32_t> visited_buf(config_size);
    vector<pair<int, int>> path_buf;
    path_buf.reserve(config_size + 1);

    auto best_wall_v = empty_wall_v();
    auto best_wall_h = empty_wall_h();
    int best_cost = INT_MAX;

    for (int pi = 0; pi < (int)configs.size(); pi++) {
        auto &cfg = configs[pi];
        vector<vector<bool>> av, ah;
        if (cfg.is_horizontal)
            tie(av, ah) = build_corridors_with_boundaries(inp, cfg.boundaries);
        else
            tie(av, ah) = build_corridors_vertical(inp, cfg.boundaries);

        Grid grid = Grid::from_merged(inp, av, ah);
        int cov = simulate_count_fast(robot, grid, visited_buf, path_buf);
        if (cov != N * N)
            continue;

        optimize_walls(inp, av, ah, robot, (uint64_t)(pi + 1) * 1000);
        int w = count_added_walls(av, ah);
        int cost = inp.a_m * 5 + inp.a_w * w;
        if (cost < best_cost) {
            best_cost = cost;
            best_wall_v = av;
            best_wall_h = ah;
        }

        if (timer.elapsed_ms() > deadline_ms)
            break;
    }

    fprintf(stderr, "Corridor: W=%d, Time=%lldms\n",
            count_added_walls(best_wall_v, best_wall_h), timer.elapsed_ms());

    return Output{{robot}, best_wall_v, best_wall_h};
}

// ---------------------------------------------------------------------------
// compute_score
// ---------------------------------------------------------------------------
pair<int, double> compute_score(const Input &inp, const Output &out) {
    int k = (int)out.robots.size();
    int m = 0;
    for (auto &r : out.robots)
        m += (int)r.transitions.size();
    int w = count_added_walls(out.added_wall_v, out.added_wall_h);

    int v = inp.a_k * max(k - 1, 0) + inp.a_m * m + inp.a_w * w;
    int baseline = inp.a_k * (N * N - 1) + inp.a_m * N * N;
    if (v == 0 || baseline == 0)
        return {1, 1.0};
    double ratio = (double)baseline / v;
    double log_val = max(0.0, log2(ratio));
    int score = 1 + (int)round(1e6 * log_val);
    return {score, (double)v};
}

// ---------------------------------------------------------------------------
// solve_b
// ---------------------------------------------------------------------------
Output solve_b(const Input &inp) {
    Timer timer;

    Output *zigzag_result = solve_b_zigzag(inp, 1500);

    long long remaining_ms = max(0LL, 2200LL - timer.elapsed_ms());
    Output corridor_result = solve_b_corridor(inp, min(remaining_ms, 700LL));

    if (zigzag_result) {
        auto [score_z, cost_z] = compute_score(inp, *zigzag_result);
        auto [score_c, cost_c] = compute_score(inp, corridor_result);
        if (cost_z <= cost_c) {
            fprintf(stderr, "Selected: zigzag (cost=%.0f)\n", cost_z);
            Output ret = move(*zigzag_result);
            delete zigzag_result;
            return ret;
        } else {
            fprintf(stderr, "Selected: corridor (cost=%.0f)\n", cost_c);
            delete zigzag_result;
            return corridor_result;
        }
    } else {
        fprintf(stderr, "Selected: corridor (zigzag failed)\n");
        return corridor_result;
    }
}

// ---------------------------------------------------------------------------
// solve_c: ハミルトン閉路 + オートマトン
// ---------------------------------------------------------------------------
vector<pair<int, int>> get_neighbors_input(int r, int c, const Input &inp) {
    vector<pair<int, int>> neighbors;
    if (r > 0 && !inp.wall_h[r - 1][c])
        neighbors.push_back({r - 1, c});
    if (r < N - 1 && !inp.wall_h[r][c])
        neighbors.push_back({r + 1, c});
    if (c > 0 && !inp.wall_v[r][c - 1])
        neighbors.push_back({r, c - 1});
    if (c < N - 1 && !inp.wall_v[r][c])
        neighbors.push_back({r, c + 1});
    return neighbors;
}

bool is_valid_next(int nr, int nc, vector<vector<bool>> &visited,
                   const Input &inp, int remaining, bool seen_buf[N][N],
                   vector<pair<int, int>> &stack_buf) {
    if (remaining == 0)
        return true;

    auto neighbors = get_neighbors_input(nr, nc, inp);
    pair<int, int> start_cell = {-1, -1};
    for (auto [r, c] : neighbors) {
        if (!visited[r][c]) {
            start_cell = {r, c};
            break;
        }
    }
    if (start_cell.first < 0)
        return false;

    stack_buf.clear();
    stack_buf.push_back(start_cell);
    seen_buf[start_cell.first][start_cell.second] = true;
    int reached = 1;
    vector<pair<int, int>> touched;
    touched.push_back(start_cell);

    while (!stack_buf.empty()) {
        auto [cr, cc] = stack_buf.back();
        stack_buf.pop_back();
        if (cr > 0 && !inp.wall_h[cr - 1][cc] && !visited[cr - 1][cc] &&
            !seen_buf[cr - 1][cc]) {
            seen_buf[cr - 1][cc] = true;
            reached++;
            stack_buf.push_back({cr - 1, cc});
            touched.push_back({cr - 1, cc});
        }
        if (cr < N - 1 && !inp.wall_h[cr][cc] && !visited[cr + 1][cc] &&
            !seen_buf[cr + 1][cc]) {
            seen_buf[cr + 1][cc] = true;
            reached++;
            stack_buf.push_back({cr + 1, cc});
            touched.push_back({cr + 1, cc});
        }
        if (cc > 0 && !inp.wall_v[cr][cc - 1] && !visited[cr][cc - 1] &&
            !seen_buf[cr][cc - 1]) {
            seen_buf[cr][cc - 1] = true;
            reached++;
            stack_buf.push_back({cr, cc - 1});
            touched.push_back({cr, cc - 1});
        }
        if (cc < N - 1 && !inp.wall_v[cr][cc] && !visited[cr][cc + 1] &&
            !seen_buf[cr][cc + 1]) {
            seen_buf[cr][cc + 1] = true;
            reached++;
            stack_buf.push_back({cr, cc + 1});
            touched.push_back({cr, cc + 1});
        }
        if (reached == remaining)
            break;
    }

    for (auto [r, c] : touched)
        seen_buf[r][c] = false;
    return reached == remaining;
}

pair<int, int> select_warnsdorff(const vector<pair<int, int>> &candidates,
                                 const Input &inp,
                                 const vector<vector<bool>> &visited,
                                 Rng &rng) {
    auto degree = [&](int r, int c) {
        auto nb = get_neighbors_input(r, c, inp);
        int cnt = 0;
        for (auto [nr, nc] : nb)
            if (!visited[nr][nc])
                cnt++;
        return cnt;
    };

    vector<pair<int, int>> sorted = candidates;
    sort(sorted.begin(), sorted.end(), [&](auto &a, auto &b) {
        return degree(a.first, a.second) < degree(b.first, b.second);
    });

    int min_deg = degree(sorted[0].first, sorted[0].second);
    vector<pair<int, int>> ties;
    for (auto &[r, c] : sorted) {
        if (degree(r, c) == min_deg)
            ties.push_back({r, c});
        else
            break;
    }

    return ties[rng.next() % ties.size()];
}

vector<pair<int, int>> *warnsdorff_path(const Input &inp, pair<int, int> start,
                                        Rng &rng) {
    int total = N * N;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    vector<pair<int, int>> path;
    path.reserve(total);
    visited[start.first][start.second] = true;
    path.push_back(start);

    int backtracks = 0;
    int max_backtracks = 300;
    bool seen_buf[N][N] = {};
    vector<pair<int, int>> stack_buf;
    stack_buf.reserve(total);

    while ((int)path.size() < total) {
        auto [r, c] = path.back();
        auto nb = get_neighbors_input(r, c, inp);
        vector<pair<int, int>> candidates;
        for (auto [nr, nc] : nb)
            if (!visited[nr][nc])
                candidates.push_back({nr, nc});

        if (candidates.empty()) {
            backtracks++;
            if (backtracks > max_backtracks)
                return nullptr;
            int steps = 1 + (int)(rng.next() % 40);
            steps = min(steps, (int)path.size() - 1);
            for (int i = 0; i < steps; i++) {
                auto [br, bc] = path.back();
                path.pop_back();
                visited[br][bc] = false;
            }
            continue;
        }

        int remaining = total - (int)path.size() - 1;
        vector<pair<int, int>> safe_candidates;
        for (auto [nr, nc] : candidates) {
            visited[nr][nc] = true;
            bool valid = is_valid_next(nr, nc, visited, inp, remaining,
                                       seen_buf, stack_buf);
            visited[nr][nc] = false;
            if (valid)
                safe_candidates.push_back({nr, nc});
        }

        if (safe_candidates.empty()) {
            backtracks++;
            if (backtracks > max_backtracks)
                return nullptr;
            int steps = 1 + (int)(rng.next() % 40);
            steps = min(steps, (int)path.size() - 1);
            for (int i = 0; i < steps; i++) {
                auto [br, bc] = path.back();
                path.pop_back();
                visited[br][bc] = false;
            }
            continue;
        }

        auto next = select_warnsdorff(safe_candidates, inp, visited, rng);
        visited[next.first][next.second] = true;
        path.push_back(next);
    }

    return new vector<pair<int, int>>(move(path));
}

vector<pair<int, int>> *try_form_cycle(const vector<pair<int, int>> &path,
                                       const Input &inp) {
    int n = (int)path.size();
    auto start = path[0];
    auto end_ = path[n - 1];

    auto end_nb = get_neighbors_input(end_.first, end_.second, inp);
    for (auto [r, c] : end_nb)
        if (r == start.first && c == start.second)
            return new vector<pair<int, int>>(path);

    int pos[N][N] = {};
    for (int i = 0; i < n; i++)
        pos[path[i].first][path[i].second] = i;

    auto start_nb = get_neighbors_input(start.first, start.second, inp);

    for (auto [nr, nc] : end_nb) {
        int i = pos[nr][nc];
        if (i == 0 || i >= n - 2)
            continue;
        auto next_cell = path[i + 1];
        bool adj_start = false;
        for (auto [sr, sc] : start_nb)
            if (sr == next_cell.first && sc == next_cell.second) {
                adj_start = true;
                break;
            }
        if (adj_start) {
            auto *cycle = new vector<pair<int, int>>();
            cycle->reserve(n);
            for (int j = 0; j <= i; j++)
                cycle->push_back(path[j]);
            for (int j = n - 1; j > i; j--)
                cycle->push_back(path[j]);
            return cycle;
        }
    }
    return nullptr;
}

void backbite(vector<pair<int, int>> &path, int pos[N][N], const Input &inp,
              Rng &rng) {
    int n = (int)path.size();
    bool modify_start = rng.next() % 2 == 0;

    if (modify_start) {
        auto start = path[0];
        auto neighbors = get_neighbors_input(start.first, start.second, inp);
        vector<int> candidates;
        for (auto [r, c] : neighbors) {
            int k = pos[r][c];
            if (k > 1)
                candidates.push_back(k);
        }
        if (candidates.empty())
            return;
        int k = candidates[rng.next() % candidates.size()];
        reverse(path.begin(), path.begin() + k);
        for (int i = 0; i < k; i++)
            pos[path[i].first][path[i].second] = i;
    } else {
        auto end_ = path[n - 1];
        auto neighbors = get_neighbors_input(end_.first, end_.second, inp);
        vector<int> candidates;
        for (auto [r, c] : neighbors) {
            int k = pos[r][c];
            if (k < n - 2)
                candidates.push_back(k);
        }
        if (candidates.empty())
            return;
        int k = candidates[rng.next() % candidates.size()];
        reverse(path.begin() + k + 1, path.end());
        for (int i = k + 1; i < n; i++)
            pos[path[i].first][path[i].second] = i;
    }
}

vector<pair<int, int>> *find_hamiltonian_cycle(const Input &inp,
                                               long long time_limit_ms = 1800) {
    Rng rng(12345);
    Timer timer;
    int attempts = 0, paths_found = 0;

    for (int trial = 0; trial < 1000000; trial++) {
        if (timer.elapsed_ms() >= time_limit_ms)
            break;
        attempts++;

        int start_r = rng.next() % N, start_c = rng.next() % N;
        auto *path = warnsdorff_path(inp, {start_r, start_c}, rng);
        if (!path)
            continue;
        paths_found++;

        auto *cycle = try_form_cycle(*path, inp);
        if (cycle) {
            fprintf(
                stderr,
                "Hamiltonian cycle found in %lldms (%d attempts, %d paths)\n",
                timer.elapsed_ms(), attempts, paths_found);
            delete path;
            return cycle;
        }

        int pos[N][N] = {};
        int n = (int)path->size();
        for (int i = 0; i < n; i++)
            pos[(*path)[i].first][(*path)[i].second] = i;

        for (int bb = 0; bb < 100000; bb++) {
            if (timer.elapsed_ms() >= time_limit_ms)
                break;
            backbite(*path, pos, inp, rng);
            cycle = try_form_cycle(*path, inp);
            if (cycle) {
                fprintf(stderr,
                        "Hamiltonian cycle found (backbite) in %lldms (%d "
                        "attempts, %d paths)\n",
                        timer.elapsed_ms(), attempts, paths_found);
                delete path;
                return cycle;
            }
        }
        delete path;
    }

    fprintf(stderr, "No Hamiltonian cycle: %d attempts, %d paths in %lldms\n",
            attempts, paths_found, timer.elapsed_ms());
    return nullptr;
}

Dir cell_to_dir(pair<int, int> from, pair<int, int> to) {
    int dr = to.first - from.first;
    int dc = to.second - from.second;
    if (dr == -1)
        return DIR_U;
    if (dr == 1)
        return DIR_D;
    if (dc == -1)
        return DIR_L;
    return DIR_R;
}

vector<Action> turns_needed(Dir from, Dir to) {
    if (from == to)
        return {};
    if (turn_right(from) == to)
        return {ACT_R};
    if (turn_left(from) == to)
        return {ACT_L};
    return {ACT_R, ACT_R};
}

Robot cycle_to_robot(const vector<pair<int, int>> &cycle, const Grid &grid) {
    int n = (int)cycle.size();

    vector<Dir> directions(n);
    for (int i = 0; i < n; i++)
        directions[i] = cell_to_dir(cycle[i], cycle[(i + 1) % n]);

    vector<Action> actions;
    vector<bool> wall_observations;

    for (int i = 0; i < n; i++) {
        auto [r, c] = cycle[i];
        Dir arrive_dir = directions[(i + n - 1) % n];
        Dir depart_dir = directions[i];

        auto turns = turns_needed(arrive_dir, depart_dir);
        Dir current_dir = arrive_dir;
        for (Action turn_action : turns) {
            wall_observations.push_back(grid.has_wall(r, c, current_dir));
            actions.push_back(turn_action);
            if (turn_action == ACT_R)
                current_dir = turn_right(current_dir);
            else if (turn_action == ACT_L)
                current_dir = turn_left(current_dir);
        }

        wall_observations.push_back(false);
        actions.push_back(ACT_F);
    }

    int total_steps = (int)actions.size();
    vector<Transition> transitions(total_steps);
    for (int i = 0; i < total_steps; i++) {
        int next_state = (i + 1) % total_steps;
        if (wall_observations[i]) {
            transitions[i] = {ACT_R, next_state, actions[i], next_state};
        } else {
            transitions[i] = {actions[i], next_state, ACT_R, next_state};
        }
    }

    Dir initial_dir = directions[n - 1];
    return Robot{transitions, cycle[0].first, cycle[0].second, initial_dir};
}

vector<pair<int, int>> build_euler_walk(const Input &inp) {
    vector<vector<vector<pair<int, int>>>> children(
        N, vector<vector<pair<int, int>>>(N));
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    vector<pair<int, int>> queue;
    int qi = 0;
    visited[0][0] = true;
    queue.push_back({0, 0});

    while (qi < (int)queue.size()) {
        auto [r, c] = queue[qi++];
        for (auto [nr, nc] : get_neighbors_input(r, c, inp)) {
            if (!visited[nr][nc]) {
                visited[nr][nc] = true;
                children[r][c].push_back({nr, nc});
                queue.push_back({nr, nc});
            }
        }
    }

    vector<pair<int, int>> walk;
    walk.reserve(2 * N * N);
    struct Frame {
        int r, c, ci;
    };
    vector<Frame> stack = {{0, 0, 0}};
    walk.push_back({0, 0});

    while (!stack.empty()) {
        auto &top = stack.back();
        if (top.ci < (int)children[top.r][top.c].size()) {
            auto [cr, cc] = children[top.r][top.c][top.ci];
            top.ci++;
            walk.push_back({cr, cc});
            stack.push_back({cr, cc, 0});
        } else {
            stack.pop_back();
            if (!stack.empty()) {
                walk.push_back({stack.back().r, stack.back().c});
            }
        }
    }

    walk.pop_back();
    return walk;
}

// ---------------------------------------------------------------------------
// solve_c_beam: C5のビームサーチアプローチ
// ---------------------------------------------------------------------------
// C5内部の方向: 0=U, 1=R, 2=D, 3=L
// dx/dy for beam search directions
static const int beam_dx[4] = {-1, 0, 1, 0};
static const int beam_dy[4] = {0, 1, 0, -1};

bool beam_can_go(int x, int y, int d, const Input &inp) {
    int nx = x + beam_dx[d], ny = y + beam_dy[d];
    if (nx < 0 || nx >= N || ny < 0 || ny >= N)
        return false;
    if (d == 0)
        return !inp.wall_h[nx][ny]; // U
    if (d == 2)
        return !inp.wall_h[x][y]; // D
    if (d == 1)
        return !inp.wall_v[x][y]; // R
    if (d == 3)
        return !inp.wall_v[x][ny]; // L
    return false;
}

enum BeamOp { BEAM_RUN_R, BEAM_RUN_L, BEAM_TURN_R, BEAM_TURN_L, BEAM_STEP_F };

int beam_apply_op(int x, int y, int dir, BeamOp op, int &nx, int &ny, int &nd,
                  bitset<400> &visited, const Input &inp) {
    int added = 0;
    if (op == BEAM_RUN_R || op == BEAM_RUN_L) {
        int cx = x, cy = y;
        while (beam_can_go(cx, cy, dir, inp)) {
            cx += beam_dx[dir];
            cy += beam_dy[dir];
            int idx = cx * N + cy;
            if (!visited[idx]) {
                visited.set(idx);
                added++;
            }
        }
        nd = (op == BEAM_RUN_R) ? (dir + 1) % 4 : (dir + 3) % 4;
        nx = cx;
        ny = cy;
    } else if (op == BEAM_TURN_R) {
        nd = (dir + 1) % 4;
        nx = x;
        ny = y;
    } else if (op == BEAM_TURN_L) {
        nd = (dir + 3) % 4;
        nx = x;
        ny = y;
    } else { // STEP_F
        nx = x + beam_dx[dir];
        ny = y + beam_dy[dir];
        nd = dir;
        int idx = nx * N + ny;
        if (!visited[idx]) {
            visited.set(idx);
            added++;
        }
    }
    return added;
}

// ビームサーチの結果をRobotに変換
// beam_dir: 0=U,1=R,2=D,3=L -> Dir: DIR_U,DIR_D,DIR_L,DIR_R
Dir beam_dir_to_dir(int bd) {
    static const Dir tbl[] = {DIR_U, DIR_R, DIR_D, DIR_L};
    return tbl[bd];
}

Output *solve_c_beam(const Input &inp, long long time_limit_ms) {
    Timer timer;
    int N2 = N * N;
    const int BEAM_W = 75;
    mt19937 rng_mt(42);

    int best_total = INT_MAX;
    vector<BeamOp> best_ops;
    int best_sx = 0, best_sy = 0, best_sd = 0;

    for (int trial = 0;; trial++) {
        if (timer.elapsed_ms() > time_limit_ms)
            break;

        int sx = rng_mt() % N, sy = rng_mt() % N, sd = rng_mt() % 4;

        struct Node {
            int x, y, dir;
            bitset<400> visited;
            int num_visited;
            int parent;
            BeamOp op;
        };
        vector<Node> all_nodes;
        {
            Node root;
            root.x = sx;
            root.y = sy;
            root.dir = sd;
            root.visited.reset();
            root.visited.set(sx * N + sy);
            root.num_visited = 1;
            root.parent = -1;
            root.op = BEAM_RUN_R; // dummy
            all_nodes.push_back(root);
        }

        vector<int> beam = {0};
        int found_idx = -1;

        for (int step = 0; step < 1500 && found_idx < 0; step++) {
            vector<Node> beam_nodes;
            beam_nodes.reserve(beam.size());
            for (int bi : beam)
                beam_nodes.push_back(all_nodes[bi]);

            vector<pair<int, int>> candidates;

            for (int b = 0; b < (int)beam.size(); b++) {
                auto &node = beam_nodes[b];
                int bi = beam[b];
                bool at_wall = !beam_can_go(node.x, node.y, node.dir, inp);

                vector<BeamOp> ops;
                if (at_wall) {
                    ops = {BEAM_TURN_R, BEAM_TURN_L};
                } else {
                    ops = {BEAM_RUN_R, BEAM_RUN_L, BEAM_TURN_R, BEAM_TURN_L,
                           BEAM_STEP_F};
                }

                for (BeamOp op : ops) {
                    Node child;
                    child.visited = node.visited;
                    child.num_visited = node.num_visited;
                    int nx, ny, nd;
                    int added = beam_apply_op(node.x, node.y, node.dir, op, nx,
                                              ny, nd, child.visited, inp);
                    child.x = nx;
                    child.y = ny;
                    child.dir = nd;
                    child.num_visited += added;
                    child.parent = bi;
                    child.op = op;
                    int idx = all_nodes.size();
                    all_nodes.push_back(child);
                    candidates.push_back({idx, child.num_visited});
                }
            }

            sort(candidates.begin(), candidates.end(),
                 [](auto &a, auto &b) { return a.second > b.second; });
            if ((int)candidates.size() > BEAM_W)
                candidates.resize(BEAM_W);

            beam.clear();
            for (auto &[idx, nv] : candidates) {
                beam.push_back(idx);
                if (nv == N2) {
                    found_idx = idx;
                    break;
                }
            }
        }

        if (found_idx < 0)
            continue;

        // 経路復元
        vector<BeamOp> ops;
        int ci = found_idx;
        while (all_nodes[ci].parent >= 0) {
            ops.push_back(all_nodes[ci].op);
            ci = all_nodes[ci].parent;
        }
        reverse(ops.begin(), ops.end());

        // 帰還パス: (x,y,dir)状態空間BFSで操作数最小化
        auto &fnode = all_nodes[found_idx];
        int cur_x = fnode.x, cur_y = fnode.y, cur_dir = fnode.dir;

        int S = N * N * 4;
        auto encode = [&](int x, int y, int d) { return (x * N + y) * 4 + d; };
        vector<int> dist_r(S, -1);
        vector<int> prev_r(S, -1);
        vector<BeamOp> prev_op(S);
        int start_s = encode(cur_x, cur_y, cur_dir);
        int goal_s = encode(sx, sy, sd);
        dist_r[start_s] = 0;
        queue<int> bq;
        bq.push(start_s);
        while (!bq.empty() && dist_r[goal_s] < 0) {
            int s = bq.front();
            bq.pop();
            int bx = s / 4 / N, by = s / 4 % N, bd = s % 4;
            BeamOp try_ops[] = {BEAM_RUN_R, BEAM_RUN_L, BEAM_TURN_R,
                                BEAM_TURN_L, BEAM_STEP_F};
            for (BeamOp op : try_ops) {
                int nx, ny, nd;
                if (op == BEAM_STEP_F && !beam_can_go(bx, by, bd, inp))
                    continue;
                if ((op == BEAM_RUN_R || op == BEAM_RUN_L) &&
                    !beam_can_go(bx, by, bd, inp))
                    continue;
                if (op == BEAM_RUN_R || op == BEAM_RUN_L) {
                    int cx2 = bx, cy2 = by;
                    while (beam_can_go(cx2, cy2, bd, inp)) {
                        cx2 += beam_dx[bd];
                        cy2 += beam_dy[bd];
                    }
                    nd = (op == BEAM_RUN_R) ? (bd + 1) % 4 : (bd + 3) % 4;
                    nx = cx2;
                    ny = cy2;
                } else if (op == BEAM_TURN_R) {
                    nx = bx;
                    ny = by;
                    nd = (bd + 1) % 4;
                } else if (op == BEAM_TURN_L) {
                    nx = bx;
                    ny = by;
                    nd = (bd + 3) % 4;
                } else {
                    nx = bx + beam_dx[bd];
                    ny = by + beam_dy[bd];
                    nd = bd;
                }
                int ns = encode(nx, ny, nd);
                if (dist_r[ns] >= 0)
                    continue;
                dist_r[ns] = dist_r[s] + 1;
                prev_r[ns] = s;
                prev_op[ns] = op;
                bq.push(ns);
            }
        }
        vector<BeamOp> return_ops;
        if (dist_r[goal_s] >= 0) {
            int cs = goal_s;
            while (cs != start_s) {
                return_ops.push_back(prev_op[cs]);
                cs = prev_r[cs];
            }
            reverse(return_ops.begin(), return_ops.end());
        }

        int total = (int)ops.size() + (int)return_ops.size();
        if (total < best_total) {
            best_total = total;
            best_ops = ops;
            best_ops.insert(best_ops.end(), return_ops.begin(),
                            return_ops.end());
            best_sx = sx;
            best_sy = sy;
            best_sd = sd;
            fprintf(stderr, "Beam trial=%d states=%d\n", trial, total);
        }
    }

    fprintf(stderr, "Beam best_total=%d, time=%lldms\n", best_total,
            timer.elapsed_ms());

    if (best_total == INT_MAX)
        return nullptr;

    // BeamOp列からRobotを構築
    int M = best_total;
    vector<Transition> transitions(M);
    for (int i = 0; i < M; i++) {
        int nxt = (i + 1) % M;
        BeamOp op = best_ops[i];
        if (op == BEAM_RUN_R) {
            transitions[i] = {ACT_F, i, ACT_R, nxt};
        } else if (op == BEAM_RUN_L) {
            transitions[i] = {ACT_F, i, ACT_L, nxt};
        } else if (op == BEAM_TURN_R) {
            transitions[i] = {ACT_R, nxt, ACT_R, nxt};
        } else if (op == BEAM_TURN_L) {
            transitions[i] = {ACT_L, nxt, ACT_L, nxt};
        } else { // STEP_F
            transitions[i] = {ACT_F, nxt, ACT_R, nxt};
        }
    }

    Robot robot;
    robot.transitions = move(transitions);
    robot.row = best_sx;
    robot.col = best_sy;
    robot.dir = beam_dir_to_dir(best_sd);

    auto *out = new Output();
    out->robots.push_back(move(robot));
    out->added_wall_v = empty_wall_v();
    out->added_wall_h = empty_wall_h();
    return out;
}

// ---------------------------------------------------------------------------
// solve_c: ハミルトン閉路とビームサーチの両方を試し、最良を返す
// ---------------------------------------------------------------------------
Output solve_c(const Input &inp) {
    Grid grid = Grid::from_input(inp);

    // Phase 1: ハミルトン閉路探索（300ms）
    int ham_states = INT_MAX;
    Robot ham_robot;
    {
        auto *cycle = find_hamiltonian_cycle(inp, 300);
        if (cycle) {
            ham_robot = cycle_to_robot(*cycle, grid);
            ham_states = (int)ham_robot.transitions.size();
            fprintf(stderr, "Problem C: Hamiltonian states=%d\n", ham_states);
            delete cycle;
        } else {
            auto walk = build_euler_walk(inp);
            ham_robot = cycle_to_robot(walk, grid);
            ham_states = (int)ham_robot.transitions.size();
            fprintf(stderr, "Problem C: Euler walk states=%d\n", ham_states);
        }
    }

    // Phase 2: ビームサーチ（1500ms）
    Output *beam_out = solve_c_beam(inp, 1500);
    int beam_states =
        beam_out ? (int)beam_out->robots[0].transitions.size() : INT_MAX;
    if (beam_out) {
        fprintf(stderr, "Problem C: Beam states=%d\n", beam_states);
    }

    // 状態数が少ない方を採用
    if (beam_out && beam_states < ham_states) {
        fprintf(stderr, "Problem C: Selected beam (states=%d vs %d)\n",
                beam_states, ham_states);
        Output ret = move(*beam_out);
        delete beam_out;
        return ret;
    } else {
        fprintf(stderr, "Problem C: Selected hamiltonian (states=%d vs %d)\n",
                ham_states, beam_states);
        if (beam_out)
            delete beam_out;
        return Output{{ham_robot}, empty_wall_v(), empty_wall_h()};
    }
}

// ---------------------------------------------------------------------------
// Coverage bitset helpers
// ---------------------------------------------------------------------------
static const int COVERAGE_WORDS = (N * N + 63) / 64;

using CovBits = array<uint64_t, 7>; // COVERAGE_WORDS = 7

CovBits coverage_bitset(const vector<pair<int, int>> &cells) {
    CovBits bits = {};
    for (auto [r, c] : cells) {
        int idx = r * N + c;
        bits[idx / 64] |= 1ULL << (idx % 64);
    }
    return bits;
}

CovBits bitset_or(const CovBits &a, const CovBits &b) {
    CovBits result = a;
    for (int i = 0; i < COVERAGE_WORDS; i++)
        result[i] |= b[i];
    return result;
}

int bitset_popcount(const CovBits &bits) {
    int cnt = 0;
    for (int i = 0; i < COVERAGE_WORDS; i++)
        cnt += __builtin_popcountll(bits[i]);
    return cnt;
}

// ---------------------------------------------------------------------------
// solve_a
// ---------------------------------------------------------------------------
struct CoverCandidate {
    Robot robot;
    CovBits bits;
    int cell_count;
};

struct BnBContext {
    const vector<CoverCandidate> *candidates;
    vector<int> suffix_benefit;
    int best_cost;
    vector<bool> best_sel;
    vector<bool> cur_sel;
    Timer timer;
    uint64_t calls;
    bool timed_out;

    void search(int idx, CovBits covered, int covered_count, int total_states) {
        if (timed_out)
            return;

        int current_cost = total_states + (N * N - covered_count);
        if (current_cost < best_cost) {
            best_cost = current_cost;
            best_sel = cur_sel;
        }

        if (idx >= (int)candidates->size())
            return;

        calls++;
        if (calls % 100000 == 0 && timer.elapsed_ms() > 1800) {
            timed_out = true;
            return;
        }

        if (total_states >= best_cost)
            return;
        if (current_cost >= best_cost + suffix_benefit[idx])
            return;
        // Corrected: current_cost - suffix_benefit[idx] >= best_cost
        // i.e., even with maximum possible benefit, we can't beat best_cost
        int lower_bound = current_cost;
        if (suffix_benefit[idx] < current_cost)
            lower_bound = current_cost - suffix_benefit[idx];
        else
            lower_bound = 0;
        // Actually the original Rust:
        // current_cost.saturating_sub(suffix_benefit[idx]) >= best_cost
        {
            int lb = max(0, current_cost - suffix_benefit[idx]);
            if (lb >= best_cost)
                return;
        }

        auto &c = (*candidates)[idx];

        CovBits new_bits = bitset_or(covered, c.bits);
        int new_count = bitset_popcount(new_bits);
        if (new_count > covered_count) {
            cur_sel[idx] = true;
            search(idx + 1, new_bits, new_count,
                   total_states + (int)c.robot.transitions.size());
            cur_sel[idx] = false;
        }

        search(idx + 1, covered, covered_count, total_states);
    }
};

Output solve_a(const Input &inp) {
    Timer timer;
    Grid grid = Grid::from_input(inp);
    Dir dirs[] = {DIR_U, DIR_D, DIR_L, DIR_R};

    using FactoryFn = Robot (*)(int, int, Dir);
    FactoryFn factories[] = {
        make_boundary_tracer, make_boundary_tracer_left, make_uturn,
        make_wall_follower,   make_left_wall_follower,   make_zigzag,
    };

    vector<CoverCandidate> candidates;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            for (Dir d : dirs)
                for (auto factory : factories) {
                    Robot robot = factory(r, c, d);
                    auto cells = simulate_cells(robot, grid);
                    int states = (int)robot.transitions.size();
                    if ((int)cells.size() > states) {
                        auto bits = coverage_bitset(cells);
                        candidates.push_back({robot, bits, (int)cells.size()});
                    }
                }

    // ビットセットで重複除去
    sort(candidates.begin(), candidates.end(),
         [](auto &a, auto &b) { return a.bits < b.bits; });
    {
        int w_idx = 0;
        for (int i = 0; i < (int)candidates.size(); i++) {
            if (w_idx > 0 && candidates[i].bits == candidates[w_idx - 1].bits) {
                if ((int)candidates[i].robot.transitions.size() <
                    (int)candidates[w_idx - 1].robot.transitions.size()) {
                    candidates[w_idx - 1] = move(candidates[i]);
                }
            } else {
                if (w_idx != i)
                    candidates[w_idx] = move(candidates[i]);
                w_idx++;
            }
        }
        candidates.resize(w_idx);
    }

    // 利得降順
    sort(candidates.begin(), candidates.end(), [](auto &a, auto &b) {
        int ba = a.cell_count - (int)a.robot.transitions.size();
        int bb = b.cell_count - (int)b.robot.transitions.size();
        return bb < ba;
    });

    int n_cands = (int)candidates.size();
    fprintf(stderr, "Problem A: %d unique candidates\n", n_cands);

    vector<int> suffix_benefit(n_cands + 1, 0);
    for (int i = n_cands - 1; i >= 0; i--) {
        int benefit = candidates[i].cell_count -
                      (int)candidates[i].robot.transitions.size();
        suffix_benefit[i] = suffix_benefit[i + 1] + benefit;
    }

    // 貪欲法
    vector<bool> greedy_sel(n_cands, false);
    int greedy_cost;
    {
        CovBits covered = {};
        int covered_count = 0, states = 0;
        vector<bool> used(n_cands, false);

        for (;;) {
            int best_idx = -1, best_new = 0, best_st = INT_MAX;
            for (int i = 0; i < n_cands; i++) {
                if (used[i])
                    continue;
                CovBits u = bitset_or(covered, candidates[i].bits);
                int new_cells = bitset_popcount(u) - covered_count;
                if (new_cells == 0)
                    continue;
                int s = (int)candidates[i].robot.transitions.size();
                if ((long long)new_cells * best_st > (long long)best_new * s ||
                    ((long long)new_cells * best_st ==
                         (long long)best_new * s &&
                     s < best_st)) {
                    best_idx = i;
                    best_new = new_cells;
                    best_st = s;
                }
            }
            if (best_idx < 0 || best_new <= best_st)
                break;
            used[best_idx] = true;
            greedy_sel[best_idx] = true;
            covered = bitset_or(covered, candidates[best_idx].bits);
            covered_count += best_new;
            states += best_st;
        }
        greedy_cost = states + (N * N - covered_count);
    }

    fprintf(stderr, "Problem A: greedy cost = %d\n", greedy_cost);

    BnBContext ctx;
    ctx.candidates = &candidates;
    ctx.suffix_benefit = suffix_benefit;
    ctx.best_cost = greedy_cost;
    ctx.best_sel = greedy_sel;
    ctx.cur_sel.assign(n_cands, false);
    ctx.calls = 0;
    ctx.timed_out = false;

    CovBits zero_bits = {};
    ctx.search(0, zero_bits, 0, 0);

    fprintf(stderr, "Problem A: B&B %llu calls, cost %d -> %d, time %lldms\n",
            (unsigned long long)ctx.calls, greedy_cost, ctx.best_cost,
            timer.elapsed_ms());

    vector<Robot> robots;
    CovBits all_covered = {};
    for (int i = 0; i < n_cands; i++) {
        if (ctx.best_sel[i]) {
            robots.push_back(candidates[i].robot);
            all_covered = bitset_or(all_covered, candidates[i].bits);
        }
    }

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++) {
            int idx = r * N + c;
            if (!(all_covered[idx / 64] & (1ULL << (idx % 64))))
                robots.push_back(make_spinner(r, c));
        }

    int total_states = 0;
    for (auto &r : robots)
        total_states += (int)r.transitions.size();
    fprintf(stderr, "Problem A: %d robots, M=%d (baseline=400)\n",
            (int)robots.size(), total_states);

    return Output{robots, empty_wall_v(), empty_wall_h()};
}

// ---------------------------------------------------------------------------
// solve_baseline
// ---------------------------------------------------------------------------
Output solve_baseline() {
    vector<Robot> robots;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            robots.push_back(make_spinner(i, j));
    return Output{robots, empty_wall_v(), empty_wall_h()};
}

// ---------------------------------------------------------------------------
// solve
// ---------------------------------------------------------------------------
Output solve(const Input &inp) {
    if (inp.a_k == 0) {
        return solve_a(inp);
    } else if (inp.a_k >= 100 && inp.a_w >= 100) {
        return solve_c(inp);
    } else if (inp.a_k > 0 && inp.a_w <= 10) {
        return solve_b(inp);
    } else {
        return solve_baseline();
    }
}

// ---------------------------------------------------------------------------
// print_output
// ---------------------------------------------------------------------------
void print_output(const Output &out) {
    printf("%d\n", (int)out.robots.size());
    for (auto &robot : out.robots) {
        printf("%d %d %d %c\n", (int)robot.transitions.size(), robot.row,
               robot.col, dir_to_char(robot.dir));
        for (auto &trans : robot.transitions) {
            printf("%c %d %c %d\n", action_to_char(trans.action_open),
                   trans.next_open, action_to_char(trans.action_wall),
                   trans.next_wall);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++)
            putchar(out.added_wall_v[i][j] ? '1' : '0');
        putchar('\n');
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++)
            putchar(out.added_wall_h[i][j] ? '1' : '0');
        putchar('\n');
    }
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main() {
    Input inp = parse_input();
    Output out = solve(inp);

    Grid grid = Grid::make(inp, out);
    int total_cells = N * N;
    bool cell_covered[N][N] = {};
    for (auto &robot : out.robots) {
        auto cells = simulate_cells(robot, grid);
        for (auto [r, c] : cells)
            cell_covered[r][c] = true;
    }
    int covered_count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            covered_count += cell_covered[i][j];
    fprintf(stderr, "Coverage: %d/%d\n", covered_count, total_cells);
    if (covered_count < total_cells)
        fprintf(stderr, "WARNING: not all cells are covered!\n");

    auto [score, cost] = compute_score(inp, out);
    fprintf(stderr, "Cost: %.0f, Score: %d\n", cost, score);

    print_output(out);
    return 0;
}
