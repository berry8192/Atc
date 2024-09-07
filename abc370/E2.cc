#include <atcoder/all>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace atcoder;
using mint = modint998244353;

mint count_partitions_not_sum_k(const vector<int> &A, int N, long long K) {
    // 累積和を管理する変数
    long long prefix_sum = 0;
    // 累積和の出現回数を記録するハッシュマップ
    unordered_map<long long, long long> prefix_count;
    // 初期値として、累積和が0のパターンを1として設定
    prefix_count[0] = 1;
    // 和がKになる部分列の数をカウントする変数
    mint count = 0;

    for (int i = 0; i < N; ++i) {
        // 現在の累積和を計算
        prefix_sum += A[i];

        // 「累積和がKとなる部分列」が存在するか確認
        if (prefix_count.find(prefix_sum - K) != prefix_count.end()) {
            count += prefix_count[prefix_sum - K];
        }

        // 現在の累積和の出現回数を更新
        prefix_count[prefix_sum]++;
    }

    // 結果として、和がKにならない分割方法の数を返す
    return count;
}

int main() {
    // 入力例
    int N, K;
    vector<int> A;

    cin >> N >> K;
    A.resize(N);

    for (int i = 0; i < N; i++)
        cin >> A[i];
    // 関数呼び出し
    mint result = count_partitions_not_sum_k(A, N, K);
    mint tw = 1;
    for (int i = 0; i < N - 1; i++)
        tw *= 2;
    // 結果の出力
    cout << (tw - result).val() << endl;

    return 0;
}
