// 二分探索 binary_search めぐる式 O(log N)

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;

// ========== ライブラリ部分 ==========

// 整数版二分探索（めぐる式）
// ok: 条件を満たす値, ng: 条件を満たさない値
// check: 判定関数（mid以下/以上が条件を満たすか）
// 最終的にokが条件を満たす境界値を返す
long long binary_search_int(long long ok, long long ng, function<bool(long long)> check) {
    while (abs(ok - ng) > 1) {
        long long mid = (ok + ng) / 2;
        if (check(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

// 実数版二分探索
// l: 左端, r: 右端
// check: 判定関数
// eps: 精度（デフォルト1e-9）、iterations: 反復回数（デフォルト100）
double binary_search_real(double l, double r, function<bool(double)> check,
                         double eps = 1e-9, int iterations = 100) {
    for (int i = 0; i < iterations && r - l > eps; i++) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

// 配列に対する二分探索（lower_bound相当）
// v[i] >= xとなる最小のインデックスを返す
template<typename T>
int lower_bound_index(const vector<T>& v, T x) {
    return binary_search_int(-1, v.size(), [&](long long mid) {
        return mid < 0 || v[mid] < x;
    }) + 1;
}

// 配列に対する二分探索（upper_bound相当）
// v[i] > xとなる最小のインデックスを返す
template<typename T>
int upper_bound_index(const vector<T>& v, T x) {
    return binary_search_int(-1, v.size(), [&](long long mid) {
        return mid < 0 || v[mid] <= x;
    }) + 1;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 整数の二分探索
    // 問題: x^2 >= 100を満たす最小の正整数xを求める
    cout << "例1: x^2 >= 100を満たす最小の正整数x" << endl;
    long long result1 = binary_search_int(1000, 0, [](long long x) {
        return x * x >= 100;
    });
    cout << "答え: " << result1 << " (検証: " << result1 * result1 << " >= 100)" << endl;
    cout << endl;

    // 例2: 実数の二分探索
    // 問題: sqrt(2)の値を求める（f(x) = x^2 - 2 = 0の解）
    cout << "例2: sqrt(2)の値" << endl;
    double result2 = binary_search_real(0, 2, [](double x) {
        return x * x <= 2.0;
    });
    cout << "答え: " << result2 << " (検証: " << result2 * result2 << " ≈ 2)" << endl;
    cout << endl;

    // 例3: 配列での二分探索
    cout << "例3: 配列での二分探索" << endl;
    vector<int> v = {1, 3, 3, 5, 7, 9, 11};
    cout << "配列: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    int target = 3;
    int lower = lower_bound_index(v, target);
    int upper = upper_bound_index(v, target);
    cout << target << "のlower_bound: index = " << lower << " (v[" << lower << "] = " << v[lower] << ")" << endl;
    cout << target << "のupper_bound: index = " << upper << " (v[" << upper << "] = " << v[upper] << ")" << endl;
    cout << endl;

    // 例4: 判定問題への応用
    // 問題: N個の品物を最大K個のグループに分けるとき、各グループの和の最大値を最小化
    cout << "例4: 配列分割問題" << endl;
    vector<int> items = {8, 1, 7, 3, 4, 6, 2, 5};
    int k = 3;

    auto can_divide = [&](long long max_sum) {
        int groups = 1;
        long long current_sum = 0;
        for (int item : items) {
            if (item > max_sum) return false;
            if (current_sum + item > max_sum) {
                groups++;
                current_sum = item;
            } else {
                current_sum += item;
            }
        }
        return groups <= k;
    };

    long long result4 = binary_search_int(100, 0, can_divide);
    cout << "品物: ";
    for (int x : items) cout << x << " ";
    cout << endl;
    cout << k << "グループに分けたときの最小の最大和: " << result4 << endl;

    return 0;
}