// KMP法 文字列検索 前処理O(M) 検索O(N) パターンマッチング

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ========== ライブラリ部分 ==========

// KMP（Knuth-Morris-Pratt）法
class KMP {
private:
    string pattern;
    vector<int> failure_function;

    // Failure Function（Border配列）を構築
    void build_failure_function() {
        int m = pattern.length();
        failure_function.assign(m, 0);

        for (int i = 1; i < m; i++) {
            int j = failure_function[i - 1];
            while (j > 0 && pattern[i] != pattern[j]) {
                j = failure_function[j - 1];
            }
            if (pattern[i] == pattern[j]) {
                j++;
            }
            failure_function[i] = j;
        }
    }

public:
    // コンストラクタ
    KMP(const string& pat) : pattern(pat) {
        build_failure_function();
    }

    // テキスト内でパターンを検索し、すべての開始位置を返す
    vector<int> search(const string& text) {
        vector<int> matches;
        int n = text.length();
        int m = pattern.length();

        if (m == 0) return matches;
        if (n < m) return matches;

        int j = 0;  // pattern内のインデックス
        for (int i = 0; i < n; i++) {
            while (j > 0 && text[i] != pattern[j]) {
                j = failure_function[j - 1];
            }
            if (text[i] == pattern[j]) {
                j++;
            }
            if (j == m) {
                matches.push_back(i - m + 1);
                j = failure_function[j - 1];
            }
        }
        return matches;
    }

    // 最初の一致位置を返す（見つからない場合は-1）
    int find_first(const string& text) {
        auto matches = search(text);
        return matches.empty() ? -1 : matches[0];
    }

    // 一致回数を返す
    int count_matches(const string& text) {
        return search(text).size();
    }

    // Failure Functionを取得
    vector<int> get_failure_function() const {
        return failure_function;
    }

    // パターンを取得
    string get_pattern() const {
        return pattern;
    }
};

// Z-algorithm（参考実装）
vector<int> z_algorithm(const string& s) {
    int n = s.length();
    vector<int> z(n);
    z[0] = n;

    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// 文字列の周期を求める
vector<int> find_periods(const string& s) {
    KMP kmp(s);
    auto failure = kmp.get_failure_function();
    vector<int> periods;

    int n = s.length();
    int len = failure[n - 1];
    while (len > 0) {
        periods.push_back(n - len);
        len = failure[len - 1];
    }
    periods.push_back(n);  // 自明な周期
    return periods;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な文字列検索
    cout << "例1: 基本的な文字列検索" << endl;
    string text1 = "ababcababa";
    string pattern1 = "aba";

    KMP kmp1(pattern1);
    auto matches1 = kmp1.search(text1);

    cout << "テキスト: " << text1 << endl;
    cout << "パターン: " << pattern1 << endl;
    cout << "一致位置: ";
    for (int pos : matches1) {
        cout << pos << " ";
    }
    cout << endl;
    cout << "一致回数: " << kmp1.count_matches(text1) << endl;
    cout << endl;

    // 例2: Failure Functionの表示
    cout << "例2: Failure Function（Border配列）" << endl;
    vector<string> patterns = {"ababa", "aabaaba", "abcabc"};

    for (const string& pat : patterns) {
        KMP kmp(pat);
        auto failure = kmp.get_failure_function();

        cout << "パターン: " << pat << endl;
        cout << "位置:     ";
        for (int i = 0; i < (int)pat.length(); i++) {
            cout << i << " ";
        }
        cout << endl;

        cout << "文字:     ";
        for (char c : pat) {
            cout << c << " ";
        }
        cout << endl;

        cout << "Failure:  ";
        for (int f : failure) {
            cout << f << " ";
        }
        cout << endl << endl;
    }

    // 例3: 複数パターンの検索
    cout << "例3: 複数パターンの検索" << endl;
    string text3 = "abracadabracadabra";
    vector<string> patterns3 = {"abra", "cada", "bra", "ad"};

    cout << "テキスト: " << text3 << endl;
    for (const string& pat : patterns3) {
        KMP kmp(pat);
        auto matches = kmp.search(text3);
        cout << "パターン '" << pat << "': ";
        for (int pos : matches) {
            cout << pos << " ";
        }
        cout << "(" << matches.size() << "回)" << endl;
    }
    cout << endl;

    // 例4: 文字列の周期
    cout << "例4: 文字列の周期" << endl;
    vector<string> periodic_strings = {"abab", "abcabc", "aaaa", "abcdef"};

    for (const string& s : periodic_strings) {
        auto periods = find_periods(s);
        cout << "文字列 '" << s << "' の周期: ";
        for (int p : periods) {
            cout << p << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 例5: Z-algorithmとの比較
    cout << "例5: Z-algorithmとの比較" << endl;
    string s = "abacaba";
    auto z = z_algorithm(s);

    cout << "文字列: " << s << endl;
    cout << "Z配列:  ";
    for (int val : z) {
        cout << val << " ";
    }
    cout << endl;

    // KMPのFailure Functionと比較
    KMP kmp_z(s);
    auto failure_z = kmp_z.get_failure_function();
    cout << "Failure:";
    for (int val : failure_z) {
        cout << val << " ";
    }
    cout << endl;
    cout << endl;

    // 例6: 大文字小文字を区別しない検索（応用例）
    cout << "例6: 大文字小文字を区別しない検索" << endl;
    auto to_lower = [](string s) {
        for (char& c : s) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        }
        return s;
    };

    string text6 = "Hello World Hello";
    string pattern6 = "hello";

    KMP kmp6(to_lower(pattern6));
    auto matches6 = kmp6.search(to_lower(text6));

    cout << "テキスト: " << text6 << endl;
    cout << "パターン: " << pattern6 << " (大文字小文字無視)" << endl;
    cout << "一致位置: ";
    for (int pos : matches6) {
        cout << pos << " ";
    }
    cout << endl;

    return 0;
}