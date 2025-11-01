// Fraction 分数 有理数 既約分数 四則演算

#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
using namespace std;

// ========== ライブラリ部分 ==========

// 分数クラス
class Fraction {
private:
    long long num, den;  // 分子、分母

    // 最大公約数
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    // 約分
    void reduce() {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }

        long long g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;

        // 分母を正にする
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

public:
    // コンストラクタ
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        reduce();
    }

    // 文字列から分数を作成 ("3/4", "5", "-2/3" など)
    Fraction(const string& s) {
        size_t slash_pos = s.find('/');
        if (slash_pos == string::npos) {
            num = stoll(s);
            den = 1;
        } else {
            num = stoll(s.substr(0, slash_pos));
            den = stoll(s.substr(slash_pos + 1));
        }
        reduce();
    }

    // アクセサ
    long long numerator() const { return num; }
    long long denominator() const { return den; }

    // double型への変換
    double to_double() const {
        return static_cast<double>(num) / den;
    }

    // 文字列表現
    string to_string() const {
        if (den == 1) {
            return std::to_string(num);
        } else {
            return std::to_string(num) + "/" + std::to_string(den);
        }
    }

    // 四則演算
    Fraction operator+(const Fraction& other) const {
        return Fraction(num * other.den + other.num * den, den * other.den);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(num * other.den - other.num * den, den * other.den);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(num * other.num, den * other.den);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.num == 0) {
            throw invalid_argument("Division by zero");
        }
        return Fraction(num * other.den, den * other.num);
    }

    // 単項演算子
    Fraction operator-() const {
        return Fraction(-num, den);
    }

    Fraction operator+() const {
        return *this;
    }

    // 比較演算子
    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return num * other.den < other.num * den;
    }

    bool operator<=(const Fraction& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Fraction& other) const {
        return !(*this <= other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }

    // 代入演算子
    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        *this = *this - other;
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        *this = *this * other;
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        *this = *this / other;
        return *this;
    }

    // 整数との演算
    Fraction operator+(long long n) const {
        return *this + Fraction(n);
    }

    Fraction operator-(long long n) const {
        return *this - Fraction(n);
    }

    Fraction operator*(long long n) const {
        return Fraction(num * n, den);
    }

    Fraction operator/(long long n) const {
        return Fraction(num, den * n);
    }

    // 絶対値
    Fraction abs() const {
        return Fraction(::abs(num), den);
    }

    // 逆数
    Fraction reciprocal() const {
        if (num == 0) {
            throw invalid_argument("Cannot take reciprocal of zero");
        }
        return Fraction(den, num);
    }

    // べき乗（整数乗のみ）
    Fraction power(int exp) const {
        if (exp == 0) return Fraction(1);
        if (exp < 0) return reciprocal().power(-exp);

        Fraction result(1);
        Fraction base = *this;
        while (exp > 0) {
            if (exp & 1) result *= base;
            base *= base;
            exp >>= 1;
        }
        return result;
    }

    // 帯分数表現 (整数部分, 分子, 分母)
    tuple<long long, long long, long long> to_mixed() const {
        long long integer_part = num / den;
        long long remainder = num % den;
        return {integer_part, remainder, den};
    }

    // ゼロ判定
    bool is_zero() const {
        return num == 0;
    }

    // 正の判定
    bool is_positive() const {
        return num > 0;
    }

    // 負の判定
    bool is_negative() const {
        return num < 0;
    }

    // 整数判定
    bool is_integer() const {
        return den == 1;
    }
};

// 外部演算子（整数 op 分数）
Fraction operator+(long long n, const Fraction& f) {
    return Fraction(n) + f;
}

Fraction operator-(long long n, const Fraction& f) {
    return Fraction(n) - f;
}

Fraction operator*(long long n, const Fraction& f) {
    return f * n;
}

Fraction operator/(long long n, const Fraction& f) {
    return Fraction(n) / f;
}

// 出力演算子
ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.to_string();
    return os;
}

// 連分数展開
vector<long long> continued_fraction(Fraction f) {
    vector<long long> result;
    f = f.abs();  // 正の値にする

    while (!f.is_zero() && f.denominator() != 1) {
        long long integer_part = f.numerator() / f.denominator();
        result.push_back(integer_part);
        f = f - integer_part;
        if (!f.is_zero()) {
            f = f.reciprocal();
        }
    }

    if (f.is_integer() && !f.is_zero()) {
        result.push_back(f.numerator());
    }

    return result;
}

