// エラトステネスの篩 prime_sieve 素数列挙 O(N log log N)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========== ライブラリ本体 ==========

// エラトステネスの篩
// n以下の素数を全て列挙
vector<int> eratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// 素数判定テーブルも返す版
pair<vector<int>, vector<bool>> eratosthenes_with_table(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return {primes, is_prime};
}

// 線形篩（Linear Sieve）
// より高速なO(N)の篩
struct LinearSieve {
    int n;
    vector<int> spf;      // smallest prime factor
    vector<int> primes;

    LinearSieve(int n) : n(n), spf(n + 1) {
        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && primes[j] <= spf[i] && i * primes[j] <= n; j++) {
                spf[i * primes[j]] = primes[j];
            }
        }
    }

    bool is_prime(int x) {
        return x >= 2 && spf[x] == x;
    }

    // 素因数分解（O(log N)）
    vector<pair<int, int>> factorize(int x) {
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            res.push_back({p, cnt});
        }
        return res;
    }
};

// 区間篩（Segmented Sieve）
// [L, R]の範囲の素数を列挙（Rが大きい場合）
vector<long long> segmented_sieve(long long L, long long R) {
    // sqrt(R)までの素数を求める
    int limit = sqrt(R) + 1;
    vector<int> base_primes = eratosthenes(limit);

    vector<bool> is_prime(R - L + 1, true);
    if (L == 1) is_prime[0] = false;

    for (int p : base_primes) {
        long long start = max((long long)p * p, (L + p - 1) / p * p);
        for (long long j = start; j <= R; j += p) {
            is_prime[j - L] = false;
        }
    }

    vector<long long> primes;
    for (long long i = L; i <= R; i++) {
        if (is_prime[i - L]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// オイラーのφ関数の篩
// 1からnまでのφ(i)を計算
vector<int> euler_phi_sieve(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {  // iは素数
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }

    return phi;
}

// メビウス関数の篩
vector<int> mobius_sieve(int n) {
    vector<int> mu(n + 1, 1);
    vector<bool> is_prime(n + 1, true);

    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i; j <= n; j += i) {
                is_prime[j] = false;
                mu[j] *= -1;
            }
            long long sq = (long long)i * i;
            for (long long j = sq; j <= n; j += sq) {
                mu[j] = 0;
            }
        }
    }

    return mu;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なエラトステネスの篩
    cout << "例1: 100以下の素数" << endl;
    vector<int> primes = eratosthenes(100);
    cout << "素数の個数: " << primes.size() << endl;
    cout << "素数: ";
    for (int i = 0; i < min(20, (int)primes.size()); i++) {
        cout << primes[i] << " ";
    }
    cout << "..." << endl << endl;

    // 例2: 素数判定テーブル
    cout << "例2: 素数判定" << endl;
    auto [primes2, is_prime] = eratosthenes_with_table(30);
    for (int i = 1; i <= 30; i++) {
        if (is_prime[i]) {
            cout << i << " ";
        }
    }
    cout << endl << endl;

    // 例3: 線形篩と素因数分解
    cout << "例3: 線形篩による素因数分解" << endl;
    LinearSieve ls(100);
    int n = 60;
    auto factors = ls.factorize(n);
    cout << n << " = ";
    for (int i = 0; i < factors.size(); i++) {
        if (i > 0) cout << " × ";
        cout << factors[i].first;
        if (factors[i].second > 1) {
            cout << "^" << factors[i].second;
        }
    }
    cout << endl << endl;

    // 例4: 区間篩
    cout << "例4: 区間篩 [1000000, 1000100]" << endl;
    vector<long long> seg_primes = segmented_sieve(1000000, 1000100);
    cout << "この区間の素数: ";
    for (long long p : seg_primes) {
        cout << p << " ";
    }
    cout << endl << endl;

    // 例5: オイラー関数
    cout << "例5: オイラー関数 φ(n)" << endl;
    vector<int> phi = euler_phi_sieve(20);
    for (int i = 1; i <= 20; i++) {
        cout << "φ(" << i << ") = " << phi[i] << endl;
    }

    return 0;
}