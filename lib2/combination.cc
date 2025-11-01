// Combination 組み合わせ 二項係数 nCr Pascal階乗 O(N) 前計算

#include <iostream>
#include <vector>
using namespace std;

// ========== ライブラリ部分 ==========

// 組み合わせライブラリ（modありver）
template<int MOD>
class Combination {
private:
    vector<long long> fact, inv_fact;
    int max_n;

    // 高速べき乗
    long long power(long long base, long long exp, long long mod) {
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

    // 逆元を求める（MODが素数の場合）
    long long mod_inverse(long long a) {
        return power(a, MOD - 2, MOD);
    }

public:
    // コンストラクタ（max_nまでの階乗を前計算）
    Combination(int n) : max_n(n) {
        fact.resize(n + 1);
        inv_fact.resize(n + 1);

        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        inv_fact[n] = mod_inverse(fact[n]);
        for (int i = n - 1; i >= 0; i--) {
            inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
        }
    }

    // nCr を計算
    long long C(int n, int r) {
        if (r < 0 || r > n || n > max_n) return 0;
        return (fact[n] * inv_fact[r] % MOD) * inv_fact[n - r] % MOD;
    }

    // nPr を計算
    long long P(int n, int r) {
        if (r < 0 || r > n || n > max_n) return 0;
        return fact[n] * inv_fact[n - r] % MOD;
    }

    // n! を計算
    long long factorial(int n) {
        if (n < 0 || n > max_n) return 0;
        return fact[n];
    }

    // 重複組み合わせ H(n,r) = C(n+r-1, r)
    long long H(int n, int r) {
        return C(n + r - 1, r);
    }

    // カタラン数 C_n = C(2n, n) / (n+1)
    long long catalan(int n) {
        if (n < 0) return 0;
        return C(2 * n, n) * mod_inverse(n + 1) % MOD;
    }

    // スターリング数第2種（近似，実装が複雑なため基本版のみ）
    long long stirling2(int n, int k) {
        if (k > n || k <= 0) return 0;
        if (k == 1 || k == n) return 1;

        // 小さな値のみ動的計算
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                dp[i][j] = (j * dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
        return dp[n][k];
    }
};

// modなしversion（オーバーフローに注意）
class CombinationLarge {
private:
    vector<vector<long long>> pascal;
    int max_n;

public:
    CombinationLarge(int n) : max_n(n) {
        pascal.assign(n + 1, vector<long long>(n + 1, 0));

        // パスカルの三角形
        for (int i = 0; i <= n; i++) {
            pascal[i][0] = pascal[i][i] = 1;
            for (int j = 1; j < i; j++) {
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
        }
    }

    long long C(int n, int r) {
        if (r < 0 || r > n || n > max_n) return 0;
        return pascal[n][r];
    }

    // 直接計算（大きな値用）
    static long long C_direct(long long n, long long r) {
        if (r > n - r) r = n - r;  // C(n,r) = C(n,n-r)
        if (r == 0) return 1;

        long long result = 1;
        for (long long i = 0; i < r; i++) {
            result = result * (n - i) / (i + 1);
        }
        return result;
    }

    // Lucas定理（modが素数の場合のC(n,r) mod p）
    static long long lucas(long long n, long long r, long long p) {
        if (r == 0) return 1;
        return C_direct(n % p, r % p) * lucas(n / p, r / p, p) % p;
    }
};

// 小さなmodに対するライブラリ
class SmallModCombination {
private:
    int mod;
    vector<long long> fact, inv_fact;

public:
    SmallModCombination(int n, int m) : mod(m) {
        fact.resize(n + 1);
        inv_fact.resize(n + 1);

        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }

        // 逆元の計算（拡張ユークリッド法）
        auto extended_gcd = [](long long a, long long b, long long& x, long long& y) {
            if (b == 0) {
                x = 1; y = 0;
                return a;
            }
            long long x1, y1;
            long long gcd = extended_gcd(b, a % b, x1, y1);
            x = y1;
            y = x1 - (a / b) * y1;
            return gcd;
        };

        for (int i = 0; i <= n; i++) {
            long long x, y;
            extended_gcd(fact[i], mod, x, y);
            inv_fact[i] = (x % mod + mod) % mod;
        }
    }

    long long C(int n, int r) {
        if (r < 0 || r > n) return 0;
        return (fact[n] * inv_fact[r] % mod) * inv_fact[n - r] % mod;
    }
};

// ========== サンプルコード ==========

int main() {
    const int MOD = 1000000007;

    // 例1: 基本的な組み合わせ計算
    cout << "例1: 基本的な組み合わせ計算" << endl;
    Combination<MOD> comb(1000);

    vector<pair<int, int>> test_cases = {{5, 2}, {10, 3}, {20, 10}, {100, 50}};

    for (auto [n, r] : test_cases) {
        cout << "C(" << n << ", " << r << ") = " << comb.C(n, r) << endl;
        cout << "P(" << n << ", " << r << ") = " << comb.P(n, r) << endl;
        cout << "H(" << n << ", " << r << ") = " << comb.H(n, r) << endl;
        cout << endl;
    }

    // 例2: パスカルの三角形
    cout << "例2: パスカルの三角形（小さな値）" << endl;
    CombinationLarge comb_large(10);

    for (int n = 0; n <= 6; n++) {
        for (int r = 0; r <= n; r++) {
            cout << comb_large.C(n, r) << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 例3: カタラン数
    cout << "例3: カタラン数" << endl;
    cout << "カタラン数列: ";
    for (int i = 0; i <= 10; i++) {
        cout << comb.catalan(i) << " ";
    }
    cout << endl << endl;

    // 例4: 階乗
    cout << "例4: 階乗" << endl;
    cout << "階乗: ";
    for (int i = 0; i <= 10; i++) {
        cout << i << "! = " << comb.factorial(i) << ", ";
    }
    cout << endl << endl;

    // 例5: スターリング数第2種
    cout << "例5: スターリング数第2種 S(n,k)" << endl;
    for (int n = 1; n <= 6; n++) {
        cout << "S(" << n << ",k): ";
        for (int k = 1; k <= n; k++) {
            cout << comb.stirling2(n, k) << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 例6: 大きな値での直接計算
    cout << "例6: 大きな値での直接計算" << endl;
    vector<pair<long long, long long>> large_cases = {{50, 25}, {30, 15}, {40, 20}};

    for (auto [n, r] : large_cases) {
        long long result = CombinationLarge::C_direct(n, r);
        cout << "C(" << n << ", " << r << ") = " << result << endl;
    }
    cout << endl;

    // 例7: 実用例 - 格子経路問題
    cout << "例7: 格子経路問題" << endl;
    // (0,0)から(m,n)への最短経路の数
    vector<tuple<int, int, string>> path_problems = {
        {3, 3, "(0,0)から(3,3)への経路数"},
        {5, 2, "(0,0)から(5,2)への経路数"},
        {10, 4, "(0,0)から(10,4)への経路数"}
    };

    for (auto [m, n, desc] : path_problems) {
        long long paths = comb.C(m + n, m);
        cout << desc << ": " << paths << endl;
    }
    cout << endl;

    // 例8: 重複組み合わせの応用
    cout << "例8: 重複組み合わせの応用" << endl;
    // n種類の品物からr個選ぶ（重複あり）
    vector<tuple<int, int, string>> duplicate_problems = {
        {3, 5, "3種類の品物から5個選ぶ"},
        {4, 3, "4種類の品物から3個選ぶ"},
        {5, 7, "5種類の品物から7個選ぶ"}
    };

    for (auto [n, r, desc] : duplicate_problems) {
        long long ways = comb.H(n, r);
        cout << desc << ": " << ways << " 通り" << endl;
    }

    return 0;
}