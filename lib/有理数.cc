#line 1 "test/verify/yukicoder-1236.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/1236"

#line 1 "template/template.cpp"
#include<bits/stdc++.h>

using namespace std;

using int64 = long long;
const int mod = 1e9 + 7;

const int64 infll = (1LL << 62) - 1;
const int inf = (1 << 30) - 1;

struct IoSetup {
  IoSetup() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cerr << fixed << setprecision(10);
  }
} iosetup;

template< typename T1, typename T2 >
ostream &operator<<(ostream &os, const pair< T1, T2 >& p) {
  os << p.first << " " << p.second;
  return os;
}

template< typename T1, typename T2 >
istream &operator>>(istream &is, pair< T1, T2 > &p) {
  is >> p.first >> p.second;
  return is;
}

template< typename T >
ostream &operator<<(ostream &os, const vector< T > &v) {
  for(int i = 0; i < (int) v.size(); i++) {
    os << v[i] << (i + 1 != v.size() ? " " : "");
  }
  return os;
}

template< typename T >
istream &operator>>(istream &is, vector< T > &v) {
  for(T &in : v) is >> in;
  return is;
}

template< typename T1, typename T2 >
inline bool chmax(T1 &a, T2 b) { return a < b && (a = b, true); }

template< typename T1, typename T2 >
inline bool chmin(T1 &a, T2 b) { return a > b && (a = b, true); }

template< typename T = int64 >
vector< T > make_v(size_t a) {
  return vector< T >(a);
}

template< typename T, typename... Ts >
auto make_v(size_t a, Ts... ts) {
  return vector< decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));
}

template< typename T, typename V >
typename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const V &v) {
  t = v;
}

template< typename T, typename V >
typename enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {
  for(auto &e : t) fill_v(e, v);
}

template< typename F >
struct FixPoint : F {
  explicit FixPoint(F &&f) : F(forward< F >(f)) {}

  template< typename... Args >
  decltype(auto) operator()(Args &&... args) const {
    return F::operator()(*this, forward< Args >(args)...);
  }
};
 
template< typename F >
inline decltype(auto) MFP(F &&f) {
  return FixPoint< F >{forward< F >(f)};
}
#line 4 "test/verify/yukicoder-1236.test.cpp"

#line 1 "math/rational/rational.hpp"
/**
 * @brief Rational (有理数型)
 */
template< typename T >
struct Rational {
private:
  T num, den;

  static T gcd(T a, T b) {
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    return std::__gcd(a, b);
  }

  void normalize() {
    if(num == 0) {
      den = 1;
    } else {
      T g = gcd(num, den);
      num /= g;
      den /= g;
      if(den < 0) {
        num = -num;
        den = -den;
      }
    }
  }

public:

  Rational() : num(0), den(1) {}

  explicit Rational(const T &n) : num(n), den(1) {}

  explicit Rational(const T &n, const T &d) : num(n), den(d) {
    normalize();
  }

  Rational &operator=(const T &n) { return assign(n, 1); }

  Rational &assign(const T &n, const T &d) {
    num = n;
    den = d;
    normalize();
    return *this;
  }

  T numerator() const { return num; }

  T denominator() const { return den; }

  Rational &operator+=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g = gcd(den, r_den);
    den /= g;
    num = num * (r_den / g) + r_num * den;
    g = gcd(num, g);
    num /= g;
    den *= r_den / g;
    return *this;
  }

  Rational &operator-=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g = gcd(den, r_den);
    den /= g;
    num = num * (r_den / g) - r_num * den;
    g = gcd(num, g);
    num /= g;
    den *= r_den / g;
    return *this;
  }

  Rational &operator*=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g1 = gcd(num, r_den);
    T g2 = gcd(den, r_num);
    num = (num / g1) * (r_num / g2);
    den = (den / g2) * (r_den / g1);
    return *this;
  }

  Rational &operator/=(const Rational &r) {
    T r_num = r.num, r_den = r.den;
    T g1 = gcd(num, r_num);
    T g2 = gcd(den, r_den);
    num = (num / g1) * (r_den / g2);
    den = (den / g2) * (r_num / g1);
    if(den < 0) {
      num = -num;
      den = -den;
    }
    return *this;
  }

  Rational &operator+=(const T &i) { return (*this) += Rational{i}; }

  Rational &operator-=(const T &i) { return (*this) -= Rational{i}; }

  Rational &operator*=(const T &i) { return (*this) *= Rational{i}; }

  Rational &operator/=(const T &i) { return (*this) /= Rational{i}; }

  Rational operator+(const Rational &r) const { return Rational(*this) += r; }

  Rational operator-(const Rational &r) const { return Rational(*this) -= r; }

  Rational operator*(const Rational &r) const { return Rational(*this) *= r; }

  Rational operator/(const Rational &r) const { return Rational(*this) /= r; }

  Rational operator+(const T &i) const { return Rational(*this) += i; }

  Rational operator-(const T &i) const { return Rational(*this) -= i; }

  Rational operator*(const T &i) const { return Rational(*this) *= i; }

  Rational operator/(const T &i) const { return Rational(*this) /= i; }

  Rational operator-() const { return Rational{-num, den}; }

  Rational &operator++() {
    num += den;
    return *this;
  }

  Rational &operator--() {
    num -= den;
    return *this;
  }

#define define_cmp(op) \
  bool operator op (const Rational& r) const { return num * r.den op r.num * den; }

  define_cmp(==)

  define_cmp(!=)

  define_cmp(<)

  define_cmp(>)

  define_cmp(<=)

  define_cmp(>=)

#undef define_cmp

  template< typename Real = double >
  Real to_double() const {
    return static_cast < Real >(numerator()) / denominator();
  }

  Rational abs() const {
    return Rational{num < 0 ? -num : num, den};
  }

  friend ostream &operator<<(ostream &os, const Rational &r) {
    return os << r.numerator() << "/" << r.denominator();
  }
};
#line 6 "test/verify/yukicoder-1236.test.cpp"

int main() {
  string s, t;
  cin >> s >> t;
  int a = stoi(s);
  int b = stoi(t);
  using F = Rational< int >;
  F c(a * 60 + b);
  F d(720, 11);
  F x(0);
  while(x < c) x += d;
  x = x - c;
  cout << x.numerator() * 60 / x.denominator() << "\n";
}