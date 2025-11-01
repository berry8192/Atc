// Manacher法 回文検出 全回文部分文字列 O(N)

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ========== ライブラリ部分 ==========

// Manacher法クラス
class Manacher {
private:
    string original;
    string processed;
    vector<int> radius;
    int n;

    // 文字列を前処理（文字間に特殊文字を挿入）
    string preprocess(const string& s) {
        string result = "^";  // 番兵
        for (char c : s) {
            result += "#";
            result += c;
        }
        result += "#$";  // 番兵
        return result;
    }

    // Manacher算法の実行
    void build() {
        processed = preprocess(original);
        n = processed.length();
        radius.assign(n, 0);

        int center = 0, right = 0;
        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * center - i;

            if (i < right) {
                radius[i] = min(right - i, radius[mirror]);
            }

            // 回文を拡張
            while (processed[i + radius[i] + 1] == processed[i - radius[i] - 1]) {
                radius[i]++;
            }

            // 右端を更新
            if (i + radius[i] > right) {
                center = i;
                right = i + radius[i];
            }
        }
    }

public:
    // コンストラクタ
    Manacher(const string& s) : original(s) {
        build();
    }

    // 位置i（元の文字列での位置）を中心とする奇数長回文の半径
    int odd_radius(int i) {
        if (i < 0 || i >= (int)original.length()) return 0;
        int processed_pos = 2 * i + 2;  // 処理済み文字列での位置
        return radius[processed_pos] / 2;
    }

    // 位置i（元の文字列での位置）を中心とする偶数長回文の半径
    int even_radius(int i) {
        if (i < 0 || i >= (int)original.length() - 1) return 0;
        int processed_pos = 2 * i + 3;  // 処理済み文字列での位置
        return radius[processed_pos] / 2;
    }

    // 位置iを中心とする最長回文の長さ（奇数長と偶数長の最大）
    int max_palindrome_length(int i) {
        int odd_len = 2 * odd_radius(i) + 1;
        int even_len = 2 * even_radius(i);
        return max(odd_len, even_len);
    }

    // 部分文字列[l, r]が回文かどうか判定
    bool is_palindrome(int l, int r) {
        if (l < 0 || r >= (int)original.length() || l > r) return false;
        int len = r - l + 1;
        int center = (l + r) / 2;

        if (len % 2 == 1) {
            // 奇数長
            return odd_radius(center) >= len / 2;
        } else {
            // 偶数長
            return even_radius(center) >= len / 2;
        }
    }

    // 最長回文部分文字列を取得
    string longest_palindrome() {
        int max_len = 0;
        int start = 0;

        for (int i = 0; i < (int)original.length(); i++) {
            // 奇数長回文をチェック
            int odd_len = 2 * odd_radius(i) + 1;
            if (odd_len > max_len) {
                max_len = odd_len;
                start = i - odd_radius(i);
            }

            // 偶数長回文をチェック
            if (i < (int)original.length() - 1) {
                int even_len = 2 * even_radius(i);
                if (even_len > max_len) {
                    max_len = even_len;
                    start = i - even_radius(i) + 1;
                }
            }
        }

        return original.substr(start, max_len);
    }

    // すべての回文部分文字列の情報を取得
    vector<tuple<int, int, int>> all_palindromes() {
        vector<tuple<int, int, int>> palindromes;  // (start, end, length)

        for (int i = 0; i < (int)original.length(); i++) {
            // 奇数長回文
            int odd_r = odd_radius(i);
            for (int r = 0; r <= odd_r; r++) {
                int start = i - r;
                int end = i + r;
                int length = 2 * r + 1;
                palindromes.emplace_back(start, end, length);
            }

            // 偶数長回文
            if (i < (int)original.length() - 1) {
                int even_r = even_radius(i);
                for (int r = 1; r <= even_r; r++) {
                    int start = i - r + 1;
                    int end = i + r;
                    int length = 2 * r;
                    palindromes.emplace_back(start, end, length);
                }
            }
        }

        return palindromes;
    }

    // 元の文字列を取得
    string get_string() const {
        return original;
    }
};

