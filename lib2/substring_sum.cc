// 部分文字列の数値和 substring sum 桁ごとの寄与度計算
// ABC379 E - Sum of All Substrings 用

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ========== ライブラリ本体 ==========

// 数字文字列の全ての部分文字列を数値と見なした和を計算
struct SubstringSum {
    string s;
    int n;
    vector<long long> contribution;  // 各桁の寄与度
    
    SubstringSum(const string& str) : s(str), n(str.size()) {
        calculate_contributions();
    }
    
    // 各桁の寄与度を計算
    void calculate_contributions() {
        contribution.resize(n);
        
        // i番目の文字が含まれる部分文字列の数と、その中での位置を考慮
        for (int i = 0; i < n; i++) {
            // i番目の文字を含む部分文字列は、
            // 左端が0～i、右端がi～n-1の範囲
            long long count = (long long)(i + 1) * (n - i);
            contribution[i] = count * (s[i] - '0');
        }
    }
    
    // 単純な和の計算（桁上がりを考慮しない）
    long long simple_sum() {
        long long result = 0;
        long long place_value = 1;
        
        for (int i = n - 1; i >= 0; i--) {
            result += contribution[i] * place_value;
            place_value *= 10;
        }
        
        return result;
    }
    
    // 桁ごとの寄与を考慮した正確な和
    string exact_sum() {
        // 各桁での値を計算（桁上がりを考慮）
        vector<long long> digit_sum(n + 10, 0);
        
        for (int i = 0; i < n; i++) {
            int digit = s[i] - '0';
            // i番目の文字が各桁に与える寄与
            for (int j = i; j < n; j++) {
                // 部分文字列[l, j]でi番目が(j-i)桁目になる
                // lは0からiまで動く
                long long count = i + 1;
                int pos = n - 1 - j + (j - i);  // 最終的な桁位置
                if (pos >= 0) {
                    digit_sum[pos] += count * digit;
                }
            }
        }
        
        // 桁上がり処理
        for (int i = 0; i < digit_sum.size() - 1; i++) {
            if (digit_sum[i] >= 10) {
                digit_sum[i + 1] += digit_sum[i] / 10;
                digit_sum[i] %= 10;
            }
        }
        
        // 文字列に変換
        string result;
        bool started = false;
        for (int i = digit_sum.size() - 1; i >= 0; i--) {
            if (digit_sum[i] > 0 || started) {
                result += to_string(digit_sum[i]);
                started = true;
            }
        }
        
        return result.empty() ? "0" : result;
    }
};

// ABC379 E用: 効率的な解法
long long solve_substring_sum_efficient(const string& s) {
    int n = s.size();
    long long result = 0;
    long long carry = 0;
    
    // 右から処理
    for (int i = n - 1; i >= 0; i--) {
        // i番目の数字が寄与する回数
        long long contribution = (long long)(s[i] - '0') * (i + 1) * (n - i);
        contribution += carry;
        
        result = (result * 10 + contribution % 10);
        carry = contribution / 10;
    }
    
    // 残りの桁上がりを処理
    string result_str = to_string(carry) + to_string(result);
    
    // 逆順にして返す
    reverse(result_str.begin(), result_str.end());
    
    // 先頭の0を除去
    size_t pos = result_str.find_first_not_of('0');
    if (pos == string::npos) return 0;
    
    return stoll(result_str.substr(pos));
}

// 正確な解法（大きな数にも対応）
string solve_substring_sum_exact(const string& s) {
    int n = s.size();
    vector<long long> digits(2 * n + 10, 0);
    
    // 各位置の寄与を計算
    for (int i = 0; i < n; i++) {
        long long val = (long long)(s[i] - '0') * (i + 1) * (n - i);
        digits[n - 1 - i] += val;
    }
    
    // 桁上がり処理
    for (int i = 0; i < digits.size() - 1; i++) {
        if (digits[i] >= 10) {
            digits[i + 1] += digits[i] / 10;
            digits[i] %= 10;
        }
    }
    
    // 文字列化
    string result;
    bool started = false;
    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] > 0 || started) {
            result += char('0' + digits[i]);
            started = true;
        }
    }
    
    return result.empty() ? "0" : result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 小さな文字列
    cout << "例1: 基本的な例" << endl;
    string s1 = "123";
    cout << "文字列: " << s1 << endl;
    cout << "部分文字列: 1, 2, 3, 12, 23, 123" << endl;
    cout << "和: 1+2+3+12+23+123 = 164" << endl;
    cout << "計算結果: " << solve_substring_sum_exact(s1) << endl;
    cout << endl;
    
    // 例2: 同じ数字の繰り返し
    cout << "例2: 同じ数字" << endl;
    string s2 = "111";
    cout << "文字列: " << s2 << endl;
    cout << "計算結果: " << solve_substring_sum_exact(s2) << endl;
    cout << endl;
    
    // 例3: ABC379 E の例
    cout << "例3: ABC379 E タイプ" << endl;
    string s3 = "1333";
    cout << "文字列: " << s3 << endl;
    cout << "計算結果: " << solve_substring_sum_exact(s3) << endl;
    cout << endl;
    
    // 例4: 大きな数字
    cout << "例4: 大きな数字" << endl;
    string s4 = "999999";
    SubstringSum ss4(s4);
    cout << "文字列: " << s4 << endl;
    cout << "各桁の寄与度:" << endl;
    for (int i = 0; i < min(6, (int)s4.size()); i++) {
        cout << "  位置" << i << ": " << ss4.contribution[i] << endl;
    }
    cout << "計算結果: " << solve_substring_sum_exact(s4) << endl;
    cout << endl;
    
    // 例5: 効率性の比較
    cout << "例5: 長い文字列での処理" << endl;
    string s5 = "";
    for (int i = 0; i < 20; i++) {
        s5 += to_string((i * 3) % 10);
    }
    cout << "文字列長: " << s5.size() << endl;
    cout << "文字列: " << s5 << endl;
    cout << "計算結果: " << solve_substring_sum_exact(s5) << endl;
    
    return 0;
}