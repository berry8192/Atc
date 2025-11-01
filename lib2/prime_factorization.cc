// 素因数分解 prime_factorization 約数列挙 O(√N)

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// ========== ライブラリ本体 ==========

// 素因数分解（試し割り法）
// O(√N)
vector<pair<long long, int>> prime_factorize(long long n) {
    vector<pair<long long, int>> res;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            res.push_back({i, cnt});
        }
    }

    if (n > 1) {
        res.push_back({n, 1});
    }

    return res;
}

// 素因数分解（map版）
map<long long, int> prime_factorize_map(long long n) {
    map<long long, int> res;

    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            res[i]++;
            n /= i;
        }
    }

    if (n > 1) {
        res[n]++;
    }

    return res;
}

// 約数列挙
// O(√N)
vector<long long> divisors(long long n) {
    vector<long long> res;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i * i != n) {
                res.push_back(n / i);
            }
        }
    }

    sort(res.begin(), res.end());
    return res;
}

// 約数の個数を求める
// 素因数分解の結果から計算
long long count_divisors(long long n) {
    auto factors = prime_factorize(n);
    long long res = 1;

    for (auto [p, e] : factors) {
        res *= (e + 1);
    }

    return res;
}

// 約数の和を求める
// 素因数分解の結果から計算
long long sum_divisors(long long n) {
    auto factors = prime_factorize(n);
    long long res = 1;

    for (auto [p, e] : factors) {
        long long sum = 0;
        long long pow_p = 1;
        for (int i = 0; i <= e; i++) {
            sum += pow_p;
            pow_p *= p;
        }
        res *= sum;
    }

    return res;
}

// オイラー関数 φ(n)
// nと互いに素な1以上n以下の整数の個数
long long euler_phi(long long n) {
    long long res = n;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1) {
        res = res / n * (n - 1);
    }

    return res;
}

// 素因数の種類数
int count_prime_factors(long long n) {
    int res = 0;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res++;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1) {
        res++;
    }

    return res;
}

// 最小素因数
long long smallest_prime_factor(long long n) {
    if (n <= 1) return -1;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return i;
        }
    }

    return n;
}

// 最大素因数
long long largest_prime_factor(long long n) {
    long long res = -1;

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1) {
        res = n;
    }

    return res;
}

// ポラード・ロー法による素因数分解（大きい数用）
long long pollard_rho(long long n) {
    if (n % 2 == 0) return 2;
    if (n == 1) return 1;

    long long x = 2, y = 2, d = 1;
    auto f = [&](long long x) { return (x * x + 1) % n; };

    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = __gcd(abs(x - y), n);
    }

    return d == n ? 1 : d;
}

// 完全数判定
bool is_perfect(long long n) {
    return sum_divisors(n) == 2 * n;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な素因数分解
    cout << "例1: 素因数分解" << endl;
    long long n = 360;
    auto factors = prime_factorize(n);
    cout << n << " = ";
    for (int i = 0; i < factors.size(); i++) {
        if (i > 0) cout << " × ";
        cout << factors[i].first;
        if (factors[i].second > 1) {
            cout << "^" << factors[i].second;
        }
    }
    cout << endl << endl;

    // 例2: 約数列挙
    cout << "例2: 約数列挙" << endl;
    n = 24;
    vector<long long> divs = divisors(n);
    cout << n << " の約数: ";
    for (long long d : divs) {
        cout << d << " ";
    }
    cout << endl;
    cout << "約数の個数: " << count_divisors(n) << endl;
    cout << "約数の和: " << sum_divisors(n) << endl;
    cout << endl;

    // 例3: オイラー関数
    cout << "例3: オイラー関数" << endl;
    for (int i = 1; i <= 12; i++) {
        cout << "φ(" << i << ") = " << euler_phi(i) << endl;
    }
    cout << endl;

    // 例4: 素因数の情報
    cout << "例4: 素因数の情報" << endl;
    n = 420;
    cout << n << " の最小素因数: " << smallest_prime_factor(n) << endl;
    cout << n << " の最大素因数: " << largest_prime_factor(n) << endl;
    cout << n << " の素因数の種類数: " << count_prime_factors(n) << endl;
    cout << endl;

    // 例5: 完全数判定
    cout << "例5: 完全数判定" << endl;
    vector<int> test = {6, 28, 120, 496};
    for (int x : test) {
        cout << x << " は完全数" << (is_perfect(x) ? "です" : "ではありません") << endl;
    }

    return 0;
}