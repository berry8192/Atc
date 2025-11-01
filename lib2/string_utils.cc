// 文字列の便利関数 string_utils 操作・変換・検索 O(N)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <regex>
#include <map>
#include <set>
using namespace std;

// ========== ライブラリ部分 ==========

// 文字列分割
vector<string> split(const string& str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

// 複数文字区切りでの分割
vector<string> split_multi(const string& str, const string& delimiters) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find_first_of(delimiters);

    while (end != string::npos) {
        if (end != start) {
            result.push_back(str.substr(start, end - start));
        }
        start = end + 1;
        end = str.find_first_of(delimiters, start);
    }

    if (start < str.length()) {
        result.push_back(str.substr(start));
    }

    return result;
}

// 文字列結合
string join(const vector<string>& strings, const string& delimiter) {
    if (strings.empty()) return "";

    string result = strings[0];
    for (int i = 1; i < strings.size(); i++) {
        result += delimiter + strings[i];
    }
    return result;
}

// トリム（前後の空白除去）
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) return "";

    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

// 前の空白除去
string ltrim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    return (start == string::npos) ? "" : str.substr(start);
}

// 後の空白除去
string rtrim(const string& str) {
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return (end == string::npos) ? "" : str.substr(0, end + 1);
}

// 大文字変換
string to_upper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// 小文字変換
string to_lower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// 文字列置換（全て）
string replace_all(string str, const string& from, const string& to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

// 文字列逆順
string reverse_string(const string& str) {
    string result = str;
    reverse(result.begin(), result.end());
    return result;
}

// 回文判定
bool is_palindrome(const string& str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) return false;
        left++;
        right--;
    }
    return true;
}

// 英数字のみの回文判定
bool is_palindrome_alphanumeric(const string& str) {
    string filtered;
    for (char c : str) {
        if (isalnum(c)) {
            filtered += tolower(c);
        }
    }
    return is_palindrome(filtered);
}

// 文字頻度カウント
map<char, int> count_chars(const string& str) {
    map<char, int> count;
    for (char c : str) {
        count[c]++;
    }
    return count;
}

// 最も頻繁な文字
char most_frequent_char(const string& str) {
    auto count = count_chars(str);
    char result = '\0';
    int max_count = 0;
    for (auto& p : count) {
        if (p.second > max_count) {
            max_count = p.second;
            result = p.first;
        }
    }
    return result;
}

// 文字列中の部分文字列出現回数
int count_substring(const string& str, const string& sub) {
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(sub, pos)) != string::npos) {
        count++;
        pos += sub.length();
    }
    return count;
}

// 重複しない部分文字列出現回数
int count_substring_non_overlapping(const string& str, const string& sub) {
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(sub, pos)) != string::npos) {
        count++;
        pos += sub.length();
    }
    return count;
}

// 文字列がプレフィックスかチェック
bool starts_with(const string& str, const string& prefix) {
    return str.length() >= prefix.length() &&
           str.substr(0, prefix.length()) == prefix;
}

// 文字列がサフィックスかチェック
bool ends_with(const string& str, const string& suffix) {
    return str.length() >= suffix.length() &&
           str.substr(str.length() - suffix.length()) == suffix;
}

// 数値文字列かチェック
bool is_numeric(const string& str) {
    if (str.empty()) return false;
    int start = 0;
    if (str[0] == '+' || str[0] == '-') start = 1;

    for (int i = start; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return start < str.length();
}

// 浮動小数点数文字列かチェック
bool is_float(const string& str) {
    if (str.empty()) return false;
    bool has_dot = false;
    int start = 0;
    if (str[0] == '+' || str[0] == '-') start = 1;

    for (int i = start; i < str.length(); i++) {
        if (str[i] == '.') {
            if (has_dot) return false;
            has_dot = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return start < str.length();
}

// Levenshtein距離（編集距離）
int levenshtein_distance(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    return dp[m][n];
}

// 文字列の最長共通部分文字列
string longest_common_substring(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int max_len = 0;
    int ending_pos = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                    ending_pos = i;
                }
            }
        }
    }

    return s1.substr(ending_pos - max_len, max_len);
}

// 文字列のランレングス符号化
vector<pair<char, int>> run_length_encode(const string& str) {
    vector<pair<char, int>> result;
    if (str.empty()) return result;

    char current = str[0];
    int count = 1;

    for (int i = 1; i < str.length(); i++) {
        if (str[i] == current) {
            count++;
        } else {
            result.push_back({current, count});
            current = str[i];
            count = 1;
        }
    }
    result.push_back({current, count});

    return result;
}

