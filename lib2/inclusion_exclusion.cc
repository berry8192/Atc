// 包除原理 inclusion_exclusion ベン図的集合演算 O(2^N)

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <cmath>
using namespace std;

// ========== ライブラリ部分 ==========

// 基本的な包除原理
// sets: 各集合のサイズ
// intersections: 共通部分のサイズを返す関数（ビットマスクで指定）
long long inclusion_exclusion(const vector<long long>& sets, function<long long(int)> intersections) {
    int n = sets.size();
    long long result = 0;

    // 全ての部分集合について
    for (int mask = 1; mask < (1 << n); mask++) {
        int bits = __builtin_popcount(mask);
        long long intersection_size = intersections(mask);

        if (bits % 2 == 1) {
            result += intersection_size;
        } else {
            result -= intersection_size;
        }
    }

    return result;
}

// 素数を使った包除原理（約数問題）
// n以下で、divisorsのいずれかで割り切れる数の個数
long long count_divisible(long long n, const vector<long long>& divisors) {
    return inclusion_exclusion(divisors, [&](int mask) {
        long long lcm = 1;
        for (int i = 0; i < divisors.size(); i++) {
            if (mask & (1 << i)) {
                lcm = lcm / __gcd(lcm, divisors[i]) * divisors[i];
                if (lcm > n) return 0LL; // オーバーフロー対策
            }
        }
        return n / lcm;
    });
}

// 互いに素な数の個数（オイラーのφ関数の一般化）
long long count_coprime(long long n, const vector<long long>& primes) {
    return n - inclusion_exclusion(primes, [&](int mask) {
        long long product = 1;
        for (int i = 0; i < primes.size(); i++) {
            if (mask & (1 << i)) {
                product *= primes[i];
                if (product > n) return 0LL;
            }
        }
        return n / product;
    });
}

// 文字列の包除原理（部分文字列の出現）
// str内でpatternsのいずれかを含む位置の個数
int count_substring_positions(const string& str, const vector<string>& patterns) {
    int n = str.length();

    return inclusion_exclusion(patterns, [&](int mask) {
        vector<string> selected;
        for (int i = 0; i < patterns.size(); i++) {
            if (mask & (1 << i)) {
                selected.push_back(patterns[i]);
            }
        }

        int count = 0;
        for (int pos = 0; pos <= (int)str.length(); pos++) {
            bool all_match = true;
            for (const string& pattern : selected) {
                if (pos + pattern.length() > str.length() ||
                    str.substr(pos, pattern.length()) != pattern) {
                    all_match = false;
                    break;
                }
            }
            if (all_match) count++;
        }
        return (long long)count;
    });
}

// 完全順列（攪乱）の個数 - 包除原理の応用
long long count_derangements(int n) {
    vector<long long> factorial(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }

    long long result = 0;
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0) {
            result += factorial[n] / factorial[i];
        } else {
            result -= factorial[n] / factorial[i];
        }
    }
    return result;
}

// 集合の和集合のサイズ
template<typename T>
long long union_size(const vector<vector<T>>& sets) {
    int n = sets.size();

    return inclusion_exclusion(vector<long long>(n), [&](int mask) {
        unordered_set<T> intersection;
        bool first = true;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (first) {
                    for (const T& elem : sets[i]) {
                        intersection.insert(elem);
                    }
                    first = false;
                } else {
                    unordered_set<T> new_intersection;
                    for (const T& elem : sets[i]) {
                        if (intersection.count(elem)) {
                            new_intersection.insert(elem);
                        }
                    }
                    intersection = new_intersection;
                }
            }
        }

        return (long long)intersection.size();
    });
}

