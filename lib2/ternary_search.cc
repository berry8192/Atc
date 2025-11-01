// 三分探索 ternary_search 凸関数 O(log N)

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>
using namespace std;

// ========== ライブラリ部分 ==========

// 実数版三分探索（凸関数の最大値を求める）
// l: 左端, r: 右端
// f: 評価関数（最大化したい関数）
// eps: 精度（デフォルト1e-9）
// iterations: 反復回数（デフォルト200）
double ternary_search_max_real(double l, double r, function<double(double)> f,
                               double eps = 1e-9, int iterations = 200) {
    for (int i = 0; i < iterations && r - l > eps; i++) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;

        if (f(m1) < f(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    return (l + r) / 2.0;
}

// 実数版三分探索（凹関数の最小値を求める）
// l: 左端, r: 右端
// f: 評価関数（最小化したい関数）
// eps: 精度（デフォルト1e-9）
// iterations: 反復回数（デフォルト200）
double ternary_search_min_real(double l, double r, function<double(double)> f,
                               double eps = 1e-9, int iterations = 200) {
    for (int i = 0; i < iterations && r - l > eps; i++) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;

        if (f(m1) > f(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    return (l + r) / 2.0;
}

// 整数版三分探索（離散的な凸関数の最大値を求める）
// l: 左端, r: 右端
// f: 評価関数（最大化したい関数）
long long ternary_search_max_int(long long l, long long r, function<long long(long long)> f) {
    while (r - l > 2) {
        long long m1 = l + (r - l) / 3;
        long long m2 = r - (r - l) / 3;

        if (f(m1) < f(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }

    long long res = l;
    long long max_val = f(l);
    for (long long i = l + 1; i <= r; i++) {
        if (f(i) > max_val) {
            max_val = f(i);
            res = i;
        }
    }
    return res;
}

// 整数版三分探索（離散的な凹関数の最小値を求める）
// l: 左端, r: 右端
// f: 評価関数（最小化したい関数）
long long ternary_search_min_int(long long l, long long r, function<long long(long long)> f) {
    while (r - l > 2) {
        long long m1 = l + (r - l) / 3;
        long long m2 = r - (r - l) / 3;

        if (f(m1) > f(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }

    long long res = l;
    long long min_val = f(l);
    for (long long i = l + 1; i <= r; i++) {
        if (f(i) < min_val) {
            min_val = f(i);
            res = i;
        }
    }
    return res;
}

// 黄金分割探索（より効率的な三分探索）
// l: 左端, r: 右端
// f: 評価関数（最小化したい関数）
// eps: 精度
double golden_section_search(double l, double r, function<double(double)> f, double eps = 1e-9) {
    const double phi = (1.0 + sqrt(5.0)) / 2.0;  // 黄金比
    const double resphi = 2.0 - phi;

    double tol = eps;
    double a = l, b = r;
    double x1 = a + resphi * (b - a);
    double x2 = b - resphi * (b - a);
    double f1 = f(x1);
    double f2 = f(x2);

    while (abs(b - a) > tol) {
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = a + resphi * (b - a);
            f1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = b - resphi * (b - a);
            f2 = f(x2);
        }
    }

    return (a + b) / 2.0;
}

// ========== サンプルコード ==========

int main() {
    cout << fixed << setprecision(6);

    // 例1: 二次関数の最小値
    // f(x) = (x-3)^2 + 2 の最小値を求める
    cout << "例1: f(x) = (x-3)^2 + 2 の最小値" << endl;
    auto f1 = [](double x) { return (x - 3) * (x - 3) + 2; };
    double min_x1 = ternary_search_min_real(-10, 10, f1);
    cout << "最小値をとるx: " << min_x1 << endl;
    cout << "最小値: " << f1(min_x1) << endl;
    cout << endl;

    // 例2: 二次関数の最大値
    // f(x) = -x^2 + 4x - 1 の最大値を求める
    cout << "例2: f(x) = -x^2 + 4x - 1 の最大値" << endl;
    auto f2 = [](double x) { return -x * x + 4 * x - 1; };
    double max_x2 = ternary_search_max_real(-10, 10, f2);
    cout << "最大値をとるx: " << max_x2 << endl;
    cout << "最大値: " << f2(max_x2) << endl;
    cout << endl;

    // 例3: 整数版三分探索
    // 離散的な関数の最大値
    cout << "例3: 整数版三分探索" << endl;
    auto f3 = [](long long x) {
        // 100 - |x - 50| のような山型の関数
        return 100 - abs(x - 50);
    };
    long long max_x3 = ternary_search_max_int(0, 100, f3);
    cout << "最大値をとるx: " << max_x3 << endl;
    cout << "最大値: " << f3(max_x3) << endl;
    cout << endl;

    // 例4: 幾何問題への応用
    // 点(0, 0)と点(10, 0)からの距離の和が最小となる直線y=1上の点を求める
    cout << "例4: 幾何問題 - 2点からの距離の和の最小化" << endl;
    auto distance_sum = [](double x) {
        double d1 = sqrt(x * x + 1);           // (0,0)からの距離
        double d2 = sqrt((10 - x) * (10 - x) + 1); // (10,0)からの距離
        return d1 + d2;
    };
    double min_x4 = ternary_search_min_real(0, 10, distance_sum);
    cout << "最小距離をとる点: (" << min_x4 << ", 1)" << endl;
    cout << "最小距離の和: " << distance_sum(min_x4) << endl;
    cout << endl;

    // 例5: 黄金分割探索
    cout << "例5: 黄金分割探索による最適化" << endl;
    auto f5 = [](double x) {
        return sin(x) + sin(2 * x) + sin(3 * x);
    };
    double min_x5 = golden_section_search(0, 2 * M_PI, [&](double x) { return -f5(x); });
    cout << "f(x) = sin(x) + sin(2x) + sin(3x) の最大値をとるx: " << min_x5 << endl;
    cout << "最大値: " << f5(min_x5) << endl;
    cout << endl;

    // 例6: 実用的な問題 - 利益最大化
    // 価格xで商品を売るとき、売上個数は(100-x)個、利益は x*(100-x) - 10*x
    cout << "例6: 利益最大化問題" << endl;
    auto profit = [](double x) {
        if (x < 0 || x > 100) return -1e18;  // 範囲外は負の無限大
        return x * (100 - x) - 10 * x;  // 利益 = 売上 - コスト
    };
    double best_price = ternary_search_max_real(0, 100, profit);
    cout << "最適価格: " << best_price << "円" << endl;
    cout << "最大利益: " << profit(best_price) << "円" << endl;

    return 0;
}