// Wavelet Matrix ウェーブレット行列 区間k番目 区間カウント O(log σ)

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

// ========== ライブラリ部分 ==========

// Bit Vector（ビットベクトル）
class BitVector {
private:
    vector<int> bits;
    vector<int> rank_table;
    int size;

public:
    BitVector() : size(0) {}

    BitVector(const vector<bool>& b) : size(b.size()) {
        bits.assign((size + 31) / 32, 0);
        rank_table.assign((size + 31) / 32 + 1, 0);

        for (int i = 0; i < size; i++) {
            if (b[i]) {
                bits[i / 32] |= (1 << (i % 32));
            }
        }

        // rank表の構築
        for (int i = 0; i < (int)bits.size(); i++) {
            rank_table[i + 1] = rank_table[i] + __builtin_popcount(bits[i]);
        }
    }

    // 位置posのビット値を取得
    bool access(int pos) const {
        if (pos < 0 || pos >= size) return false;
        return (bits[pos / 32] >> (pos % 32)) & 1;
    }

    // [0, pos)のビット1の個数
    int rank1(int pos) const {
        if (pos <= 0) return 0;
        if (pos >= size) pos = size;
        int block = pos / 32;
        int offset = pos % 32;
        int result = rank_table[block];
        if (offset > 0) {
            result += __builtin_popcount(bits[block] & ((1u << offset) - 1));
        }
        return result;
    }

    // [0, pos)のビット0の個数
    int rank0(int pos) const {
        return pos - rank1(pos);
    }

    int get_size() const { return size; }
};

// Wavelet Matrix
template<typename T>
class WaveletMatrix {
private:
    vector<BitVector> bv;
    vector<int> zeros;
    vector<T> sorted_values;
    int height;
    int n;

    // 値を座標圧縮
    void compress(vector<T>& arr) {
        sorted_values = arr;
        sort(sorted_values.begin(), sorted_values.end());
        sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());

        for (auto& x : arr) {
            x = lower_bound(sorted_values.begin(), sorted_values.end(), x) - sorted_values.begin();
        }
    }

public:
    WaveletMatrix(vector<T> arr) : n(arr.size()) {
        if (n == 0) {
            height = 0;
            return;
        }

        compress(arr);
        height = 32 - __builtin_clz(sorted_values.size());
        if ((1 << height) < (int)sorted_values.size()) height++;

        bv.resize(height);
        zeros.resize(height);

        for (int level = height - 1; level >= 0; level--) {
            vector<bool> bits(n);
            vector<T> left, right;

            for (int i = 0; i < n; i++) {
                bool bit = (arr[i] >> level) & 1;
                bits[i] = bit;
                if (bit) {
                    right.push_back(arr[i]);
                } else {
                    left.push_back(arr[i]);
                }
            }

            bv[level] = BitVector(bits);
            zeros[level] = left.size();
            arr = left;
            arr.insert(arr.end(), right.begin(), right.end());
        }
    }

    // 位置posの値を取得
    T access(int pos) {
        if (pos < 0 || pos >= n) return T();

        T result = 0;
        for (int level = height - 1; level >= 0; level--) {
            bool bit = bv[level].access(pos);
            result |= T(bit) << level;

            if (bit) {
                pos = zeros[level] + bv[level].rank1(pos);
            } else {
                pos = bv[level].rank0(pos);
            }
        }
        return sorted_values[result];
    }

    // [l, r)でのvalの出現回数
    int count(int l, int r, T val) {
        auto it = lower_bound(sorted_values.begin(), sorted_values.end(), val);
        if (it == sorted_values.end() || *it != val) return 0;
        int compressed_val = it - sorted_values.begin();

        return count_compressed(l, r, compressed_val);
    }

    // [l, r)でのk番目（0-indexed）の値
    T kth(int l, int r, int k) {
        if (k < 0 || k >= r - l) return T();

        int compressed_result = kth_compressed(l, r, k);
        return sorted_values[compressed_result];
    }

    // [l, r)でval未満の値の個数
    int count_less(int l, int r, T val) {
        auto it = lower_bound(sorted_values.begin(), sorted_values.end(), val);
        int compressed_val = it - sorted_values.begin();
        return count_less_compressed(l, r, compressed_val);
    }

