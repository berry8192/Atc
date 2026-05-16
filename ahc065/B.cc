#include <bits/stdc++.h>
using namespace std;

// AHC065 B.cc
// 構成:
//   belt 0      : 縦ベルコン (cols 10-11 を一周, 長さ 40)
//   belt 1..10  : 横ベルコン 2x20 (行 (2k, 2k+1) 全幅, 長さ 40)
//   belt 11..   : 2x1 縦往復ベルコン (cols 0-9, 12-19 の各 row pair, 長さ 2)
// 各セルは横ベルコン1本 + (縦ベルコン or 2x1 filler)1本 = 2本。
// 搬出ロジック: A.cc 流 (横ベルコンで cols 10/11 に寄せ → 縦ベルコンで (0,10) に運ぶ)

static const int N = 20;
static const int EXIT_R = 0, EXIT_C = N / 2;  // (0, 10)
static const int VBELT = 0;
static const int VLEN = 40;
static const int HLEN = 40;

vector<vector<pair<int, int>>> belts;
int grid[N][N];
vector<pair<int, int>> ops;
int current_target;

void build_belts() {
    belts.clear();
    // 0: 縦ベルコン (cols 10, 11)
    {
        vector<pair<int, int>> b;
        for (int i = 0; i < N; i++) b.push_back({i, 10});
        for (int i = N - 1; i >= 0; i--) b.push_back({i, 11});
        belts.push_back(b);
    }
    // 1..10: 横ベルコン 2x20
    for (int k = 0; k < N / 2; k++) {
        vector<pair<int, int>> b;
        for (int j = 0; j < N; j++) b.push_back({2 * k, j});
        for (int j = N - 1; j >= 0; j--) b.push_back({2 * k + 1, j});
        belts.push_back(b);
    }
    // 11..: 2x1 縦 filler (cols 0-9, 12-19)
    for (int k = 0; k < N / 2; k++) {
        for (int c = 0; c < N; c++) {
            if (c == 10 || c == 11) continue;
            vector<pair<int, int>> b;
            b.push_back({2 * k, c});
            b.push_back({2 * k + 1, c});
            belts.push_back(b);
        }
    }
}

int h_belt_id(int row) { return 1 + row / 2; }
int h_pos(int r, int c) { return (r % 2 == 0) ? c : 39 - c; }
int v_pos(int r, int c) { return (c == 10) ? r : 39 - r; }

// 2x1 filler belt id at (row_pair, col), col != 10, 11
int filler_id(int row_pair, int c) {
    int off = (c < 10) ? c : (c - 2);
    return 11 + 18 * row_pair + off;
}

int dist_to_vert(int c) { return min(abs(c - 10), abs(c - 11)); }

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
        for (int x = L - 1; x >= 1; x--)
            grid[cells[x].first][cells[x].second] =
                grid[cells[x - 1].first][cells[x - 1].second];
        grid[cells[0].first][cells[0].second] = last;
    } else {
        int first = grid[cells[0].first][cells[0].second];
        for (int x = 0; x < L - 1; x++)
            grid[cells[x].first][cells[x].second] =
                grid[cells[x + 1].first][cells[x + 1].second];
        grid[cells[L - 1].first][cells[L - 1].second] = first;
    }
    ops.push_back({m, d});
    try_remove();
}

void rotate_belt_min(int m, int delta_signed) {
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

    cout << belts.size() << "\n";
    for (auto& b : belts) {
        cout << b.size();
        for (auto [i, j] : b) cout << " " << i << " " << j;
        cout << "\n";
    }

    current_target = 0;
    if (grid[EXIT_R][EXIT_C] == 0) {
        grid[EXIT_R][EXIT_C] = -1;
        current_target = 1;
    }

    while (current_target < N * N) {
        int k = current_target;
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
        if (br == -1) break;

        int hb = h_belt_id(br);
        int vb = VBELT;

        // 4 通りの「横ベルコン操作後の到達セル」から最良を選ぶ
        int best_total = INT_MAX;
        int best_tr = br, best_tc = bc;
        int h_from = h_pos(br, bc);
        int v_to_target = v_pos(EXIT_R, EXIT_C);

        for (int dr = 0; dr < 2; dr++) {
            int tr = 2 * (br / 2) + dr;
            for (int tc : {10, 11}) {
                int h_to = h_pos(tr, tc);
                int hd = (h_to - h_from + HLEN) % HLEN;
                int hops = min(hd, HLEN - hd);
                int v_from = v_pos(tr, tc);
                int vd = (v_to_target - v_from + VLEN) % VLEN;
                int vops = min(vd, VLEN - vd);
                int total = hops + vops;
                if (total < best_total) {
                    best_total = total;
                    best_tr = tr;
                    best_tc = tc;
                }
            }
        }

        // 横ベルコン
        int h_to = h_pos(best_tr, best_tc);
        int hd = (h_to - h_from + HLEN) % HLEN;

        // 2 番目に小さい箱が縦ベルコンから遠ざかるなら 2x1 filler で先に swap
        if (hd != 0) {
            auto& cells_h = belts[hb];
            int B2_val = INT_MAX, B2_r = -1, B2_c = -1;
            for (auto& [r, c] : cells_h) {
                int v = grid[r][c];
                if (v >= 0 && (r != br || c != bc) && v < B2_val) {
                    B2_val = v;
                    B2_r = r;
                    B2_c = c;
                }
            }
            if (B2_r != -1 && B2_c != bc && B2_c != 10 && B2_c != 11) {
                int pre = dist_to_vert(B2_c);
                int p2 = h_pos(B2_r, B2_c);
                int new_p = (p2 + hd) % HLEN;
                int new_c = (new_p < N) ? new_p : (39 - new_p);
                int post = dist_to_vert(new_c);
                if (post > pre) {
                    int fid = filler_id(br / 2, B2_c);
                    rotate_step(fid, 1);
                }
            }
        }

        rotate_belt_min(hb, hd);

        if (current_target != k) continue;

        // 縦ベルコン
        int v_from = v_pos(best_tr, best_tc);
        int vd = (v_to_target - v_from + VLEN) % VLEN;
        rotate_belt_min(vb, vd);

        if (current_target == k) break;  // 進捗なし防止
    }

    cout << ops.size() << "\n";
    for (auto [m, d] : ops) cout << m << " " << d << "\n";

    return 0;
}
