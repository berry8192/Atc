// Rolling Hash ローリングハッシュ 文字列ハッシュ O(1) 部分文字列比較

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

// ========== ライブラリ部分 ==========

// Rolling Hash
class RollingHash {
  private:
    static const long long MOD1 = 1000000007LL;
    static const long long MOD2 = 1000000009LL;
    static long long BASE1, BASE2;

    vector<long long> hash1, hash2;
    vector<long long> pow1, pow2;
    int n;

    // 静的変数の初期化
    static void init_base() {
        if (BASE1 == 0) {
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            BASE1 = 257 + rng() % 100;
            BASE2 = 307 + rng() % 100;
        }
    }

  public:
    // コンストラクタ
    RollingHash(const string &s) : n(s.length()) {
        init_base();

        hash1.assign(n + 1, 0);
        hash2.assign(n + 1, 0);
        pow1.assign(n + 1, 1);
        pow2.assign(n + 1, 1);

        // ハッシュ値と累乗の前計算
        for (int i = 0; i < n; i++) {
            hash1[i + 1] = (hash1[i] * BASE1 + s[i]) % MOD1;
            hash2[i + 1] = (hash2[i] * BASE2 + s[i]) % MOD2;

            pow1[i + 1] = (pow1[i] * BASE1) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE2) % MOD2;
        }
    }

    // 部分文字列[l, r)のハッシュ値を取得
    pair<long long, long long> get_hash(int l, int r) {
        if (l < 0 || r > n || l >= r)
            return {0, 0};

        long long h1 = (hash1[r] - hash1[l] * pow1[r - l] % MOD1 + MOD1) % MOD1;
        long long h2 = (hash2[r] - hash2[l] * pow2[r - l] % MOD2 + MOD2) % MOD2;

        return {h1, h2};
    }

    // 部分文字列[l, r)のハッシュ値を取得（単一）
    long long get_single_hash(int l, int r) {
        auto [h1, h2] = get_hash(l, r);
        return h1;
    }

    // 文字列全体のハッシュ値
    pair<long long, long long> get_full_hash() { return get_hash(0, n); }

    // 二つの部分文字列が等しいか判定
    bool equal(int l1, int r1, int l2, int r2) {
        return get_hash(l1, r1) == get_hash(l2, r2);
    }

    // 文字列の長さを取得
    int size() const { return n; }
};

// 静的メンバの定義
long long RollingHash::BASE1 = 0;
long long RollingHash::BASE2 = 0;

// 複数文字列のハッシュ値を管理するクラス
class MultiStringHash {
  private:
    vector<RollingHash> hashes;
    vector<string> strings;

  public:
    // 文字列を追加
    void add_string(const string &s) {
        strings.push_back(s);
        hashes.emplace_back(s);
    }

    // 指定した文字列の部分文字列のハッシュ値を取得
    pair<long long, long long> get_hash(int str_id, int l, int r) {
        if (str_id < 0 || str_id >= (int)hashes.size())
            return {0, 0};
        return hashes[str_id].get_hash(l, r);
    }

    // 二つの部分文字列が等しいか判定
    bool equal(int str1, int l1, int r1, int str2, int l2, int r2) {
        if (str1 < 0 || str1 >= (int)hashes.size() || str2 < 0 ||
            str2 >= (int)hashes.size())
            return false;
        return hashes[str1].get_hash(l1, r1) == hashes[str2].get_hash(l2, r2);
    }

    // 文字列数を取得
    int size() const { return strings.size(); }

    // 文字列を取得
    string get_string(int id) const {
        if (id < 0 || id >= (int)strings.size())
            return "";
        return strings[id];
    }
};

// LCP（Longest Common Prefix）をRolling Hashで求める
int longest_common_prefix(RollingHash &rh1, int start1, RollingHash &rh2,
                          int start2) {
    int left = 0;
    int right = min(rh1.size() - start1, rh2.size() - start2) + 1;

    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (rh1.get_hash(start1, start1 + mid) ==
            rh2.get_hash(start2, start2 + mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

// ========== サンプルコード ==========

void solve() {
    MultiStringHash msh;
    string a, b;
    cin >> a >> b;
    msh.add_string(a + a);
    msh.add_string(b);

    int sz = a.size();
    rep(i, sz) {
        if (msh.equal(0, i, i + sz, 1, 0, sz)) {
            cout << i << endl;
            return;
        }
    }
    cout << -1 << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}