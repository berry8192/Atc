#include <bits/stdc++.h>
using namespace std;

// 素数を前計算する関数
vector<int> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            // cout << i << endl;
            primes.push_back(i);
            for (int j = i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return primes;
}

// 素因数分解を行う関数（前計算した素数リストを利用）
map<int, int> prime_factorize(int x, const vector<int> &primes) {
    map<int, int> factors;
    for (int prime : primes) {
        if (prime > x)
            break;
        while (x % prime == 0) {
            factors[prime]++;
            x /= prime;
        }
    }
    if (x > 1) {
        factors[x]++;
    }
    return factors;
}

// 各指数のNimゲームの勝敗を判定する関数
string nim_game_winner(const vector<int> &numbers, const vector<int> &primes) {
    // 各素数の指数のXORを保存するmap
    vector<int> exponent_counts(numbers.size());

    // 数字ごとの素因数分解を行い指数を収集
    for (int i = 0; i < numbers.size(); i++) {
        map<int, int> factors = prime_factorize(numbers[i], primes);
        for (auto &factor : factors) {
            exponent_counts[i] += factor.second;
        }
    }

    // XOR和を計算
    int xor_sum = 0;
    for (auto &entry : exponent_counts) {
        xor_sum ^= entry;
    }

    // 勝者を決定
    if (xor_sum != 0) {
        return "Anna"; // 先行の勝ち
    } else {
        return "Bruno"; // 後攻の勝ち
    }
}

int main() {
    const int MAX_PRIME = 100000;
    vector<int> primes = sieve(MAX_PRIME);

    int n;
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    // Nimゲームの結果を出力
    cout << nim_game_winner(v, primes) << endl;

    return 0;
}