private:
    int count_compressed(int l, int r, int val) {
        for (int level = height - 1; level >= 0; level--) {
            bool bit = (val >> level) & 1;
            if (bit) {
                l = zeros[level] + bv[level].rank1(l);
                r = zeros[level] + bv[level].rank1(r);
            } else {
                l = bv[level].rank0(l);
                r = bv[level].rank0(r);
            }
        }
        return r - l;
    }

    int kth_compressed(int l, int r, int k) {
        int result = 0;
        for (int level = height - 1; level >= 0; level--) {
            int zeros_count = bv[level].rank0(r) - bv[level].rank0(l);
            if (k < zeros_count) {
                l = bv[level].rank0(l);
                r = bv[level].rank0(r);
            } else {
                result |= 1 << level;
                k -= zeros_count;
                l = zeros[level] + bv[level].rank1(l);
                r = zeros[level] + bv[level].rank1(r);
            }
        }
        return result;
    }

    int count_less_compressed(int l, int r, int val) {
        int result = 0;
        for (int level = height - 1; level >= 0; level--) {
            bool bit = (val >> level) & 1;
            int zeros_count = bv[level].rank0(r) - bv[level].rank0(l);

            if (bit) {
                result += zeros_count;
                l = zeros[level] + bv[level].rank1(l);
                r = zeros[level] + bv[level].rank1(r);
            } else {
                l = bv[level].rank0(l);
                r = bv[level].rank0(r);
            }
        }
        return result;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な操作
    cout << "例1: 基本的なWavelet Matrix操作" << endl;
    vector<int> arr1 = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    WaveletMatrix<int> wm1(arr1);

    cout << "配列: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // アクセス
    cout << "access(3) = " << wm1.access(3) << endl;
    cout << "access(7) = " << wm1.access(7) << endl;
    cout << endl;

    // 例2: 区間でのk番目の値
    cout << "例2: 区間でのk番目の値" << endl;
    vector<pair<int, int>> ranges = {{0, 5}, {2, 8}, {1, 6}};

    for (auto [l, r] : ranges) {
        cout << "範囲[" << l << ", " << r << "):" << endl;
        for (int k = 0; k < r - l; k++) {
            cout << "  " << k << "番目: " << wm1.kth(l, r, k) << endl;
        }
        cout << endl;
    }

    // 例3: 区間での値の出現回数
    cout << "例3: 区間での値の出現回数" << endl;
    vector<int> values = {1, 2, 3, 5, 9};

    for (int val : values) {
        cout << "値" << val << "の出現回数:" << endl;
        cout << "  全体: " << wm1.count(0, arr1.size(), val) << endl;
        cout << "  [2, 7): " << wm1.count(2, 7, val) << endl;
    }
    cout << endl;

    // 例4: 区間での値未満の個数
    cout << "例4: 区間での値未満の個数" << endl;
    for (int val : {3, 5, 7}) {
        cout << "値" << val << "未満の個数:" << endl;
        cout << "  全体: " << wm1.count_less(0, arr1.size(), val) << endl;
        cout << "  [1, 6): " << wm1.count_less(1, 6, val) << endl;
    }
    cout << endl;

    // 例5: より大きな配列での性能確認
    cout << "例5: 大きな配列での操作" << endl;
    vector<int> large_arr(10000);
    for (int i = 0; i < 10000; i++) {
        large_arr[i] = rand() % 100;
    }

    WaveletMatrix<int> wm_large(large_arr);
    cout << "要素数10,000の配列でWavelet Matrixを構築完了" << endl;

    // いくつかのクエリ例
    cout << "範囲[1000, 5000)での中央値: " << wm_large.kth(1000, 5000, 2000) << endl;
    cout << "範囲[0, 1000)での50未満の個数: " << wm_large.count_less(0, 1000, 50) << endl;

    return 0;
}