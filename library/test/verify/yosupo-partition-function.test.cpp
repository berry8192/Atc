#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fps/formal-power-series-friendly-ntt.cpp"
#include "../../math/fps/partition.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  cout << partition< FPS, mint >(N) << endl;
}

