#include <bits/stdc++.h>
using namespace std;

// AHC065 A.cc
// 戦略: 20x2 の縦ループ 10 本と 2x20 の横ループ 10 本を設置。
// 各マスはちょうど 2 本のループに含まれる（制約「高々 2 本」を満たす）。
// 各箱について「横ループで col10/11 に寄せ」→「col10-11 の縦ループで (0,10) に移送」を繰り返す。

static const int N = 20;
static const int EXIT_R = 0, EXIT_C = N / 2;  // (0, 10)
static const int LOOP_LEN = 2 * N;            // 各ループ長 = 40

vector<vector<pair<int, int>>> belts;
int grid[N][N];
vector<pair<int, int>> ops;
int current_target;

void build_belts() {
    // 縦ループ 0..9: ループ k は列 2k, 2k+1 を覆う
    for (int k = 0; k < N / 2; k++) {
        vector<pair<int, int>> b;
        for (int i = 0; i < N; i++) b.push_back({i, 2 * k});
        for (int i = N - 1; i >= 0; i--) b.push_back({i, 2 * k + 1});
        belts.push_back(b);
    }
    // 横ループ 10..19: ループ k は行 2k, 2k+1 を覆う
    for (int k = 0; k < N / 2; k++) {
        vector<pair<int, int>> b;
        for (int j = 0; j < N; j++) b.push_back({2 * k, j});
        for (int j = N - 1; j >= 0; j--) b.push_back({2 * k + 1, j});
        belts.push_back(b);
    }
}

int v_belt_id(int col) { return col / 2; }
int h_belt_id(int row) { return N / 2 + row / 2; }

// (r,c) の縦ループ内位置
int v_pos(int r, int c) {
    if (c % 2 == 0) return r;
    return N + (N - 1 - r);  // = 39 - r
}
// (r,c) の横ループ内位置
int h_pos(int r, int c) {
    if (r % 2 == 0) return c;
    return N + (N - 1 - c);  // = 39 - c
}

void try_remove() {
    if (grid[EXIT_R][EXIT_C] == current_target) {
        grid[EXIT_R][EXIT_C] = -1;
        current_target++;
    }
}

void rotate_step(int m, int d) {
    auto& cells = belts[m];
    int L = (int)cells.size();
    if (d == 1) {
        int last = grid[cells[L - 1].first][cells[L - 1].second];
        for (int x = L - 1; x >= 1; x--) {
            grid[cells[x].first][cells[x].second] =
                grid[cells[x - 1].first][cells[x - 1].second];
        }
        grid[cells[0].first][cells[0].second] = last;
    } else {
        int first = grid[cells[0].first][cells[0].second];
        for (int x = 0; x < L - 1; x++) {
            grid[cells[x].first][cells[x].second] =
                grid[cells[x + 1].first][cells[x + 1].second];
        }
        grid[cells[L - 1].first][cells[L - 1].second] = first;
    }
    ops.push_back({m, d});
    try_remove();
}

// 位置差 (to-from) mod L だけ最短方向で回す
void rotate_min(int m, int delta_signed) {
    int L = (int)belts[m].size();
    int d = ((delta_signed % L) + L) % L;
    if (d == 0) return;
    int dir, cnt;
    if (d <= L - d) {
        dir = 1;
        cnt = d;
    } else {
        dir = -1;
        cnt = L - d;
    }
    for (int i = 0; i < cnt; i++) rotate_step(m, dir);
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) cin >> grid[i][j];

    build_belts();

    // ループの出力
    cout << belts.size() << "\n";
    for (auto& b : belts) {
        cout << b.size();
        for (auto [i, j] : b) cout << " " << i << " " << j;
        cout << "\n";
    }

    current_target = 0;
    if (grid[EXIT_R][EXIT_C] == 0) {
        // 初期状態で箱 0 が出口にあれば、最初の操作前に取り除かれる
        grid[EXIT_R][EXIT_C] = -1;
        current_target = 1;
    }

    while (current_target < N * N) {
        int k = current_target;

        // 箱 k の現在位置を探す
        int br = -1, bc = -1;
        for (int i = 0; i < N && br == -1; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == k) {
                    br = i;
                    bc = j;
                    break;
                }
            }
        }
        if (br == -1) break;  // 念の為

        int hb = h_belt_id(br);
        int vb = v_belt_id(EXIT_C);  // = 5

        // 4 通りの「横ループ操作後の到達セル」から最良を選ぶ
        int best_total = INT_MAX;
        int best_tr = br, best_tc = bc;
        int h_from = h_pos(br, bc);
        int v_to_target = v_pos(EXIT_R, EXIT_C);  // = 0

        for (int dr = 0; dr < 2; dr++) {
            int tr = 2 * (br / 2) + dr;
            for (int tc : {EXIT_C, EXIT_C + 1}) {
                int h_to = h_pos(tr, tc);
                int hd = ((h_to - h_from) % LOOP_LEN + LOOP_LEN) % LOOP_LEN;
                int hops = min(hd, LOOP_LEN - hd);
                int v_from = v_pos(tr, tc);
                int vd = ((v_to_target - v_from) % LOOP_LEN + LOOP_LEN) %
                         LOOP_LEN;
                int vops = min(vd, LOOP_LEN - vd);
                int total = hops + vops;
                if (total < best_total) {
                    best_total = total;
                    best_tr = tr;
                    best_tc = tc;
                }
            }
        }

        // 横ループ操作: 箱 k を (best_tr, best_tc) に移す
        int h_to = h_pos(best_tr, best_tc);
        int hd = ((h_to - h_from) % LOOP_LEN + LOOP_LEN) % LOOP_LEN;
        rotate_min(hb, hd);

        // 既に取り除かれていたら次へ（横操作中に出口に乗ったケース）
        if (current_target != k) continue;

        // 縦ループ操作: (best_tr, best_tc) -> (0, 10)
        int v_from = v_pos(best_tr, best_tc);
        int vd = ((v_to_target - v_from) % LOOP_LEN + LOOP_LEN) % LOOP_LEN;
        rotate_min(vb, vd);

        // 進捗なしなら無限ループ防止
        if (current_target == k) break;
    }

    cout << ops.size() << "\n";
    for (auto [m, d] : ops) cout << m << " " << d << "\n";

    return 0;
}