// モジュラー演算版包除原理
long long inclusion_exclusion_mod(const vector<long long>& sets,
                                 function<long long(int)> intersections,
                                 long long mod) {
    int n = sets.size();
    long long result = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        int bits = __builtin_popcount(mask);
        long long intersection_size = intersections(mask) % mod;

        if (bits % 2 == 1) {
            result = (result + intersection_size) % mod;
        } else {
            result = (result - intersection_size + mod) % mod;
        }
    }

    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な包除原理（倍数の個数）
    cout << "例1: 1000以下で2,3,5のいずれかで割り切れる数の個数" << endl;
    vector<long long> divisors = {2, 3, 5};
    long long count1 = count_divisible(1000, divisors);
    cout << "答え: " << count1 << endl;

    // 検証: 直接計算
    int direct_count = 0;
    for (int i = 1; i <= 1000; i++) {
        if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0) {
            direct_count++;
        }
    }
    cout << "検証: " << direct_count << endl;
    cout << endl;

    // 例2: 互いに素な数の個数
    cout << "例2: 100以下で2,3,5と互いに素な数の個数" << endl;
    vector<long long> primes = {2, 3, 5};
    long long count2 = count_coprime(100, primes);
    cout << "答え: " << count2 << endl;

    // 検証
    int coprime_count = 0;
    for (int i = 1; i <= 100; i++) {
        if (__gcd(i, 2) == 1 && __gcd(i, 3) == 1 && __gcd(i, 5) == 1) {
            coprime_count++;
        }
    }
    cout << "検証: " << coprime_count << endl;
    cout << endl;

    // 例3: 完全順列（攪乱）
    cout << "例3: 完全順列の個数" << endl;
    for (int n = 1; n <= 10; n++) {
        cout << "n=" << n << ": " << count_derangements(n) << endl;
    }
    cout << endl;

    // 例4: 集合の和集合
    cout << "例4: 集合の和集合" << endl;
    vector<vector<int>> sets = {
        {1, 2, 3, 4},
        {3, 4, 5, 6},
        {1, 5, 7, 8},
        {2, 6, 8, 9}
    };

    cout << "集合A: ";
    for (int x : sets[0]) cout << x << " ";
    cout << endl;
    cout << "集合B: ";
    for (int x : sets[1]) cout << x << " ";
    cout << endl;
    cout << "集合C: ";
    for (int x : sets[2]) cout << x << " ";
    cout << endl;
    cout << "集合D: ";
    for (int x : sets[3]) cout << x << " ";
    cout << endl;

    long long union_count = union_size(sets);
    cout << "和集合のサイズ: " << union_count << endl;
    cout << endl;

    // 例5: 文字列パターンマッチング
    cout << "例5: 文字列パターンマッチング" << endl;
    string text = "abcabcabc";
    vector<string> patterns = {"ab", "bc", "ca"};

    cout << "文字列: " << text << endl;
    cout << "パターン: ";
    for (const string& p : patterns) cout << p << " ";
    cout << endl;

    int match_count = count_substring_positions(text, patterns);
    cout << "パターンを含む位置の数: " << match_count << endl;
    cout << endl;

    // 例6: 複雑な例（条件を満たす順列）
    cout << "例6: 条件を満たす順列の数" << endl;
    // 1,2,3,4の順列で、1が1番目、2が2番目、3が3番目、4が4番目のいずれにもない順列
    int n = 4;
    long long forbidden_arrangements = 0;

    // 各位置に特定の数が来ることを禁止条件とする
    for (int mask = 1; mask < (1 << n); mask++) {
        int bits = __builtin_popcount(mask);
        long long arrangements = 1;
        for (int i = 0; i < n - bits; i++) {
            arrangements *= (i + 1);
        }

        if (bits % 2 == 1) {
            forbidden_arrangements += arrangements;
        } else {
            forbidden_arrangements -= arrangements;
        }
    }

    long long total_arrangements = 1;
    for (int i = 1; i <= n; i++) total_arrangements *= i;

    long long valid_arrangements = total_arrangements - forbidden_arrangements;
    cout << "全順列数: " << total_arrangements << endl;
    cout << "条件を満たす順列数: " << valid_arrangements << endl;
    cout << "完全順列の数: " << count_derangements(n) << endl;

    return 0;
}