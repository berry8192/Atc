#include <bits/stdc++.h>
using namespace std;

// AHC065 D.cc
// ベルコン構成: 全マスを通る単一のハミルトン閉路 (蛇行) 1本のみ
//   (0,0) → 列0を下降 → (19,0)
//   行19右, 行18左, 行17右, ... 行1右 (各列1..19の蛇行)
//   行0を (0,19) → (0,18) → ... → (0,1) で戻り、(0,0) に閉じる
// 操作: 各搬出ターゲットを最短回転 (±1 のうち短い方) で出口 (0,10) に運ぶ
// これは「単一蛇行 + 補助ベルコン」戦略のベースラインとなる。

static const int N = 20;
static const int EXIT_R = 0, EXIT_C = N / 2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---- ハミルトン閉路を構築 ----
    vector<pair<int, int>> belt;
    // 列0を上から下へ: (0,0)..(19,0)
    for (int i = 0; i < N; i++) belt.push_back({i, 0});
    // 行19から行1まで、列1..19を蛇行
    for (int k = 0; k < N - 1; k++) {
        int r = N - 1 - k;
        if (k % 2 == 0) {
            // 右向き: (r,1)..(r,19)
            for (int c = 1; c < N; c++) belt.push_back({r, c});
        } else {
            // 左向き: (r,19)..(r,1)
            for (int c = N - 1; c >= 1; c--) belt.push_back({r, c});
        }
    }
    // 行0を (0,19) → (0,1) で戻る ((0,0) に閉じる)
    for (int c = N - 1; c >= 1; c--) belt.push_back({0, c});

    int L = (int)belt.size();
    assert(L == N * N);
    // 隣接性と閉路性の検証 (デバッグ用)
    for (int i = 0; i < L; i++) {
        auto [r1, c1] = belt[i];
        auto [r2, c2] = belt[(i + 1) % L];
        int md = abs(r1 - r2) + abs(c1 - c2);
        assert(md == 1);
    }

    // ---- 入力読み込み ----
    int n;
    cin >> n;
    vector<int> a(N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) cin >> a[i * N + j];

    // セル (r,c) → 閉路上の位置
    vector<int> cell_to_pos(N * N);
    for (int i = 0; i < L; i++) {
        auto [r, c] = belt[i];
        cell_to_pos[r * N + c] = i;
    }

    // 箱 v の初期位置 (閉路上)
    vector<int> pos(N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            pos[a[i * N + j]] = cell_to_pos[i * N + j];

    int e = cell_to_pos[EXIT_R * N + EXIT_C];

    // ---- ベルコン出力 ----
    cout << 1 << "\n";
    cout << L;
    for (auto& [r, c] : belt) cout << " " << r << " " << c;
    cout << "\n";

    // ---- 操作列を貪欲生成 ----
    // shift: 累積回転量 (+: d=+1 で増える, -: d=-1 で減る)
    // 箱 v の現在位置 = (pos[v] + shift) mod L
    vector<pair<int, int>> ops;
    long long shift = 0;
    int target = 0;
    // 初期状態で (0,10) に箱 0 があれば、操作前に取出
    if (a[EXIT_R * N + EXIT_C] == 0) target = 1;

    while (target < N * N) {
        int p = (int)(((pos[target] + shift) % L + L) % L);
        // d=+1 を rot 回: 箱は位置 +rot へ移動 → p + rot ≡ e (mod L)
        int rot_plus = (e - p + L) % L;
        int rot_minus = (p - e + L) % L;
        int rotations, dir;
        if (rot_plus <= rot_minus) {
            rotations = rot_plus;
            dir = 1;
        } else {
            rotations = rot_minus;
            dir = -1;
        }
        for (int i = 0; i < rotations; i++) ops.push_back({0, dir});
        shift += (long long)dir * rotations;
        // この時点で box target は出口にあり、自動搬出される
        target++;
    }

    // ---- 操作列出力 ----
    cout << ops.size() << "\n";
    for (auto& [m, d] : ops) cout << m << " " << d << "\n";

    cerr << "T=" << ops.size() << "\n";
    return 0;
}