// 連分数から分数を復元
Fraction from_continued_fraction(const vector<long long>& cf) {
    if (cf.empty()) return Fraction(0);

    Fraction result(cf.back());
    for (int i = cf.size() - 2; i >= 0; i--) {
        result = result.reciprocal() + cf[i];
    }
    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な分数の操作
    cout << "例1: 基本的な分数の操作" << endl;
    Fraction a(3, 4);
    Fraction b(2, 5);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
    cout << "a の double値 = " << a.to_double() << endl;
    cout << endl;

    // 例2: 約分の確認
    cout << "例2: 約分の確認" << endl;
    Fraction c(6, 8);
    Fraction d(15, 25);

    cout << "6/8 = " << c << endl;
    cout << "15/25 = " << d << endl;
    cout << "6/8 + 15/25 = " << c + d << endl;
    cout << endl;

    // 例3: 整数との演算
    cout << "例3: 整数との演算" << endl;
    Fraction e(7, 3);

    cout << "e = " << e << endl;
    cout << "e + 2 = " << e + 2 << endl;
    cout << "e * 3 = " << e * 3 << endl;
    cout << "5 - e = " << 5 - e << endl;
    cout << endl;

    // 例4: 比較演算
    cout << "例4: 比較演算" << endl;
    Fraction f1(1, 2);
    Fraction f2(3, 6);
    Fraction f3(2, 3);

    cout << "1/2 = " << f1 << ", 3/6 = " << f2 << ", 2/3 = " << f3 << endl;
    cout << "1/2 == 3/6: " << (f1 == f2 ? "true" : "false") << endl;
    cout << "1/2 < 2/3: " << (f1 < f3 ? "true" : "false") << endl;
    cout << "2/3 > 1/2: " << (f3 > f1 ? "true" : "false") << endl;
    cout << endl;

    // 例5: べき乗と逆数
    cout << "例5: べき乗と逆数" << endl;
    Fraction g(2, 3);

    cout << "g = " << g << endl;
    cout << "g^2 = " << g.power(2) << endl;
    cout << "g^3 = " << g.power(3) << endl;
    cout << "g^(-1) = " << g.reciprocal() << endl;
    cout << "g^(-2) = " << g.power(-2) << endl;
    cout << endl;

    // 例6: 帯分数表現
    cout << "例6: 帯分数表現" << endl;
    Fraction h(22, 7);

    cout << "22/7 = " << h << endl;
    auto [integer, numerator, denominator] = h.to_mixed();
    cout << "帯分数: " << integer << " と " << numerator << "/" << denominator << endl;
    cout << "小数値: " << h.to_double() << endl;
    cout << endl;

    // 例7: 文字列からの作成
    cout << "例7: 文字列からの作成" << endl;
    vector<string> fraction_strings = {"3/4", "5", "-7/8", "0", "10/5"};

    for (const string& s : fraction_strings) {
        Fraction frac(s);
        cout << "\"" << s << "\" -> " << frac << " (double: " << frac.to_double() << ")" << endl;
    }
    cout << endl;

    // 例8: 連分数展開
    cout << "例8: 連分数展開" << endl;
    vector<Fraction> test_fractions = {Fraction(22, 7), Fraction(355, 113), Fraction(8, 5)};

    for (const Fraction& frac : test_fractions) {
        auto cf = continued_fraction(frac);
        cout << frac << " の連分数展開: [";
        for (int i = 0; i < (int)cf.size(); i++) {
            if (i > 0) cout << ", ";
            cout << cf[i];
        }
        cout << "]" << endl;

        // 復元確認
        Fraction restored = from_continued_fraction(cf);
        cout << "復元: " << restored << endl;
        cout << endl;
    }

    // 例9: 分数の配列での計算
    cout << "例9: 分数の配列での計算" << endl;
    vector<Fraction> fractions = {Fraction(1, 2), Fraction(1, 3), Fraction(1, 4), Fraction(1, 6)};

    cout << "分数配列: ";
    for (const Fraction& frac : fractions) {
        cout << frac << " ";
    }
    cout << endl;

    Fraction sum(0);
    for (const Fraction& frac : fractions) {
        sum += frac;
    }
    cout << "合計: " << sum << " (= " << sum.to_double() << ")" << endl;

    Fraction product(1);
    for (const Fraction& frac : fractions) {
        product *= frac;
    }
    cout << "積: " << product << " (= " << product.to_double() << ")" << endl;

    return 0;
}