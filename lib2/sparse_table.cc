// Sparse Table RMQ 範囲最小値クエリ O(1) クエリ O(N log N) 構築

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
using namespace std;

// ========== ライブラリ部分 ==========

// Sparse Table（スパーステーブル）
// 冪等な演算（min, max, gcd等）に対する範囲クエリをO(1)で処理
template<typename T>
class SparseTable {
private:
    vector<vector<T>> table;
    vector<int> log_table;
    function<T(T, T)> op;
    int n;

public:
    // コンストラクタ
    // arr: 配列, operation: 演算（例: min, max, gcd）
    SparseTable(const vector<T>& arr, function<T(T, T)> operation) : op(operation), n(arr.size()) {
        if (n == 0) return;

        // log_table[i] = floor(log2(i))
        log_table.resize(n + 1);
        log_table[1] = 0;
        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i / 2] + 1;
        }

        // テーブルの構築
        int max_log = log_table[n] + 1;
        table.assign(max_log, vector<T>(n));

        // 長さ1の区間
        for (int i = 0; i < n; i++) {
            table[0][i] = arr[i];
        }

        // 長さ2^kの区間
        for (int k = 1; k < max_log; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                table[k][i] = op(table[k-1][i], table[k-1][i + (1 << (k-1))]);
            }
        }
    }

    // 範囲[l, r]での演算結果を取得（0-indexed, rは含む）
    T query(int l, int r) {
        if (l > r || l < 0 || r >= n) return T();
        int len = r - l + 1;
        int k = log_table[len];
        return op(table[k][l], table[k][r - (1 << k) + 1]);
    }

    // 配列のサイズを取得
    int size() const { return n; }
};

// Range Minimum Query用のSparse Table
template<typename T>
class RMQ : public SparseTable<T> {
public:
    RMQ(const vector<T>& arr) : SparseTable<T>(arr, [](T a, T b) { return min(a, b); }) {}
};

// Range Maximum Query用のSparse Table
template<typename T>
class RMaxQ : public SparseTable<T> {
public:
    RMaxQ(const vector<T>& arr) : SparseTable<T>(arr, [](T a, T b) { return max(a, b); }) {}
};

// Range GCD Query用のSparse Table
class RGCDQ : public SparseTable<long long> {
private:
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
public:
    RGCDQ(const vector<long long>& arr) : SparseTable<long long>(arr, [this](long long a, long long b) { return gcd(a, b); }) {}
};

// ========== サンプルコード ==========

int main() {
    // 例1: Range Minimum Query (RMQ)
    cout << "例1: Range Minimum Query" << endl;
    vector<int> arr1 = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    RMQ<int> rmq(arr1);

    cout << "配列: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // いくつかの範囲クエリ
    vector<pair<int, int>> queries1 = {{0, 2}, {1, 4}, {3, 7}, {0, 8}};
    for (auto [l, r] : queries1) {
        cout << "min[" << l << ", " << r << "] = " << rmq.query(l, r) << endl;
    }
    cout << endl;

    // 例2: Range Maximum Query (RMaxQ)
    cout << "例2: Range Maximum Query" << endl;
    vector<int> arr2 = {2, 8, 3, 7, 1, 6, 4, 9, 5};
    RMaxQ<int> rmaxq(arr2);

    cout << "配列: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    vector<pair<int, int>> queries2 = {{0, 3}, {2, 5}, {4, 8}, {1, 7}};
    for (auto [l, r] : queries2) {
        cout << "max[" << l << ", " << r << "] = " << rmaxq.query(l, r) << endl;
    }
    cout << endl;

    // 例3: Range GCD Query
    cout << "例3: Range GCD Query" << endl;
    vector<long long> arr3 = {12, 18, 24, 36, 48, 60};
    RGCDQ rgcdq(arr3);

    cout << "配列: ";
    for (long long x : arr3) cout << x << " ";
    cout << endl;

    vector<pair<int, int>> queries3 = {{0, 2}, {1, 3}, {2, 5}, {0, 5}};
    for (auto [l, r] : queries3) {
        cout << "gcd[" << l << ", " << r << "] = " << rgcdq.query(l, r) << endl;
    }
    cout << endl;

    // 例4: カスタム演算（範囲での積）
    cout << "例4: カスタム演算（範囲での積）" << endl;
    vector<int> arr4 = {1, 2, 3, 2, 1, 4, 2, 1};

    // 注意: 積は冪等ではないため、正確性は保証されない
    // デモンストレーション目的のみ
    SparseTable<int> product_st(arr4, [](int a, int b) { return a * b; });

    cout << "配列: ";
    for (int x : arr4) cout << x << " ";
    cout << endl;
    cout << "注意: 積は冪等ではないため、結果は正確ではありません" << endl;

    // 正確な積の計算（参考）
    auto exact_product = [&](int l, int r) {
        int result = 1;
        for (int i = l; i <= r; i++) {
            result *= arr4[i];
        }
        return result;
    };

    for (auto [l, r] : vector<pair<int, int>>{{0, 2}, {1, 3}, {3, 5}}) {
        cout << "範囲[" << l << ", " << r << "] - ";
        cout << "SparseTable: " << product_st.query(l, r);
        cout << ", 正確な値: " << exact_product(l, r) << endl;
    }
    cout << endl;

    // 例5: 性能比較（大きな配列での応答時間）
    cout << "例5: 性能比較" << endl;
    vector<int> large_arr(100000);
    for (int i = 0; i < 100000; i++) {
        large_arr[i] = rand() % 1000;
    }

    RMQ<int> large_rmq(large_arr);
    cout << "要素数100,000の配列でSparse Tableを構築完了" << endl;
    cout << "クエリ例: min[10000, 50000] = " << large_rmq.query(10000, 50000) << endl;

    return 0;
}