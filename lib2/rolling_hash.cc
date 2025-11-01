// Rolling Hash ローリングハッシュ 文字列ハッシュ O(1) 部分文字列比較

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
using namespace std;

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
    RollingHash(const string& s) : n(s.length()) {
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
        if (l < 0 || r > n || l >= r) return {0, 0};

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
    pair<long long, long long> get_full_hash() {
        return get_hash(0, n);
    }

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
    void add_string(const string& s) {
        strings.push_back(s);
        hashes.emplace_back(s);
    }

    // 指定した文字列の部分文字列のハッシュ値を取得
    pair<long long, long long> get_hash(int str_id, int l, int r) {
        if (str_id < 0 || str_id >= (int)hashes.size()) return {0, 0};
        return hashes[str_id].get_hash(l, r);
    }

    // 二つの部分文字列が等しいか判定
    bool equal(int str1, int l1, int r1, int str2, int l2, int r2) {
        if (str1 < 0 || str1 >= (int)hashes.size() ||
            str2 < 0 || str2 >= (int)hashes.size()) return false;
        return hashes[str1].get_hash(l1, r1) == hashes[str2].get_hash(l2, r2);
    }

    // 文字列数を取得
    int size() const { return strings.size(); }

    // 文字列を取得
    string get_string(int id) const {
        if (id < 0 || id >= (int)strings.size()) return "";
        return strings[id];
    }
};

// LCP（Longest Common Prefix）をRolling Hashで求める
int longest_common_prefix(RollingHash& rh1, int start1, RollingHash& rh2, int start2) {
    int left = 0;
    int right = min(rh1.size() - start1, rh2.size() - start2) + 1;

    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (rh1.get_hash(start1, start1 + mid) == rh2.get_hash(start2, start2 + mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な部分文字列比較
    cout << "例1: 基本的な部分文字列比較" << endl;
    string s1 = "abcdefg";
    RollingHash rh1(s1);

    cout << "文字列: " << s1 << endl;
    cout << "全体のハッシュ値: " << rh1.get_single_hash(0, s1.length()) << endl;

    // 部分文字列のハッシュ値
    cout << "部分文字列のハッシュ値:" << endl;
    for (int len = 1; len <= 3; len++) {
        for (int i = 0; i + len <= (int)s1.length(); i++) {
            cout << "s[" << i << ":" << i + len << "] = \"";
            cout << s1.substr(i, len) << "\" -> ";
            cout << rh1.get_single_hash(i, i + len) << endl;
        }
    }
    cout << endl;

    // 例2: 部分文字列の等値判定
    cout << "例2: 部分文字列の等値判定" << endl;
    string s2 = "abcabcabc";
    RollingHash rh2(s2);

    cout << "文字列: " << s2 << endl;
    vector<pair<pair<int, int>, pair<int, int>>> comparisons = {
        {{0, 3}, {3, 6}},  // "abc" と "abc"
        {{0, 3}, {6, 9}},  // "abc" と "abc"
        {{1, 4}, {4, 7}},  // "bca" と "bca"
        {{0, 2}, {3, 5}},  // "ab" と "ab"
        {{0, 3}, {1, 4}}   // "abc" と "bca"
    };

    for (auto [range1, range2] : comparisons) {
        auto [l1, r1] = range1;
        auto [l2, r2] = range2;
        string sub1 = s2.substr(l1, r1 - l1);
        string sub2 = s2.substr(l2, r2 - l2);
        bool equal = rh2.equal(l1, r1, l2, r2);
        cout << "\"" << sub1 << "\" == \"" << sub2 << "\": " << (equal ? "Yes" : "No") << endl;
    }
    cout << endl;

    // 例3: 複数文字列の比較
    cout << "例3: 複数文字列の比較" << endl;
    MultiStringHash msh;
    vector<string> strings = {"hello", "world", "helloworld", "hell"};

    for (const string& s : strings) {
        msh.add_string(s);
    }

    // すべてのペアで部分文字列を比較
    for (int i = 0; i < msh.size(); i++) {
        for (int j = i + 1; j < msh.size(); j++) {
            string s1 = msh.get_string(i);
            string s2 = msh.get_string(j);
            cout << "文字列" << i << "(\"" << s1 << "\") と 文字列" << j << "(\"" << s2 << "\"):" << endl;

            // 共通の長さで比較
            int min_len = min(s1.length(), s2.length());
            for (int len = 1; len <= min_len; len++) {
                bool equal = msh.equal(i, 0, len, j, 0, len);
                cout << "  先頭" << len << "文字: " << (equal ? "一致" : "不一致") << endl;
            }
        }
    }
    cout << endl;

    // 例4: Longest Common Prefix
    cout << "例4: Longest Common Prefix" << endl;
    string str1 = "abcdefgh";
    string str2 = "abcdxyz";
    RollingHash rh_str1(str1);
    RollingHash rh_str2(str2);

    int lcp = longest_common_prefix(rh_str1, 0, rh_str2, 0);
    cout << "文字列1: " << str1 << endl;
    cout << "文字列2: " << str2 << endl;
    cout << "LCP長: " << lcp << endl;
    cout << "共通接頭辞: \"" << str1.substr(0, lcp) << "\"" << endl;
    cout << endl;

    // 例5: 回文判定
    cout << "例5: 回文判定" << endl;
    vector<string> palindrome_candidates = {"racecar", "hello", "abccba", "a", "abcd"};

    for (const string& s : palindrome_candidates) {
        RollingHash rh(s);
        bool is_palindrome = true;
        int n = s.length();

        // 前半と後半を逆順で比較
        for (int len = 1; len <= n / 2; len++) {
            if (!rh.equal(0, len, n - len, n)) {
                is_palindrome = false;
                break;
            }
        }

        cout << "\"" << s << "\": " << (is_palindrome ? "回文" : "回文でない") << endl;
    }

    return 0;
}