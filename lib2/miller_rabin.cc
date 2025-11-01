// ミラーラビン素数判定 miller_rabin 確率的素数判定 O(k log^3 N)

#include <iostream>
#include <vector>
#include <random>
using namespace std;

// ========== ライブラリ本体 ==========

// 累乗のmod計算（オーバーフロー対策）
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1) {
            res = (__int128)res * base % mod;
        }
        base = (__int128)base * base % mod;
        exp >>= 1;
    }

    return res;
}

// ミラーラビン素数判定
// 確率的アルゴリズム（決定的版）
bool miller_rabin(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    // n-1 = 2^r * d を計算
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // 決定的版のwitnesses
    // 2^64までの全ての数に対して正しく判定
    vector<long long> witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (long long a : witnesses) {
        if (a >= n) break;

        long long x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = (__int128)x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        if (composite) return false;
    }

    return true;
}

// 32bit整数用の高速版
bool is_prime_32(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // 2^32までは以下のwitnessで十分
    vector<long long> witnesses = {2, 7, 61};

    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    for (long long a : witnesses) {
        if (a >= n) continue;

        long long x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = x * x % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        if (composite) return false;
    }

    return true;
}

// 素数判定（試し割り + ミラーラビン）
// 小さい数は試し割り、大きい数はミラーラビン
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // 小さい素数で試し割り
    vector<int> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for (int p : small_primes) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }

    // ミラーラビン判定
    return miller_rabin(n);
}

// 次の素数を見つける
long long next_prime(long long n) {
    if (n <= 2) return 2;
    if (n % 2 == 0) n++;
    else n += 2;

    while (!is_prime(n)) {
        n += 2;
    }

    return n;
}

// 前の素数を見つける
long long prev_prime(long long n) {
    if (n <= 2) return -1;
    if (n == 3) return 2;

    if (n % 2 == 0) n--;
    else n -= 2;

    while (n > 2 && !is_prime(n)) {
        n -= 2;
    }

    return n;
}

// n番目の素数の近似値（素数定理）
long long nth_prime_approx(long long n) {
    if (n == 1) return 2;

    double ln_n = log(n);
    double ln_ln_n = log(ln_n);

    // より精密な近似式
    double approx = n * (ln_n + ln_ln_n - 1.0 +
                         (ln_ln_n - 2.0) / ln_n -
                         ((ln_ln_n * ln_ln_n - 6.0 * ln_ln_n + 11.0) / (2.0 * ln_n * ln_n)));

    return (long long)approx;
}

// 素数ギャップを調べる
pair<long long, long long> prime_gap(long long n) {
    long long p1 = n;
    while (!is_prime(p1)) p1--;

    long long p2 = n;
    while (!is_prime(p2)) p2++;

    return {p1, p2};
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な素数判定
    cout << "例1: ミラーラビン素数判定" << endl;
    vector<long long> test_nums = {2, 17, 100, 997, 1000000007, 1000000009,
                                   998244353, 1000000000039LL};

    for (long long n : test_nums) {
        cout << n << " は" << (miller_rabin(n) ? "素数" : "合成数") << endl;
    }
    cout << endl;

    // 例2: 大きな数の素数判定
    cout << "例2: 大きな数の素数判定" << endl;
    long long large = 1000000000000000003LL;
    cout << large << " は" << (is_prime(large) ? "素数" : "合成数") << endl;
    cout << endl;

    // 例3: 次の素数・前の素数
    cout << "例3: 次の素数・前の素数" << endl;
    long long n = 100;
    cout << n << " の次の素数: " << next_prime(n) << endl;
    cout << n << " の前の素数: " << prev_prime(n) << endl;
    cout << endl;

    // 例4: 素数ギャップ
    cout << "例4: 素数ギャップ" << endl;
    n = 1000;
    auto [p1, p2] = prime_gap(n);
    cout << n << " を挟む素数: " << p1 << " と " << p2 << endl;
    cout << "ギャップ: " << p2 - p1 << endl;
    cout << endl;

    // 例5: n番目の素数の近似
    cout << "例5: n番目の素数の近似" << endl;
    vector<int> indices = {10, 100, 1000, 10000};
    for (int idx : indices) {
        cout << idx << "番目の素数の近似値: " << nth_prime_approx(idx) << endl;
    }

    return 0;
}