// 入力ヘルパーの使用例集

#include <bits/stdc++.h>
using namespace std;

// template_with_input.cc の入力ヘルパー部分をここに含める
// （実際は template_with_input.cc をコピペして使う）

// ========== よくある入力パターンの例 ==========

void example1() {
    // パターン1: N個の整数
    // 入力:
    // 5
    // 1 2 3 4 5

    INT(n);
    VEC(int, a, n);

    // aを使った処理
}

void example2() {
    // パターン2: N M と M本の辺（グラフ）
    // 入力:
    // 4 5
    // 1 2
    // 2 3
    // 3 4
    // 4 1
    // 2 4

    INT(n, m);
    auto edges = input_edges(m);  // 1-indexed を 0-indexed に自動変換

    // グラフ構築
    vvi graph(n);
    for (auto [u, v] : edges) {
        graph[u].pb(v);
        graph[v].pb(u);  // 無向グラフの場合
    }
}

void example3() {
    // パターン3: H×Wグリッド
    // 入力:
    // 3 4
    // ####
    // #..#
    // ####

    INT(h, w);
    GRID(grid, h);

    // グリッド処理
    rep(i, h) rep(j, w) {
        if (grid[i][j] == '#') {
            // 壁の処理
        }
    }
}

void example4() {
    // パターン4: クエリ処理
    // 入力:
    // 5
    // 1 3 5
    // 2 1
    // 1 4 2
    // 2 3
    // 2 5

    INT(q);
    rep(_, q) {
        INT(type);

        if (type == 1) {
            INT(x, y);
            // タイプ1の処理
        } else {
            INT(x);
            // タイプ2の処理
        }
    }
}

void example5() {
    // パターン5: 重み付きグラフ
    // 入力:
    // 4 5
    // 1 2 10
    // 2 3 20
    // 3 4 30
    // 4 1 40
    // 2 4 50

    INT(n, m);
    auto edges = input_weighted_edges(m);

    // 隣接リスト構築
    vector<vector<pair<int, ll>>> graph(n);
    for (auto [u, v, w] : edges) {
        graph[u].pb({v, w});
        graph[v].pb({u, w});  // 無向グラフの場合
    }
}

void example6() {
    // パターン6: 座標点の入力
    // 入力:
    // 5
    // 1 2
    // 3 4
    // 5 6
    // 7 8
    // 9 10

    INT(n);
    auto points = input_pairs<int, int>(n);

    for (auto [x, y] : points) {
        // 点の処理
    }
}

void example7() {
    // パターン7: 複数のベクトル
    // 入力:
    // 5
    // 1 2 3 4 5
    // 6 7 8 9 10
    // 11 12 13 14 15

    INT(n);
    VEC(int, a, n);
    VEC(int, b, n);
    VEC(int, c, n);

    rep(i, n) {
        // a[i], b[i], c[i] を使った処理
    }
}

void example8() {
    // パターン8: 2次元配列
    // 入力:
    // 3 4
    // 1 2 3 4
    // 5 6 7 8
    // 9 10 11 12

    INT(h, w);
    VVI(matrix, h, w);

    rep(i, h) rep(j, w) {
        // matrix[i][j] を使った処理
    }
}

void example9() {
    // パターン9: 木の入力（N頂点、N-1辺）
    // 入力:
    // 5
    // 1 2
    // 2 3
    // 2 4
    // 4 5

    INT(n);
    auto edges = input_edges(n - 1);

    vvi tree(n);
    for (auto [u, v] : edges) {
        tree[u].pb(v);
        tree[v].pb(u);
    }
}

void example10() {
    // パターン10: 文字列と数値の混在
    // 入力:
    // 3
    // abc 10
    // def 20
    // ghi 30

    INT(n);
    vector<pair<string, int>> data(n);
    rep(i, n) {
        input(data[i].first, data[i].second);
    }

    for (auto [s, val] : data) {
        // 処理
    }
}

// ========== 競技プログラミングでよく使うパターン ==========

void abc_pattern() {
    // AtCoder ABC の典型パターン

    // A問題（単純な計算）
    // INT(a, b, c);

    // B問題（配列処理）
    // INT(n);
    // VEC(int, a, n);

    // C問題（累積和、二分探索など）
    // INT(n, k);
    // VEC(ll, a, n);

    // D問題（グラフ、DP）
    // INT(n, m);
    // auto edges = input_edges(m);

    // E問題（セグ木、UnionFindなど）
    // INT(n, q);
    // クエリ処理

    // F問題（複雑なDP、数学）
    // 問題による
}

int main() {
    // 使用例を選んで実行
    // example1();
    // example2();
    // ...

    return 0;
}