// ランレングス符号化からの復号
string run_length_decode(const vector<pair<char, int>>& encoded) {
    string result;
    for (auto& p : encoded) {
        result += string(p.second, p.first);
    }
    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 文字列分割と結合
    cout << "例1: 文字列分割と結合" << endl;
    string csv = "apple,banana,cherry,date";
    auto fruits = split(csv, ',');
    cout << "分割: ";
    for (const string& fruit : fruits) {
        cout << "[" << fruit << "] ";
    }
    cout << endl;
    cout << "結合: " << join(fruits, " | ") << endl;
    cout << endl;

    // 例2: トリムと大小文字変換
    cout << "例2: トリムと大小文字変換" << endl;
    string messy = "  Hello World  ";
    cout << "元の文字列: [" << messy << "]" << endl;
    cout << "トリム後: [" << trim(messy) << "]" << endl;
    cout << "大文字: [" << to_upper(trim(messy)) << "]" << endl;
    cout << "小文字: [" << to_lower(trim(messy)) << "]" << endl;
    cout << endl;

    // 例3: 文字列置換
    cout << "例3: 文字列置換" << endl;
    string text = "Hello World Hello Universe";
    cout << "元: " << text << endl;
    cout << "置換後: " << replace_all(text, "Hello", "Hi") << endl;
    cout << endl;

    // 例4: 回文判定
    cout << "例4: 回文判定" << endl;
    vector<string> test_strings = {"racecar", "hello", "A man a plan a canal Panama"};
    for (const string& s : test_strings) {
        cout << "\"" << s << "\" は回文: " << (is_palindrome(s) ? "Yes" : "No") << endl;
        cout << "\"" << s << "\" は英数字回文: " << (is_palindrome_alphanumeric(s) ? "Yes" : "No") << endl;
    }
    cout << endl;

    // 例5: 文字頻度と最頻文字
    cout << "例5: 文字頻度と最頻文字" << endl;
    string sample = "programming";
    auto freq = count_chars(sample);
    cout << "文字列: " << sample << endl;
    cout << "文字頻度: ";
    for (auto& p : freq) {
        cout << p.first << ":" << p.second << " ";
    }
    cout << endl;
    cout << "最頻文字: " << most_frequent_char(sample) << endl;
    cout << endl;

    // 例6: 部分文字列検索
    cout << "例6: 部分文字列検索" << endl;
    string haystack = "abcabcabc";
    string needle = "abc";
    cout << "文字列: " << haystack << endl;
    cout << "部分文字列 \"" << needle << "\" の出現回数: " << count_substring(haystack, needle) << endl;
    cout << "重複なし出現回数: " << count_substring_non_overlapping(haystack, needle) << endl;
    cout << endl;

    // 例7: プレフィックス・サフィックス判定
    cout << "例7: プレフィックス・サフィックス判定" << endl;
    string filename = "document.pdf";
    cout << "ファイル名: " << filename << endl;
    cout << "\"doc\" で始まる: " << (starts_with(filename, "doc") ? "Yes" : "No") << endl;
    cout << "\".pdf\" で終わる: " << (ends_with(filename, ".pdf") ? "Yes" : "No") << endl;
    cout << endl;

    // 例8: 数値判定
    cout << "例8: 数値判定" << endl;
    vector<string> numbers = {"123", "-456", "12.34", "abc", "12.34.56"};
    for (const string& num : numbers) {
        cout << "\"" << num << "\" は整数: " << (is_numeric(num) ? "Yes" : "No");
        cout << ", 浮動小数点: " << (is_float(num) ? "Yes" : "No") << endl;
    }
    cout << endl;

    // 例9: 編集距離
    cout << "例9: 編集距離" << endl;
    string s1 = "kitten", s2 = "sitting";
    cout << "\"" << s1 << "\" と \"" << s2 << "\" の編集距離: " << levenshtein_distance(s1, s2) << endl;
    cout << endl;

    // 例10: 最長共通部分文字列
    cout << "例10: 最長共通部分文字列" << endl;
    string str1 = "abcdxyz", str2 = "xyzabcd";
    cout << "\"" << str1 << "\" と \"" << str2 << "\" の最長共通部分文字列: \""
         << longest_common_substring(str1, str2) << "\"" << endl;
    cout << endl;

    // 例11: ランレングス符号化
    cout << "例11: ランレングス符号化" << endl;
    string rle_input = "aaabbbbcccc";
    auto encoded = run_length_encode(rle_input);
    cout << "元の文字列: " << rle_input << endl;
    cout << "符号化: ";
    for (auto& p : encoded) {
        cout << p.first << p.second << " ";
    }
    cout << endl;
    cout << "復号: " << run_length_decode(encoded) << endl;

    return 0;
}