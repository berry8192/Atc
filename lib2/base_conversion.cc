// 進数変換 base_conversion 2進数、16進数、任意進数 O(log N)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;

// ========== ライブラリ部分 ==========

// 10進数を任意の進数に変換
string to_base(long long n, int base) {
    if (n == 0) return "0";
    string result = "";
    bool negative = n < 0;
    n = abs(n);

    const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (n > 0) {
        result = digits[n % base] + result;
        n /= base;
    }
    return negative ? "-" + result : result;
}

// 任意の進数から10進数に変換
long long from_base(const string& s, int base) {
    long long result = 0;
    long long power = 1;
    bool negative = false;
    int start = 0;

    if (s[0] == '-') {
        negative = true;
        start = 1;
    }

    for (int i = s.length() - 1; i >= start; i--) {
        char c = s[i];
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else {
            continue;
        }
        result += digit * power;
        power *= base;
    }

    return negative ? -result : result;
}

// 10進数を2進数文字列に変換
string to_binary(long long n) {
    return to_base(n, 2);
}

// 2進数文字列から10進数に変換
long long from_binary(const string& s) {
    return from_base(s, 2);
}

// 10進数を16進数文字列に変換
string to_hex(long long n) {
    return to_base(n, 16);
}

// 16進数文字列から10進数に変換
long long from_hex(const string& s) {
    return from_base(s, 16);
}

// bitsetを使った2進数表現（固定長）
template<int N>
string to_binary_fixed(long long n) {
    bitset<N> bs(n);
    return bs.to_string();
}

// 指定桁数の2進数表現
string to_binary_width(long long n, int width) {
    string bin = to_binary(abs(n));
    while (bin.length() < width) {
        bin = "0" + bin;
    }
    return n < 0 ? "-" + bin : bin;
}

// 2進数のビット操作補助関数
bool get_bit(long long n, int pos) {
    return (n >> pos) & 1;
}

void set_bit(long long& n, int pos) {
    n |= (1LL << pos);
}

void clear_bit(long long& n, int pos) {
    n &= ~(1LL << pos);
}

void toggle_bit(long long& n, int pos) {
    n ^= (1LL << pos);
}

// ビット数を数える
int count_bits(long long n) {
    return __builtin_popcountll(n);
}

// 最下位ビットの位置
int lowest_bit(long long n) {
    return __builtin_ctzll(n);
}

// 最上位ビットの位置
int highest_bit(long long n) {
    return 63 - __builtin_clzll(n);
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な進数変換
    cout << "例1: 基本的な進数変換" << endl;
    long long num = 255;
    cout << "10進数: " << num << endl;
    cout << "2進数: " << to_binary(num) << endl;
    cout << "8進数: " << to_base(num, 8) << endl;
    cout << "16進数: " << to_hex(num) << endl;
    cout << "36進数: " << to_base(num, 36) << endl;
    cout << endl;

    // 例2: 各進数から10進数に戻す
    cout << "例2: 各進数から10進数に戻す" << endl;
    cout << "11111111 (2進数) -> " << from_binary("11111111") << endl;
    cout << "377 (8進数) -> " << from_base("377", 8) << endl;
    cout << "FF (16進数) -> " << from_hex("FF") << endl;
    cout << "73 (36進数) -> " << from_base("73", 36) << endl;
    cout << endl;

    // 例3: 固定長2進数表現
    cout << "例3: 固定長2進数表現" << endl;
    cout << "42の8bit表現: " << to_binary_fixed<8>(42) << endl;
    cout << "42の16bit表現: " << to_binary_fixed<16>(42) << endl;
    cout << "42の6桁2進数: " << to_binary_width(42, 6) << endl;
    cout << endl;

    // 例4: ビット操作
    cout << "例4: ビット操作" << endl;
    long long n = 42; // 101010
    cout << "元の数: " << n << " (2進数: " << to_binary(n) << ")" << endl;
    cout << "ビット数: " << count_bits(n) << endl;
    cout << "最下位ビット位置: " << lowest_bit(n) << endl;
    cout << "最上位ビット位置: " << highest_bit(n) << endl;

    cout << "2番目のビット: " << get_bit(n, 2) << endl;
    set_bit(n, 0);
    cout << "0番目ビットをセット: " << to_binary(n) << endl;
    clear_bit(n, 3);
    cout << "3番目ビットをクリア: " << to_binary(n) << endl;
    toggle_bit(n, 2);
    cout << "2番目ビットをトグル: " << to_binary(n) << endl;
    cout << endl;

    // 例5: 負数の扱い
    cout << "例5: 負数の扱い" << endl;
    long long neg = -42;
    cout << "負数 " << neg << " の16進数: " << to_hex(neg) << endl;
    cout << "負数 " << neg << " の2進数: " << to_binary(neg) << endl;
    cout << "-FF (16進数) -> " << from_hex("-FF") << endl;
    cout << endl;

    // 例6: 実用的な応用例
    cout << "例6: RGB色の変換" << endl;
    int r = 255, g = 128, b = 64;
    long long rgb = (r << 16) | (g << 8) | b;
    cout << "RGB(" << r << ", " << g << ", " << b << ") -> #" << to_hex(rgb) << endl;

    string hex_color = "FF8040";
    long long color = from_hex(hex_color);
    int r2 = (color >> 16) & 0xFF;
    int g2 = (color >> 8) & 0xFF;
    int b2 = color & 0xFF;
    cout << "#" << hex_color << " -> RGB(" << r2 << ", " << g2 << ", " << b2 << ")" << endl;

    return 0;
}