#include <bits/stdc++.h>
using namespace std;

// AHC065 C.cc
// ベルト構成は A.cc と同一（縦10 + 横10、各長さ40）。
// 操作列はビームサーチで決定する。
// - 1 操作 = 1 ノード深さ進行
// - ビーム幅 BEAM_WIDTH
// - 各状態から「番号が小さい順 TOP_K_BOXES 個の箱 × {縦ループ,横ループ} ×
// {d=-1,+1}」を候補展開
// - 評価関数 h = Σ_{k=cur..cur+TOP_K_EVAL-1} MD(箱_k, 出口) / (k - cur + 1)

static const int N = 20;
static const int NN = N * N;
static const int EXIT_R = 0, EXIT_C = N / 2;
static const int LOOP_LEN = 2 * N;
static const int BEAM_WIDTH = 25;
static const int TOP_K_BOXES = 10;
static const int TOP_K_EVAL = 50;
static const int MAX_DEPTH = 100000;
static const double TIME_LIMIT_SEC = 600.0;

vector<vector<pair<int, int>>> belts;

// Zobrist ハッシュ: (cell, box_id) → 64-bit ランダム値
uint64_t zobrist[NN][NN];
void init_zobrist() {
    mt19937_64 rng(20260516ULL);
    for (int c = 0; c < NN; c++)
        for (int b = 0; b < NN; b++)
            zobrist[c][b] = rng();
}

// 評価関数用の乱数 (同点タイブレーク用に微小な ±1% を掛ける)
mt19937 eval_rng(20260516ULL);
inline double eval_jitter() {
    return 0.998 + (eval_rng() & 0xFFFF) * (0.004 / 65535.0);
}

int v_belt_id(int col) { return col / 2; }
int h_belt_id(int row) { return N / 2 + row / 2; }

void build_belts() {
    for (int k = 0; k < N / 2; k++) {
        vector<pair<int, int>> b;
        for (int i = 0; i < N; i++)
            b.push_back({i, 2 * k});
        for (int i = N - 1; i >= 0; i--)
            b.push_back({i, 2 * k + 1});
        belts.push_back(b);
    }
    for (int k = 0; k < N / 2; k++) {
        vector<pair<int, int>> b;
        for (int j = 0; j < N; j++)
            b.push_back({2 * k, j});
        for (int j = N - 1; j >= 0; j--)
            b.push_back({2 * k + 1, j});
        belts.push_back(b);
    }
}

struct Node {
    int parent;
    int8_t m;
    int8_t d;
};
vector<Node> tree;

struct State {
    array<int16_t, NN> grid; // 箱番号、空き or 取出済みは -1
    array<int16_t, NN> pos;  // pos[k] = r*N+c、取出済み箱は -1
    int current_target;
    int node_idx;
    double h;
    uint64_t hash;
};

// セル dst の中身を newv に書き換え、ハッシュ・pos も更新
static inline void write_cell(State &s, int dst, int16_t newv) {
    int16_t old = s.grid[dst];
    if (old == newv)
        return;
    if (old >= 0)
        s.hash ^= zobrist[dst][old];
    if (newv >= 0)
        s.hash ^= zobrist[dst][newv];
    s.grid[dst] = newv;
    if (newv >= 0)
        s.pos[newv] = dst;
}

void apply_op(State &s, int m, int d) {
    auto &cells = belts[m];
    int L = (int)cells.size();
    if (d == 1) {
        int16_t carry = s.grid[cells[L - 1].first * N + cells[L - 1].second];
        for (int x = L - 1; x >= 1; x--) {
            int dst = cells[x].first * N + cells[x].second;
            int src = cells[x - 1].first * N + cells[x - 1].second;
            write_cell(s, dst, s.grid[src]);
        }
        int dst0 = cells[0].first * N + cells[0].second;
        write_cell(s, dst0, carry);
    } else {
        int16_t carry = s.grid[cells[0].first * N + cells[0].second];
        for (int x = 0; x < L - 1; x++) {
            int dst = cells[x].first * N + cells[x].second;
            int src = cells[x + 1].first * N + cells[x + 1].second;
            write_cell(s, dst, s.grid[src]);
        }
        int dstL = cells[L - 1].first * N + cells[L - 1].second;
        write_cell(s, dstL, carry);
    }
    // 出口で取出
    int exit_idx = EXIT_R * N + EXIT_C;
    if (s.current_target < NN && s.grid[exit_idx] == s.current_target) {
        s.hash ^= zobrist[exit_idx][s.current_target];
        s.pos[s.current_target] = -1;
        s.grid[exit_idx] = -1;
        s.current_target++;
    }
}

