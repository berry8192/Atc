// 素数ユーティリティ prime_utilities 素数関連の便利関数

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

// ========== ライブラリ本体 ==========

// 最大公約数（ユークリッド互除法）
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 最小公倍数
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

// 拡張ユークリッド互除法
// ax + by = gcd(a, b) の解を求める
pair<long long, long long> extgcd(long long a, long long b) {
    if (b == 0) return {1, 0};

    auto [x, y] = extgcd(b, a % b);
    return {y, x - a / b * y};
}

// 中国剰余定理
// x ≡ r1 (mod m1), x ≡ r2 (mod m2) の解
// 返り値: {解x, 周期lcm(m1, m2)}、解なしの場合{0, -1}
pair<long long, long long> chinese_remainder(long long r1, long long m1, long long r2, long long m2) {
    auto [p, q] = extgcd(m1, m2);
    long long g = gcd(m1, m2);

    if ((r2 - r1) % g != 0) return {0, -1};

    long long m = m1 / g * m2;
    long long t = ((r2 - r1) / g * p % (m2 / g) + m2 / g) % (m2 / g);
    long long r = (r1 + m1 * t) % m;
    if (r < 0) r += m;

    return {r, m};
}

// 複数の中国剰余定理
// x ≡ r[i] (mod m[i]) の解
pair<long long, long long> chinese_remainder_vector(vector<long long> r, vector<long long> m) {
    long long r0 = 0, m0 = 1;

    for (int i = 0; i < r.size(); i++) {
        auto [r1, m1] = chinese_remainder(r0, m0, r[i], m[i]);
        if (m1 == -1) return {0, -1};
        r0 = r1;
        m0 = m1;
    }

    return {r0, m0};
}

// モジュラー逆元（拡張ユークリッド互除法）
// a * x ≡ 1 (mod m)
long long mod_inverse(long long a, long long m) {
    auto [x, y] = extgcd(a, m);
    if (gcd(a, m) != 1) return -1;

    x %= m;
    if (x < 0) x += m;
    return x;
}

// ウィルソンの定理
// (p-1)! ≡ -1 (mod p) if p is prime
bool wilson_test(long long p) {
    if (p <= 1) return false;
    if (p == 2) return true;

    long long fact = 1;
    for (long long i = 2; i < p; i++) {
        fact = fact * i % p;
    }

    return fact == p - 1;
}

// フェルマーの小定理によるテスト
// a^(p-1) ≡ 1 (mod p) if p is prime and gcd(a,p) = 1
bool fermat_test(long long p, long long a = 2) {
    if (p <= 1) return false;
    if (p == 2) return true;
    if (gcd(a, p) != 1) return false;

    long long result = 1;
    long long base = a % p;
    long long exp = p - 1;

    while (exp > 0) {
        if (exp & 1) {
            result = (__int128)result * base % p;
        }
        base = (__int128)base * base % p;
        exp >>= 1;
    }

    return result == 1;
}

// カーマイケル関数 λ(n)
// a^λ(n) ≡ 1 (mod n) for all a with gcd(a,n) = 1
long long carmichael_lambda(long long n) {
    if (n == 1) return 1;

    // 素因数分解
    vector<pair<long long, int>> factors;
    long long temp = n;

    for (long long i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            int cnt = 0;
            while (temp % i == 0) {
                temp /= i;
                cnt++;
            }
            factors.push_back({i, cnt});
        }
    }
    if (temp > 1) {
        factors.push_back({temp, 1});
    }

    long long result = 1;

    for (auto [p, e] : factors) {
        long long lambda_pe;

        if (p == 2) {
            if (e == 1) lambda_pe = 1;
            else if (e == 2) lambda_pe = 2;
            else lambda_pe = (1LL << (e - 2));
        } else {
            lambda_pe = 1;
            for (int i = 0; i < e - 1; i++) lambda_pe *= p;
            lambda_pe *= (p - 1);
        }

        result = lcm(result, lambda_pe);
    }

    return result;
}

// 原始根を求める
// gが法pの原始根 ⟺ ord_p(g) = φ(p)
long long primitive_root(long long p) {
    if (p == 2) return 1;

    // p-1の約数を求める
    vector<long long> divs;
    long long phi = p - 1;

    for (long long i = 2; i * i <= phi; i++) {
        if (phi % i == 0) {
            divs.push_back(i);
            if (i != phi / i) {
                divs.push_back(phi / i);
            }
        }
    }

    // 最小の原始根を探す
    for (long long g = 2; g < p; g++) {
        bool is_root = true;

        for (long long d : divs) {
            long long result = 1;
            long long base = g;
            long long exp = d;

            while (exp > 0) {
                if (exp & 1) {
                    result = result * base % p;
                }
                base = base * base % p;
                exp >>= 1;
            }

            if (result == 1) {
                is_root = false;
                break;
            }
        }

        if (is_root) return g;
    }

    return -1;
}

// 離散対数問題（Baby-step Giant-step）
// g^x ≡ a (mod p) を満たすxを求める
long long discrete_log(long long g, long long a, long long p) {
    long long m = ceil(sqrt(p));

    // Baby step: g^j for j = 0, 1, ..., m-1
    map<long long, long long> baby;
    long long g_j = 1;

    for (long long j = 0; j < m; j++) {
        baby[g_j] = j;
        g_j = g_j * g % p;
    }

    // Giant step: a * (g^{-m})^i for i = 0, 1, ..., m-1
    long long g_m_inv = mod_inverse(g_j, p);
    long long gamma = a;

    for (long long i = 0; i < m; i++) {
        if (baby.count(gamma)) {
            return i * m + baby[gamma];
        }
        gamma = gamma * g_m_inv % p;
    }

    return -1;  // 解なし
}

// ========== サンプルコード ==========

int main() {
    // 例1: GCDとLCM
    cout << "例1: GCDとLCM" << endl;
    cout << "gcd(48, 18) = " << gcd(48, 18) << endl;
    cout << "lcm(48, 18) = " << lcm(48, 18) << endl;
    cout << endl;

    // 例2: 拡張ユークリッド互除法
    cout << "例2: 拡張ユークリッド互除法" << endl;
    auto [x, y] = extgcd(30, 18);
    cout << "30x + 18y = gcd(30, 18) = 6" << endl;
    cout << "解: x = " << x << ", y = " << y << endl;
    cout << "検証: 30*" << x << " + 18*" << y << " = " << 30 * x + 18 * y << endl;
    cout << endl;

    // 例3: 中国剰余定理
    cout << "例3: 中国剰余定理" << endl;
    auto [sol, period] = chinese_remainder(2, 3, 3, 5);
    cout << "x ≡ 2 (mod 3), x ≡ 3 (mod 5)" << endl;
    cout << "解: x ≡ " << sol << " (mod " << period << ")" << endl;
    cout << endl;

    // 例4: モジュラー逆元
    cout << "例4: モジュラー逆元" << endl;
    long long inv = mod_inverse(3, 11);
    cout << "3の逆元 (mod 11) = " << inv << endl;
    cout << "検証: 3 * " << inv << " ≡ " << 3 * inv % 11 << " (mod 11)" << endl;
    cout << endl;

    // 例5: 原始根
    cout << "例5: 原始根" << endl;
    long long p = 13;
    long long g = primitive_root(p);
    cout << p << " の原始根: " << g << endl;

    // 検証
    cout << "検証: ";
    for (int i = 1; i < p; i++) {
        long long pow_g = 1;
        for (int j = 0; j < i; j++) {
            pow_g = pow_g * g % p;
        }
        cout << pow_g << " ";
    }
    cout << endl;

    return 0;
}