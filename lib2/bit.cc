// Binary Indexed Tree BIT Fenwick Tree 区間和 O(log N)

#include <iostream>
#include <vector>
using namespace std;

// ========== ライブラリ本体 ==========

// Binary Indexed Tree (1-indexed)
template<typename T>
struct BIT {
    int n;
    vector<T> data;

    BIT(int n) : n(n), data(n + 1, 0) {}

    // i番目にxを加算
    void add(int i, T x) {
        for (; i <= n; i += i & -i) {
            data[i] += x;
        }
    }

    // [1, i]の和
    T sum(int i) {
        T res = 0;
        for (; i > 0; i -= i & -i) {
            res += data[i];
        }
        return res;
    }

    // [l, r]の和
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // 値xを持つ最小のindex（単調増加の場合）
    int lower_bound(T x) {
        int k = 1;
        while (k * 2 <= n) k *= 2;

        int i = 0;
        for (; k > 0; k /= 2) {
            if (i + k <= n && data[i + k] < x) {
                x -= data[i + k];
                i += k;
            }
        }
        return i + 1;
    }
};

// 2次元BIT
template<typename T>
struct BIT2D {
    int h, w;
    vector<vector<T>> data;

    BIT2D(int h, int w) : h(h), w(w), data(h + 1, vector<T>(w + 1, 0)) {}

    // (i, j)にxを加算
    void add(int i, int j, T x) {
        for (int a = i; a <= h; a += a & -a) {
            for (int b = j; b <= w; b += b & -b) {
                data[a][b] += x;
            }
        }
    }

    // [(1,1), (i,j)]の和
    T sum(int i, int j) {
        T res = 0;
        for (int a = i; a > 0; a -= a & -a) {
            for (int b = j; b > 0; b -= b & -b) {
                res += data[a][b];
            }
        }
        return res;
    }

    // [(i1,j1), (i2,j2)]の和
    T sum(int i1, int j1, int i2, int j2) {
        return sum(i2, j2) - sum(i1 - 1, j2) - sum(i2, j1 - 1) + sum(i1 - 1, j1 - 1);
    }
};

// 区間加算・点取得BIT（いもす法的な使い方）
template<typename T>
struct RangeAddBIT {
    BIT<T> bit;

    RangeAddBIT(int n) : bit(n) {}

    // [l, r]にxを加算
    void add(int l, int r, T x) {
        bit.add(l, x);
        if (r + 1 <= bit.n) {
            bit.add(r + 1, -x);
        }
    }

    // i番目の値を取得
    T get(int i) {
        return bit.sum(i);
    }
};

// 区間加算・区間和BIT
template<typename T>
struct RangeSumBIT {
    BIT<T> bit0, bit1;

    RangeSumBIT(int n) : bit0(n), bit1(n) {}

    // [l, r]にxを加算
    void add(int l, int r, T x) {
        bit0.add(l, -x * (l - 1));
        bit0.add(r + 1, x * r);
        bit1.add(l, x);
        bit1.add(r + 1, -x);
    }

    // [1, i]の和
    T sum(int i) {
        return bit0.sum(i) + bit1.sum(i) * i;
    }

    // [l, r]の和
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

// 転倒数を求める
long long count_inversions(vector<int>& a) {
    int n = a.size();
    int max_val = *max_element(a.begin(), a.end());

    BIT<int> bit(max_val);
    long long res = 0;

    for (int i = 0; i < n; i++) {
        res += i - bit.sum(a[i]);
        bit.add(a[i], 1);
    }

    return res;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なBIT
    cout << "例1: 基本的なBIT" << endl;
    BIT<int> bit(10);

    bit.add(1, 3);
    bit.add(3, 5);
    bit.add(5, 2);
    bit.add(7, 4);

    cout << "sum[1, 5] = " << bit.sum(1, 5) << endl;
    cout << "sum[3, 7] = " << bit.sum(3, 7) << endl;
    cout << endl;

    // 例2: 転倒数
    cout << "例2: 転倒数の計算" << endl;
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    cout << "配列: ";
    for (int x : a) cout << x << " ";
    cout << endl;
    cout << "転倒数: " << count_inversions(a) << endl;
    cout << endl;

    // 例3: 2次元BIT
    cout << "例3: 2次元BIT" << endl;
    BIT2D<int> bit2d(5, 5);

    bit2d.add(2, 2, 1);
    bit2d.add(3, 3, 2);
    bit2d.add(4, 4, 3);

    cout << "sum[(2,2), (4,4)] = " << bit2d.sum(2, 2, 4, 4) << endl;
    cout << endl;

    // 例4: 区間加算・点取得
    cout << "例4: 区間加算・点取得" << endl;
    RangeAddBIT<int> rabit(10);

    rabit.add(2, 5, 3);
    rabit.add(4, 8, 2);

    for (int i = 1; i <= 10; i++) {
        cout << "a[" << i << "] = " << rabit.get(i) << endl;
    }
    cout << endl;

    // 例5: lower_bound
    cout << "例5: lower_bound" << endl;
    BIT<int> bit2(10);
    for (int i = 1; i <= 10; i++) {
        bit2.add(i, i);
    }

    cout << "累積和が20以上になる最小のindex: " << bit2.lower_bound(20) << endl;
    cout << "累積和が50以上になる最小のindex: " << bit2.lower_bound(50) << endl;

    return 0;
}