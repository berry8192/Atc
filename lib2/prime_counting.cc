// 素数計数関数 prime_counting π(n) メルテンス関数

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

// ========== ライブラリ本体 ==========

// 素数計数関数 π(n): n以下の素数の個数
// 単純な実装 O(N log log N)
long long prime_count_simple(long long n) {
    if (n < 2) return 0;

    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (long long i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    long long count = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) count++;
    }

    return count;
}

// Lucyの素数計数アルゴリズム
// O(N^(2/3))
class PrimeCounter {
private:
    long long n;
    int sqrt_n;
    vector<long long> lo, hi;

    long long count(long long x) {
        if (x <= sqrt_n) return lo[x];
        else return hi[n / x];
    }

public:
    PrimeCounter(long long n) : n(n), sqrt_n(sqrt(n) + 1) {
        lo.resize(sqrt_n + 1);
        hi.resize(sqrt_n + 1);

        // 初期化: count[i] = i - 1
        for (int i = 1; i <= sqrt_n; i++) {
            lo[i] = i - 1;
            hi[i] = n / i - 1;
        }

        // 篩
        for (int p = 2; p <= sqrt_n; p++) {
            if (lo[p] == lo[p - 1]) continue;  // pは素数でない

            long long p2 = (long long)p * p;
            long long cnt_p = lo[p - 1];

            // loの更新
            for (int i = sqrt_n; i >= p2; i--) {
                lo[i] -= count(i / p) - cnt_p;
            }

            // hiの更新
            for (int i = 1; i <= sqrt_n && p2 * i <= n; i++) {
                hi[i] -= count(n / i / p) - cnt_p;
            }
        }
    }

    long long get() {
        return hi[1];
    }
};

// Legendreの公式による素数計数
// φ(n, a) = n以下でa番目までの素数で割り切れない数の個数
long long legendre_pi(long long n) {
    if (n < 2) return 0;

    int sqrt_n = sqrt(n);
    vector<bool> is_prime(sqrt_n + 1, true);
    vector<int> primes;

    for (int i = 2; i <= sqrt_n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= sqrt_n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // φ関数のメモ化
    map<pair<long long, int>, long long> memo;

    function<long long(long long, int)> phi = [&](long long x, int a) -> long long {
        if (a == 0) return x;
        if (x == 0) return 0;

        auto key = make_pair(x, a);
        if (memo.count(key)) return memo[key];

        return memo[key] = phi(x, a - 1) - phi(x / primes[a - 1], a - 1);
    };

    int a = upper_bound(primes.begin(), primes.end(), sqrt_n) - primes.begin();
    return phi(n, a) + a - 1;
}

// メルテンス関数 M(n) = Σ_{i=1}^{n} μ(i)
// μはメビウス関数
vector<long long> mertens_function(int n) {
    vector<int> mu(n + 1, 1);
    vector<bool> is_prime(n + 1, true);

    // メビウス関数を計算
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= n; j += i) {
                is_prime[j] = false;
                mu[j] *= -1;
            }
            long long sq = (long long)i * i;
            if (sq <= n) {
                for (long long j = sq; j <= n; j += sq) {
                    mu[j] = 0;
                }
            }
        }
    }

    // メルテンス関数（累積和）
    vector<long long> M(n + 1);
    for (int i = 1; i <= n; i++) {
        M[i] = M[i - 1] + mu[i];
    }

    return M;
}

// リーマンゼータ関数による素数計数の近似
// Li(x) = 対数積分
double logarithmic_integral(double x) {
    if (x <= 0) return 0;
    if (x < 2) return 0;

    double sum = 0;
    double t = log(x);

    // 数値積分（簡易版）
    int steps = 10000;
    double dt = (t - log(2)) / steps;

    for (int i = 0; i < steps; i++) {
        double ti = log(2) + i * dt;
        sum += 1.0 / ti;
    }

    return sum * dt;
}

// 素数定理による近似
double prime_count_approx(long long n) {
    if (n < 2) return 0;
    return n / log(n);
}

// より精密な近似（Riemann's formula）
double prime_count_riemann(long long n) {
    if (n < 2) return 0;

    double ln_n = log(n);
    double result = logarithmic_integral(n);

    // 補正項を追加
    result -= 0.5 * logarithmic_integral(sqrt(n));
    result -= (1.0 / 3.0) * logarithmic_integral(pow(n, 1.0 / 3.0));

    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 単純な素数計数
    cout << "例1: 素数計数関数 π(n)" << endl;
    vector<int> test = {10, 100, 1000, 10000};
    for (int n : test) {
        cout << "π(" << n << ") = " << prime_count_simple(n) << endl;
    }
    cout << endl;

    // 例2: 高速な素数計数
    cout << "例2: Lucy法による素数計数" << endl;
    long long n = 1000000;
    PrimeCounter pc(n);
    cout << "π(" << n << ") = " << pc.get() << endl;
    cout << endl;

    // 例3: メルテンス関数
    cout << "例3: メルテンス関数" << endl;
    vector<long long> M = mertens_function(30);
    for (int i = 1; i <= 20; i++) {
        cout << "M(" << i << ") = " << M[i] << endl;
    }
    cout << endl;

    // 例4: 素数計数の近似
    cout << "例4: 素数計数の近似" << endl;
    n = 1000000;
    long long exact = pc.get();
    double approx1 = prime_count_approx(n);
    double approx2 = logarithmic_integral(n);

    cout << "n = " << n << endl;
    cout << "正確な値: " << exact << endl;
    cout << "n/ln(n): " << (long long)approx1 << " (誤差: "
         << abs(exact - approx1) / exact * 100 << "%)" << endl;
    cout << "Li(n): " << (long long)approx2 << " (誤差: "
         << abs(exact - approx2) / exact * 100 << "%)" << endl;

    return 0;
}