// 色付きUnionFind colored_union_find 連結成分 色管理

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

// ========== ライブラリ本体 ==========

// 色付きUnionFind（各連結成分が色を持つ）
struct ColoredUnionFind {
    int n;
    vector<int> parent, rank, size;
    vector<int> color;  // 各頂点の色（根の色が成分全体の色）
    map<int, set<int>> color_groups;  // color -> 根のset
    map<int, int> color_count;  // 各色の要素数

    ColoredUnionFind(int n) : n(n), parent(n), rank(n, 0), size(n, 1), color(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            color[i] = i;  // 初期色は頂点番号
            color_groups[i].insert(i);
            color_count[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;

        if (rank[x] < rank[y]) swap(x, y);

        // yの色情報を削除
        int y_color = color[y];
        color_groups[y_color].erase(y);
        color_count[y_color] -= size[y];
        if (color_groups[y_color].empty()) {
            color_groups.erase(y_color);
            color_count.erase(y_color);
        }

        // 統合
        parent[y] = x;
        size[x] += size[y];
        if (rank[x] == rank[y]) rank[x]++;

        // xの色情報を更新
        color_count[color[x]] += size[y];

        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int get_size(int x) {
        return size[find(x)];
    }

    int get_color(int x) {
        return color[find(x)];
    }

    void set_color(int x, int new_color) {
        x = find(x);
        int old_color = color[x];

        if (old_color == new_color) return;

        // 古い色から削除
        color_groups[old_color].erase(x);
        color_count[old_color] -= size[x];
        if (color_groups[old_color].empty()) {
            color_groups.erase(old_color);
            color_count.erase(old_color);
        }

        // 新しい色に追加
        color[x] = new_color;
        color_groups[new_color].insert(x);
        color_count[new_color] += size[x];
    }

    // xを含む連結成分とその隣接成分を全て統合して色を変える
    void paint_and_merge(int x, int new_color, vector<set<int>>& adj) {
        x = find(x);
        set<int> to_merge;

        // 隣接する同色の成分を探す
        for (int neighbor : adj[x]) {
            neighbor = find(neighbor);
            if (neighbor != x && get_color(neighbor) == get_color(x)) {
                to_merge.insert(neighbor);
            }
        }

        // 色を変更
        set_color(x, new_color);

        // 同色だった隣接成分と統合
        for (int y : to_merge) {
            if (find(y) != find(x)) {
                unite(x, y);
            }
        }
    }

    int count_color(int c) {
        return color_count.count(c) ? color_count[c] : 0;
    }

    vector<int> get_roots_with_color(int c) {
        vector<int> result;
        if (color_groups.count(c)) {
            for (int root : color_groups[c]) {
                result.push_back(root);
            }
        }
        return result;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例: ABC380 E のような問題
    cout << "例: 1次元のバケット塗りつぶし" << endl;

    int n = 5;
    ColoredUnionFind uf(n);
    vector<set<int>> adj(n);  // 隣接リスト

    // 1次元の隣接関係を構築
    for (int i = 0; i < n - 1; i++) {
        adj[i].insert(i + 1);
        adj[i + 1].insert(i);
    }

    cout << "初期状態:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "セル" << i << ": 色" << uf.get_color(i) << endl;
    }
    cout << endl;

    // クエリ1: セル4を色3に塗る
    cout << "クエリ1: セル4を色3に塗る" << endl;
    uf.set_color(4, 3);
    cout << "色3の個数: " << uf.count_color(3) << endl;
    cout << endl;

    // クエリ2: セル3を色1に塗る（隣接する同色と統合）
    cout << "クエリ2: セル3を色1に塗る" << endl;
    uf.set_color(3, 1);

    // 隣接チェック
    for (int neighbor : adj[3]) {
        if (uf.get_color(neighbor) == 1) {
            uf.unite(3, neighbor);
        }
    }

    cout << "色1の個数: " << uf.count_color(1) << endl;
    cout << endl;

    // 最終状態
    cout << "最終状態:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "セル" << i << ": 色" << uf.get_color(i)
             << " (成分サイズ" << uf.get_size(i) << ")" << endl;
    }

    return 0;
}