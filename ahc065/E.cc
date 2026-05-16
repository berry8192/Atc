#include <bits/stdc++.h>
using namespace std;

// AHC065 E.cc
// ベルコン構成:
//   belt 0     : 全マス蛇行ハミルトン閉路 (D.cc と同一)
//   belt 1..10 : 縦 2x20 ループ (列ペア (2k, 2k+1), k=0..9, 各長さ 40)
// 各セルはちょうど 2 本のベルコンに含まれる (上限)。
// 操作部分は別途指示で実装する。今は空の操作列を出力する。

static const int N = 20;
static const int EXIT_R = 0, EXIT_C = N / 2;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<pair<int, int>>> belts;

    // ---- belt 0: 蛇行ハミルトン閉路 ----
    {
        vector<pair<int, int>> b;
        for (int i = 0; i < N; i++) b.push_back({i, 0});
        for (int k = 0; k < N - 1; k++) {
            int r = N - 1 - k;
            if (k % 2 == 0) {
                for (int c = 1; c < N; c++) b.push_back({r, c});
            } else {
                for (int c = N - 1; c >= 1; c--) b.push_back({r, c});
            }
        }
        for (int c = N - 1; c >= 1; c--) b.push_back({0, c});
        belts.push_back(b);
    }

    // ---- belt 1..10: 縦 2x20 ループ ----
    for (int k = 0; k < N / 2; k++) {
        int c0 = 2 * k, c1 = 2 * k + 1;
        vector<pair<int, int>> b;
        for (int i = 0; i < N; i++) b.push_back({i, c0});
        for (int i = N - 1; i >= 0; i--) b.push_back({i, c1});
        belts.push_back(b);
    }

    // ---- 検証 (各ベルコンが有効か、各セルがちょうど 2 本か) ----
    {
        int cnt[N][N] = {};
        for (auto& b : belts) {
            int L = (int)b.size();
            assert(L >= 2);
            set<pair<int, int>> seen(b.begin(), b.end());
            assert((int)seen.size() == L);
            for (int i = 0; i < L; i++) {
                auto [r1, c1] = b[i];
                auto [r2, c2] = b[(i + 1) % L];
                assert(abs(r1 - r2) + abs(c1 - c2) == 1);
                cnt[r1][c1]++;
            }
        }
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) assert(cnt[i][j] == 2);
    }

    // ---- 入力読み込み ----
    int n;
    cin >> n;
    vector<int> a(N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) cin >> a[i * N + j];

    // ---- ベルコン出力 ----
    cout << belts.size() << "\n";
    for (auto& b : belts) {
        cout << b.size();
        for (auto& [r, c] : b) cout << " " << r << " " << c;
        cout << "\n";
    }

    // ---- 操作列 (空) ----
    cout << 0 << "\n";

    return 0;
}
