// いもす法・累積和・累積積 imos_cumsum O(N)

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// ========== ライブラリ部分 ==========

// 1次元いもす法クラス
template<typename T>
class imos_1d {
private:
    vector<T> diff;
    int n;

public:
    imos_1d(int size) : n(size), diff(size + 1, 0) {}

    // 区間[l, r)にvalueを加算
    void add(int l, int r, T value) {
        if (l < 0 || r > n || l >= r) return;
        diff[l] += value;
        diff[r] -= value;
    }

    // 実際の配列を構築
    vector<T> build() {
        vector<T> result(n);
        result[0] = diff[0];
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] + diff[i];
        }
        return result;
    }
};

// 2次元いもす法クラス
template<typename T>
class imos_2d {
private:
    vector<vector<T>> diff;
    int h, w;

public:
    imos_2d(int height, int width) : h(height), w(width), diff(height + 1, vector<T>(width + 1, 0)) {}

    // 矩形領域(r1,c1)から(r2,c2)にvalueを加算（両端含む）
    void add(int r1, int c1, int r2, int c2, T value) {
        if (r1 < 0 || r2 >= h || c1 < 0 || c2 >= w || r1 > r2 || c1 > c2) return;
        diff[r1][c1] += value;
        diff[r1][c2 + 1] -= value;
        diff[r2 + 1][c1] -= value;
        diff[r2 + 1][c2 + 1] += value;
    }

    // 実際の配列を構築
    vector<vector<T>> build() {
        vector<vector<T>> result(h, vector<T>(w, 0));

        // 横方向の累積和
        for (int i = 0; i < h; i++) {
            result[i][0] = diff[i][0];
            for (int j = 1; j < w; j++) {
                result[i][j] = result[i][j - 1] + diff[i][j];
            }
        }

        // 縦方向の累積和
        for (int j = 0; j < w; j++) {
            for (int i = 1; i < h; i++) {
                result[i][j] += result[i - 1][j];
            }
        }

        return result;
    }
};

// 1次元累積和クラス
template<typename T>
class cumsum_1d {
private:
    vector<T> sum;

public:
    cumsum_1d(const vector<T>& arr) {
        int n = arr.size();
        sum.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + arr[i];
        }
    }

    // 区間[l, r)の和
    T query(int l, int r) {
        if (l < 0 || r > sum.size() - 1 || l >= r) return 0;
        return sum[r] - sum[l];
    }

    // インデックスiまでの和
    T prefix(int i) {
        if (i < 0) return 0;
        if (i >= sum.size() - 1) return sum.back();
        return sum[i + 1];
    }
};

// 2次元累積和クラス
template<typename T>
class cumsum_2d {
private:
    vector<vector<T>> sum;

public:
    cumsum_2d(const vector<vector<T>>& grid) {
        int h = grid.size();
        int w = grid[0].size();
        sum.assign(h + 1, vector<T>(w + 1, 0));

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + grid[i][j];
            }
        }
    }

    // 矩形領域(r1,c1)から(r2,c2)の和（両端含む）
    T query(int r1, int c1, int r2, int c2) {
        if (r1 < 0 || r2 >= sum.size() - 1 || c1 < 0 || c2 >= sum[0].size() - 1 || r1 > r2 || c1 > c2) return 0;
        return sum[r2 + 1][c2 + 1] - sum[r1][c2 + 1] - sum[r2 + 1][c1] + sum[r1][c1];
    }
};

// 累積積クラス（modular arithmetic）
template<typename T>
class cumproduct {
private:
    vector<T> prod;
    vector<T> inv_prod;
    T mod;

    T mod_pow(T base, T exp, T mod) {
        T result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }

    T mod_inv(T a, T mod) {
        return mod_pow(a, mod - 2, mod);
    }

public:
    cumproduct(const vector<T>& arr, T modulo = 1000000007) : mod(modulo) {
        int n = arr.size();
        prod.resize(n + 1, 1);
        inv_prod.resize(n + 1, 1);

        for (int i = 0; i < n; i++) {
            prod[i + 1] = (prod[i] * arr[i]) % mod;
        }

        inv_prod[n] = mod_inv(prod[n], mod);
        for (int i = n - 1; i >= 0; i--) {
            inv_prod[i] = (inv_prod[i + 1] * arr[i]) % mod;
        }
    }

    // 区間[l, r)の積
    T query(int l, int r) {
        if (l < 0 || r > prod.size() - 1 || l >= r) return 1;
        return (prod[r] * inv_prod[l]) % mod;
    }
};

// 差分配列から元の配列を復元
template<typename T>
vector<T> restore_from_diff(const vector<T>& diff) {
    vector<T> result(diff.size());
    result[0] = diff[0];
    for (int i = 1; i < diff.size(); i++) {
        result[i] = result[i - 1] + diff[i];
    }
    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 1次元いもす法
    cout << "例1: 1次元いもす法" << endl;
    imos_1d<int> imos(10);
    imos.add(1, 5, 3);  // [1, 5)に+3
    imos.add(3, 8, 2);  // [3, 8)に+2
    imos.add(0, 3, 1);  // [0, 3)に+1

    auto result1 = imos.build();
    cout << "結果: ";
    for (int x : result1) cout << x << " ";
    cout << endl << endl;

    // 例2: 2次元いもす法
    cout << "例2: 2次元いもす法" << endl;
    imos_2d<int> imos2d(5, 5);
    imos2d.add(1, 1, 3, 3, 1);  // (1,1)から(3,3)に+1
    imos2d.add(0, 0, 2, 2, 2);  // (0,0)から(2,2)に+2

    auto result2 = imos2d.build();
    cout << "結果:" << endl;
    for (auto& row : result2) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    cout << endl;

    // 例3: 1次元累積和
    cout << "例3: 1次元累積和" << endl;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cumsum_1d<int> cs1d(arr);

    cout << "配列: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << "区間[2, 7)の和: " << cs1d.query(2, 7) << endl;
    cout << "インデックス5までの和: " << cs1d.prefix(5) << endl;
    cout << endl;

    // 例4: 2次元累積和
    cout << "例4: 2次元累積和" << endl;
    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    cumsum_2d<int> cs2d(grid);

    cout << "グリッド:" << endl;
    for (auto& row : grid) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
    cout << "(1,1)から(2,2)の和: " << cs2d.query(1, 1, 2, 2) << endl;
    cout << endl;

    // 例5: 累積積（mod付き）
    cout << "例5: 累積積（mod付き）" << endl;
    vector<long long> arr2 = {2, 3, 4, 5, 6};
    cumproduct<long long> cp(arr2, 1000000007);

    cout << "配列: ";
    for (long long x : arr2) cout << x << " ";
    cout << endl;
    cout << "区間[1, 4)の積: " << cp.query(1, 4) << endl;
    cout << "区間[0, 5)の積: " << cp.query(0, 5) << endl;
    cout << endl;

    // 例6: 差分配列の復元
    cout << "例6: 差分配列の復元" << endl;
    vector<int> diff = {3, -1, 2, -2, 1, -3};
    auto restored = restore_from_diff(diff);

    cout << "差分配列: ";
    for (int x : diff) cout << x << " ";
    cout << endl;
    cout << "復元配列: ";
    for (int x : restored) cout << x << " ";
    cout << endl;

    return 0;
}