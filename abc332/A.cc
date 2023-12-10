#include <iostream>

int main() {
    // 商品の種類数 N, 送料の条件 S, 送料 K
    int N, S, K;
    std::cin >> N >> S >> K;

    int totalCost = 0;  // 商品の合計金額

    // 各商品の価格 Pi と数量 Qi を読み込み、合計金額を計算
    for (int i = 0; i < N; ++i) {
        int Pi, Qi;
        std::cin >> Pi >> Qi;
        totalCost += Pi * Qi;
    }

    // 送料を考慮した支払い金額を計算
    int finalCost = (totalCost >= S) ? totalCost : (totalCost + K);

    // 結果を出力
    std::cout << finalCost << std::endl;

    return 0;
}
