// BigInt 多倍長整数 大きな整数 四則演算 文字列変換

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// ========== ライブラリ部分 ==========

// 多倍長整数クラス
class BigInt {
private:
    vector<int> digits;
    bool negative;
    static const int BASE = 10000;  // 各桁の基数
    static const int DIGITS_PER_ELEMENT = 4;  // 各要素が表現する桁数

    // 先頭の0を削除
    void remove_leading_zeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.size() == 1 && digits[0] == 0) {
            negative = false;
        }
    }

    // 絶対値の比較
    int compare_abs(const BigInt& other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() < other.digits.size() ? -1 : 1;
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] < other.digits[i] ? -1 : 1;
            }
        }
        return 0;
    }

    // 絶対値の加算
    BigInt add_abs(const BigInt& other) const {
        BigInt result;
        result.digits.clear();
        result.negative = false;

        int carry = 0;
        int max_size = max(digits.size(), other.digits.size());

        for (int i = 0; i < max_size || carry; i++) {
            int sum = carry;
            if (i < (int)digits.size()) sum += digits[i];
            if (i < (int)other.digits.size()) sum += other.digits[i];

            result.digits.push_back(sum % BASE);
            carry = sum / BASE;
        }

        return result;
    }

    // 絶対値の減算（this >= other を仮定）
    BigInt subtract_abs(const BigInt& other) const {
        BigInt result;
        result.digits.clear();
        result.negative = false;

        int borrow = 0;
        for (int i = 0; i < (int)digits.size(); i++) {
            int diff = digits[i] - borrow;
            if (i < (int)other.digits.size()) {
                diff -= other.digits[i];
            }

            if (diff < 0) {
                diff += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.digits.push_back(diff);
        }

        result.remove_leading_zeros();
        return result;
    }

public:
    // コンストラクタ
    BigInt() : negative(false) {
        digits.push_back(0);
    }

    BigInt(long long num) : negative(num < 0) {
        if (negative) num = -num;
        if (num == 0) {
            digits.push_back(0);
        } else {
            while (num > 0) {
                digits.push_back(num % BASE);
                num /= BASE;
            }
        }
    }

    BigInt(const string& s) : negative(false) {
        string str = s;
        if (!str.empty() && str[0] == '-') {
            negative = true;
            str = str.substr(1);
        } else if (!str.empty() && str[0] == '+') {
            str = str.substr(1);
        }

        if (str.empty()) {
            digits.push_back(0);
            return;
        }

        digits.clear();
        for (int i = str.length(); i > 0; i -= DIGITS_PER_ELEMENT) {
            int start = max(0, i - DIGITS_PER_ELEMENT);
            int len = i - start;
            string substr = str.substr(start, len);
            digits.push_back(stoi(substr));
        }

        remove_leading_zeros();
    }

    // 符号反転
    BigInt operator-() const {
        BigInt result = *this;
        if (!is_zero()) {
            result.negative = !result.negative;
        }
        return result;
    }

    // 加算
    BigInt operator+(const BigInt& other) const {
        if (negative == other.negative) {
            BigInt result = add_abs(other);
            result.negative = negative;
            return result;
        } else {
            int cmp = compare_abs(other);
            if (cmp == 0) return BigInt(0);

            BigInt result;
            if (cmp > 0) {
                result = subtract_abs(other);
                result.negative = negative;
            } else {
                result = other.subtract_abs(*this);
                result.negative = other.negative;
            }
            return result;
        }
    }

    // 減算
    BigInt operator-(const BigInt& other) const {
        return *this + (-other);
    }

    // 乗算
    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.assign(digits.size() + other.digits.size(), 0);
        result.negative = negative != other.negative;

        for (int i = 0; i < (int)digits.size(); i++) {
            long long carry = 0;
            for (int j = 0; j < (int)other.digits.size() || carry; j++) {
                long long prod = result.digits[i + j] + carry;
                if (j < (int)other.digits.size()) {
                    prod += (long long)digits[i] * other.digits[j];
                }

                result.digits[i + j] = prod % BASE;
                carry = prod / BASE;
            }
        }

        result.remove_leading_zeros();
        return result;
    }

    // 除算（整数除算）
    BigInt operator/(const BigInt& divisor) const {
        if (divisor.is_zero()) {
            throw invalid_argument("Division by zero");
        }

        if (compare_abs(divisor) < 0) return BigInt(0);

        BigInt result;
        result.digits.clear();
        result.negative = negative != divisor.negative;

        BigInt current;
        for (int i = digits.size() - 1; i >= 0; i--) {
            current = current * BASE + digits[i];

            int quotient = 0;
            while (current.compare_abs(divisor) >= 0) {
                current = current - divisor.abs();
                quotient++;
            }

            result.digits.push_back(quotient);
        }

        reverse(result.digits.begin(), result.digits.end());
        result.remove_leading_zeros();
        return result;
    }

    // 剰余
    BigInt operator%(const BigInt& divisor) const {
        return *this - (*this / divisor) * divisor;
    }

    // 比較演算子
    bool operator==(const BigInt& other) const {
        return negative == other.negative && digits == other.digits;
    }

    bool operator!=(const BigInt& other) const {
        return !(*this == other);
    }

    bool operator<(const BigInt& other) const {
        if (negative != other.negative) {
            return negative;
        }

        int cmp = compare_abs(other);
        return negative ? cmp > 0 : cmp < 0;
    }

    bool operator<=(const BigInt& other) const {
        return *this < other || *this == other;
    }

    bool operator>(const BigInt& other) const {
        return !(*this <= other);
    }

    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    }

    // 代入演算子
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        *this = *this - other;
        return *this;
    }

    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    BigInt& operator/=(const BigInt& other) {
        *this = *this / other;
        return *this;
    }

    BigInt& operator%=(const BigInt& other) {
        *this = *this % other;
        return *this;
    }

    // ユーティリティ関数
    bool is_zero() const {
        return digits.size() == 1 && digits[0] == 0;
    }

    bool is_positive() const {
        return !negative && !is_zero();
    }

    bool is_negative() const {
        return negative;
    }

    BigInt abs() const {
        BigInt result = *this;
        result.negative = false;
        return result;
    }

    // べき乗
    BigInt power(int exp) const {
        if (exp < 0) throw invalid_argument("Negative exponent not supported");
        if (exp == 0) return BigInt(1);

        BigInt result(1);
        BigInt base = *this;

        while (exp > 0) {
            if (exp & 1) {
                result *= base;
            }
            base *= base;
            exp >>= 1;
        }

        return result;
    }

    // 文字列変換
    string to_string() const {
        if (is_zero()) return "0";

        string result;
        if (negative) result += "-";

        for (int i = digits.size() - 1; i >= 0; i--) {
            if (i == (int)digits.size() - 1) {
                result += std::to_string(digits[i]);
            } else {
                result += string(DIGITS_PER_ELEMENT - std::to_string(digits[i]).length(), '0');
                result += std::to_string(digits[i]);
            }
        }

        return result;
    }

    // 最大公約数
    static BigInt gcd(BigInt a, BigInt b) {
        a = a.abs();
        b = b.abs();
        while (!b.is_zero()) {
            BigInt temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // 最小公倍数
    static BigInt lcm(const BigInt& a, const BigInt& b) {
        return (a * b).abs() / gcd(a, b);
    }
};

// 出力演算子
ostream& operator<<(ostream& os, const BigInt& bi) {
    os << bi.to_string();
    return os;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な四則演算
    cout << "例1: 基本的な四則演算" << endl;
    BigInt a("123456789012345678901234567890");
    BigInt b("987654321098765432109876543210");

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << endl;

    // 例2: 大きな数での計算
    cout << "例2: 大きな数での計算" << endl;
    BigInt factorial(1);
    int n = 50;

    for (int i = 1; i <= n; i++) {
        factorial *= BigInt(i);
    }

    cout << n << "! = " << factorial << endl;
    cout << "桁数: " << factorial.to_string().length() << endl;
    cout << endl;

    // 例3: フィボナッチ数列
    cout << "例3: フィボナッチ数列" << endl;
    vector<BigInt> fib = {BigInt(0), BigInt(1)};

    for (int i = 2; i <= 100; i++) {
        fib.push_back(fib[i-1] + fib[i-2]);
    }

    cout << "フィボナッチ数列の最初の20項:" << endl;
    for (int i = 0; i < 20; i++) {
        cout << "F(" << i << ") = " << fib[i] << endl;
    }

    cout << "F(100) = " << fib[100] << endl;
    cout << "F(100)の桁数: " << fib[100].to_string().length() << endl;
    cout << endl;

    // 例4: べき乗計算
    cout << "例4: べき乗計算" << endl;
    BigInt base(2);
    vector<int> exponents = {10, 50, 100, 200};

    for (int exp : exponents) {
        BigInt result = base.power(exp);
        cout << "2^" << exp << " = " << result << endl;
        cout << "桁数: " << result.to_string().length() << endl;
    }
    cout << endl;

    // 例5: 除算と剰余
    cout << "例5: 除算と剰余" << endl;
    BigInt dividend("12345678901234567890");
    BigInt divisor("123456789");

    cout << "被除数: " << dividend << endl;
    cout << "除数: " << divisor << endl;
    cout << "商: " << dividend / divisor << endl;
    cout << "余り: " << dividend % divisor << endl;
    cout << "検証: " << (dividend / divisor) * divisor + (dividend % divisor) << endl;
    cout << endl;

    // 例6: 比較演算
    cout << "例6: 比較演算" << endl;
    BigInt x("999999999999999999999");
    BigInt y("1000000000000000000000");

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "x < y: " << (x < y ? "true" : "false") << endl;
    cout << "x == y: " << (x == y ? "true" : "false") << endl;
    cout << "x + 1 == y: " << ((x + BigInt(1)) == y ? "true" : "false") << endl;
    cout << endl;

    // 例7: 最大公約数と最小公倍数
    cout << "例7: 最大公約数と最小公倍数" << endl;
    BigInt num1("123456789012345");
    BigInt num2("987654321098765");

    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "GCD = " << BigInt::gcd(num1, num2) << endl;
    cout << "LCM = " << BigInt::lcm(num1, num2) << endl;
    cout << endl;

    // 例8: 負の数の扱い
    cout << "例8: 負の数の扱い" << endl;
    BigInt pos("12345");
    BigInt neg("-67890");

    cout << "pos = " << pos << endl;
    cout << "neg = " << neg << endl;
    cout << "pos + neg = " << pos + neg << endl;
    cout << "pos - neg = " << pos - neg << endl;
    cout << "pos * neg = " << pos * neg << endl;
    cout << "neg.abs() = " << neg.abs() << endl;

    return 0;
}