double compute_h(const State &s) {
    double h = 0.0;
    int rank = 1;
    int end = min(s.current_target + TOP_K_EVAL, NN);
    for (int k = s.current_target; k < end; k++, rank++) {
        int p = s.pos[k];
        int r = p / N;
        int c = p % N;
        int md = abs(r - EXIT_R) + abs(c - EXIT_C);
        h += (double)md / rank;
    }
    return h * eval_jitter();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int grid_in[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> grid_in[i][j];

    build_belts();
    init_zobrist();

    // ベルト出力
    cout << belts.size() << "\n";
    for (auto &b : belts) {
        cout << b.size();
        for (auto &[i, j] : b)
            cout << " " << i << " " << j;
        cout << "\n";
    }

    // 初期状態
    tree.push_back({-1, -1, -1});
    State init;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            init.grid[i * N + j] = grid_in[i][j];
            init.pos[grid_in[i][j]] = i * N + j;
        }
    init.current_target = 0;
    if (init.grid[EXIT_R * N + EXIT_C] == 0) {
        init.pos[0] = -1;
        init.grid[EXIT_R * N + EXIT_C] = -1;
        init.current_target = 1;
    }
    init.node_idx = 0;
    init.hash = 0;
    for (int c = 0; c < NN; c++) {
        if (init.grid[c] >= 0)
            init.hash ^= zobrist[c][init.grid[c]];
    }
    init.h = compute_h(init);

    unordered_set<uint64_t> seen;
    seen.reserve(1 << 20);
    seen.insert(init.hash);

    vector<State> frontier;
    frontier.push_back(init);

    State best_done_state;
    int best_done_depth = INT_MAX;
    auto t_start = chrono::steady_clock::now();
    bool timed_out = false;

    for (int step = 1; step <= MAX_DEPTH; step++) {
        // 実行時間チェック（1.8 秒で打ち切り）
        double elapsed =
            chrono::duration<double>(chrono::steady_clock::now() - t_start)
                .count();
        if (elapsed > TIME_LIMIT_SEC) {
            cerr << "TIMEOUT step=" << step << " elapsed=" << elapsed << "\n";
            timed_out = true;
            break;
        }

        vector<State> candidates;
        candidates.reserve(frontier.size() * TOP_K_BOXES * 4);

        for (auto &s : frontier) {
            if (s.current_target >= NN)
                continue;

            int8_t tried[20][2] = {}; // tried[m][d_idx]
            int top_n = min(TOP_K_BOXES, NN - s.current_target);
            for (int bi = 0; bi < top_n; bi++) {
                int boxid = s.current_target + bi;
                int p = s.pos[boxid];
                int r = p / N, c = p % N;
                int vb = v_belt_id(c);
                int hb = h_belt_id(r);

                int belts_to_try[2] = {vb, hb};
                for (int bm = 0; bm < 2; bm++) {
                    int m = belts_to_try[bm];
                    for (int d : {-1, 1}) {
                        int d_idx = (d == 1) ? 1 : 0;
                        if (tried[m][d_idx])
                            continue;
                        tried[m][d_idx] = 1;

                        State ns = s;
                        apply_op(ns, m, d);
                        if (!seen.insert(ns.hash).second)
                            continue;
                        int new_idx = (int)tree.size();
                        tree.push_back({s.node_idx, (int8_t)m, (int8_t)d});
                        ns.node_idx = new_idx;
                        ns.h = compute_h(ns);
                        candidates.push_back(std::move(ns));
                    }
                }
            }
        }

        if (candidates.empty())
            break;

        // 完了検出
        for (auto &c : candidates) {
            if (c.current_target >= NN) {
                if (step < best_done_depth) {
                    best_done_depth = step;
                    best_done_state = c;
                }
            }
        }
        if (best_done_depth < INT_MAX)
            break;

        // ソート: 出荷数多い → h 小さい
        sort(candidates.begin(), candidates.end(),
             [](const State &a, const State &b) {
                 if (a.current_target != b.current_target)
                     return a.current_target > b.current_target;
                 return a.h < b.h;
             });
        if ((int)candidates.size() > BEAM_WIDTH)
            candidates.resize(BEAM_WIDTH);
        frontier = std::move(candidates);
    }

    // 復元対象を決定
    State *best_ptr;
    if (best_done_depth < INT_MAX) {
        best_ptr = &best_done_state;
    } else {
        State *b = &frontier[0];
        for (auto &s : frontier) {
            if (s.current_target > b->current_target ||
                (s.current_target == b->current_target && s.h < b->h))
                b = &s;
        }
        best_ptr = b;
    }

    // 操作復元
    vector<pair<int, int>> ops;
    int idx = best_ptr->node_idx;
    while (idx > 0) {
        ops.push_back({tree[idx].m, tree[idx].d});
        idx = tree[idx].parent;
    }
    reverse(ops.begin(), ops.end());

    cout << ops.size() << "\n";
    for (auto &[m, d] : ops)
        cout << m << " " << d << "\n";

    return timed_out ? 1 : 0;
}