// 回文の個数を数える
int count_palindromes(const string& s) {
    Manacher manacher(s);
    int count = 0;
    int n = s.length();

    for (int i = 0; i < n; i++) {
        count += manacher.odd_radius(i) + 1;  // 奇数長回文
        if (i < n - 1) {
            count += manacher.even_radius(i);  // 偶数長回文
        }
    }

    return count;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な回文検出
    cout << "例1: 基本的な回文検出" << endl;
    string s1 = "racecar";
    Manacher manacher1(s1);

    cout << "文字列: " << s1 << endl;
    cout << "最長回文: \"" << manacher1.longest_palindrome() << "\"" << endl;
    cout << "文字列全体が回文: " << (manacher1.is_palindrome(0, s1.length() - 1) ? "Yes" : "No") << endl;
    cout << endl;

    // 例2: 各位置での回文半径
    cout << "例2: 各位置での回文半径" << endl;
    string s2 = "abaaababa";
    Manacher manacher2(s2);

    cout << "文字列: " << s2 << endl;
    cout << "位置: ";
    for (int i = 0; i < (int)s2.length(); i++) {
        cout << i << " ";
    }
    cout << endl;

    cout << "文字: ";
    for (char c : s2) {
        cout << c << " ";
    }
    cout << endl;

    cout << "奇数: ";
    for (int i = 0; i < (int)s2.length(); i++) {
        cout << manacher2.odd_radius(i) << " ";
    }
    cout << endl;

    cout << "偶数: ";
    for (int i = 0; i < (int)s2.length() - 1; i++) {
        cout << manacher2.even_radius(i) << " ";
    }
    cout << endl;
    cout << endl;

    // 例3: 部分文字列の回文判定
    cout << "例3: 部分文字列の回文判定" << endl;
    string s3 = "abcdefedcba";
    Manacher manacher3(s3);

    cout << "文字列: " << s3 << endl;
    vector<pair<int, int>> ranges = {{0, 2}, {3, 7}, {5, 9}, {0, 10}};

    for (auto [l, r] : ranges) {
        string substr = s3.substr(l, r - l + 1);
        bool is_pal = manacher3.is_palindrome(l, r);
        cout << "s[" << l << ":" << r + 1 << "] = \"" << substr << "\": ";
        cout << (is_pal ? "回文" : "回文でない") << endl;
    }
    cout << endl;

    // 例4: すべての回文部分文字列
    cout << "例4: すべての回文部分文字列" << endl;
    string s4 = "aba";
    Manacher manacher4(s4);

    cout << "文字列: " << s4 << endl;
    auto palindromes = manacher4.all_palindromes();

    cout << "すべての回文部分文字列:" << endl;
    for (auto [start, end, length] : palindromes) {
        string palindrome = s4.substr(start, length);
        cout << "[" << start << ", " << end << "] \"" << palindrome << "\" (長さ " << length << ")" << endl;
    }
    cout << "回文の総数: " << palindromes.size() << endl;
    cout << endl;

    // 例5: 回文数のカウント
    cout << "例5: 回文数のカウント" << endl;
    vector<string> test_strings = {"a", "aa", "aba", "abcba", "aabbaa"};

    for (const string& s : test_strings) {
        int count = count_palindromes(s);
        cout << "\"" << s << "\": " << count << "個の回文" << endl;
    }
    cout << endl;

    // 例6: 長い文字列での性能確認
    cout << "例6: 長い文字列での最長回文" << endl;
    string s6 = "abcdefghijklmnopqrstuvwxyzabcdefedcbazyxwvutsrqponmlkjihgfedcba";
    Manacher manacher6(s6);

    cout << "文字列長: " << s6.length() << endl;
    string longest = manacher6.longest_palindrome();
    cout << "最長回文: \"" << longest << "\" (長さ " << longest.length() << ")" << endl;

    // 最長回文の位置を見つける
    size_t pos = s6.find(longest);
    cout << "位置: [" << pos << ", " << pos + longest.length() - 1 << "]" << endl;

    return 0;
}