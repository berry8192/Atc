// 有理数 rational 分数 fraction 既約分数

#include <iostream>
#include <numeric>
using namespace std;

// ========== ライブラリ本体 ==========

// 有理数クラス
template<typename T = long long>
struct Rational {
    T num, den;  // 分子、分母

    Rational(T n = 0, T d = 1) : num(n), den(d) {
        if (den == 0) {
            throw runtime_error("Division by zero");
        }
        normalize();
    }

    // 正規化（既約分数にする）
    void normalize() {
        if (den < 0) {
            num = -num;
            den = -den;
        }
        T g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;
    }

    // 四則演算
    Rational operator+(const Rational& r) const {
        return Rational(num * r.den + r.num * den, den * r.den);
    }

    Rational operator-(const Rational& r) const {
        return Rational(num * r.den - r.num * den, den * r.den);
    }

    Rational operator*(const Rational& r) const {
        return Rational(num * r.num, den * r.den);
    }

    Rational operator/(const Rational& r) const {
        return Rational(num * r.den, den * r.num);
    }

    Rational& operator+=(const Rational& r) {
        *this = *this + r;
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        *this = *this - r;
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        *this = *this * r;
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        *this = *this / r;
        return *this;
    }

    // 比較演算
    bool operator==(const Rational& r) const {
        return num * r.den == r.num * den;
    }

    bool operator!=(const Rational& r) const {
        return !(*this == r);
    }

    bool operator<(const Rational& r) const {
        return num * r.den < r.num * den;
    }

    bool operator<=(const Rational& r) const {
        return *this < r || *this == r;
    }

    bool operator>(const Rational& r) const {
        return r < *this;
    }

    bool operator>=(const Rational& r) const {
        return !(*this < r);
    }

    // 単項演算
    Rational operator-() const {
        return Rational(-num, den);
    }

    Rational operator+() const {
        return *this;
    }

    // 型変換
    double to_double() const {
        return (double)num / den;
    }

    long double to_long_double() const {
        return (long double)num / den;
    }

    // 逆数
    Rational inv() const {
        return Rational(den, num);
    }

    // 絶対値
    Rational abs() const {
        return Rational(std::abs(num), den);
    }

    // 出力
    friend ostream& operator<<(ostream& os, const Rational& r) {
        if (r.den == 1) {
            os << r.num;
        } else {
            os << r.num << "/" << r.den;
        }
        return os;
    }
};

// 連分数展開
template<typename T>
vector<T> continued_fraction(T num, T den, int max_terms = 20) {
    vector<T> result;

    for (int i = 0; i < max_terms && den != 0; i++) {
        T q = num / den;
        result.push_back(q);

        T tmp = num - q * den;
        num = den;
        den = tmp;
    }

    return result;
}

// 連分数から有理数を復元
template<typename T>
Rational<T> from_continued_fraction(const vector<T>& cf) {
    if (cf.empty()) return Rational<T>(0);

    Rational<T> result(cf.back());

    for (int i = cf.size() - 2; i >= 0; i--) {
        result = Rational<T>(cf[i]) + result.inv();
    }

    return result;
}

// ファレイ数列の生成
template<typename T>
vector<Rational<T>> farey_sequence(T n) {
    vector<Rational<T>> result;

    result.push_back(Rational<T>(0, 1));
    result.push_back(Rational<T>(1, n));

    T a = 0, b = 1, c = 1, d = n;

    while (c <= n) {
        T k = (n + b) / d;
        T tmp_a = a, tmp_b = b;
        a = c;
        b = d;
        c = k * c - tmp_a;
        d = k * d - tmp_b;

        if (c <= n) {
            result.push_back(Rational<T>(a, b));
        }
    }

    result.push_back(Rational<T>(1, 1));

    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な有理数演算
    cout << "例1: 有理数の四則演算" << endl;
    Rational<long long> a(2, 3);  // 2/3
    Rational<long long> b(3, 4);  // 3/4

    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    cout << a << " / " << b << " = " << a / b << endl;
    cout << endl;

    // 例2: 既約分数への自動変換
    cout << "例2: 既約分数への変換" << endl;
    Rational<long long> c(6, 8);  // 6/8 -> 3/4
    Rational<long long> d(15, 25);  // 15/25 -> 3/5
    cout << "6/8 = " << c << endl;
    cout << "15/25 = " << d << endl;
    cout << endl;

    // 例3: 比較演算
    cout << "例3: 比較演算" << endl;
    Rational<long long> x(1, 2);
    Rational<long long> y(2, 3);
    cout << x << " < " << y << " : " << (x < y ? "true" : "false") << endl;
    cout << x << " > " << y << " : " << (x > y ? "true" : "false") << endl;
    cout << endl;

    // 例4: 連分数展開
    cout << "例4: 連分数展開" << endl;
    auto cf = continued_fraction<long long>(355, 113);  // π の近似
    cout << "355/113 の連分数展開: ";
    for (auto val : cf) {
        cout << val << " ";
    }
    cout << endl;

    auto recovered = from_continued_fraction(cf);
    cout << "復元: " << recovered << endl;
    cout << endl;

    // 例5: ファレイ数列
    cout << "例5: ファレイ数列 F(5)" << endl;
    auto farey = farey_sequence<long long>(5);
    for (auto& r : farey) {
        cout << r << " ";
    }
    cout << endl;

    return 0;
}