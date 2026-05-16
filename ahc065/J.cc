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
static const int TOP_K_BOXES = 20;
static const int TOP_K_EVAL = NN;
static const int MAX_DEPTH = 100000;
static const double TIME_LIMIT_SEC = 2.0;

vector<vector<pair<int, int>>> belts;

// Zobrist ハッシュ: (cell, box_id) → 64-bit ランダム値
uint64_t zobrist[NN][NN];

// MD テーブル: md_table[cell_idx] = |r - EXIT_R| + |c - EXIT_C|
int md_table[NN];
// 逆ランクテーブル: inv_rank[k] = 1.0 / k^RANK_POWER
static const double RANK_POWER = 0.75;
double inv_rank[NN + 1];
void init_tables() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            md_table[i * N + j] = abs(i - EXIT_R) + abs(j - EXIT_C);
    inv_rank[0] = 0.0;
    for (int k = 1; k <= NN; k++) inv_rank[k] = 1.0 / pow((double)k, RANK_POWER);
}

// open-addressing ハッシュ集合（線形探査）。0 は未使用。
struct HashSet {
    static constexpr size_t CAP = 1u << 23; // 8M スロット
    static constexpr size_t MASK = CAP - 1;
    uint64_t *data;
    size_t count = 0;
    HashSet() {
        data = (uint64_t *)calloc(CAP, sizeof(uint64_t));
    }
    ~HashSet() { free(data); }
    bool insert(uint64_t h) {
        if (h == 0) h = 0x9E3779B97F4A7C15ULL; // 0 は予約値なので別値に
        size_t idx = h & MASK;
        while (data[idx] != 0) {
            if (data[idx] == h) return false;
            idx = (idx + 1) & MASK;
        }
        data[idx] = h;
        count++;
        return true;
    }
};
void init_zobrist() {
    mt19937_64 rng(20260516ULL);
    for (int c = 0; c < NN; c++)
        for (int b = 0; b < NN; b++)
            zobrist[c][b] = rng();
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

double compute_h(const State &s) {
    double h = 0.0;
    int rank = 1;
    int end = min(s.current_target + TOP_K_EVAL, NN);
    for (int k = s.current_target; k < end; k++, rank++) {
        h += md_table[s.pos[k]] * inv_rank[rank];
    }
    return h;
}

void apply_op(State &s, int m, int d) {
    auto &cells = belts[m];
    int L = (int)cells.size();
    int cur = s.current_target;
    int end = min(cur + TOP_K_EVAL, NN);

    // 差分で h を更新: ベルト m 上のセルを走査し、評価窓 [cur, end) 内の箱だけ寄与
    double delta_h = 0.0;
    for (int p = 0; p < L; p++) {
        int c_idx = cells[p].first * N + cells[p].second;
        int b = s.grid[c_idx];
        if (b >= cur && b < end) {
            int new_p = (p + d + L) % L;
            int new_c_idx = cells[new_p].first * N + cells[new_p].second;
            delta_h +=
                (md_table[new_c_idx] - md_table[c_idx]) * inv_rank[b - cur + 1];
        }
    }
    s.h += delta_h;

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
    // 出口で取出。current_target が進むとランクが全シフトするので h を再計算
    int exit_idx = EXIT_R * N + EXIT_C;
    if (s.current_target < NN && s.grid[exit_idx] == s.current_target) {
        s.hash ^= zobrist[exit_idx][s.current_target];
        s.pos[s.current_target] = -1;
        s.grid[exit_idx] = -1;
        s.current_target++;
        s.h = compute_h(s);
    }
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
    init_tables();

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

    HashSet seen;
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
                        if (!seen.insert(ns.hash))
                            continue;
                        int new_idx = (int)tree.size();
                        tree.push_back({s.node_idx, (int8_t)m, (int8_t)d});
                        ns.node_idx = new_idx;
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

        // 上位 BEAM_WIDTH 個だけ取り出す（インデックスで nth_element して State 自体は動かさない）
        int K = min((int)candidates.size(), BEAM_WIDTH);
        if ((int)candidates.size() > BEAM_WIDTH) {
            vector<int> idx(candidates.size());
            iota(idx.begin(), idx.end(), 0);
            nth_element(idx.begin(), idx.begin() + K, idx.end(),
                        [&](int a, int b) {
                            const auto &sa = candidates[a];
                            const auto &sb = candidates[b];
                            if (sa.current_target != sb.current_target)
                                return sa.current_target > sb.current_target;
                            return sa.h < sb.h;
                        });
            vector<State> next_frontier;
            next_frontier.reserve(K);
            for (int i = 0; i < K; i++)
                next_frontier.push_back(std::move(candidates[idx[i]]));
            frontier = std::move(next_frontier);
        } else {
            frontier = std::move(candidates);
        }
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

    return 0;
}
