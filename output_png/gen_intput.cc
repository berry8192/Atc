#include <fstream>
#include <iostream>
#include <random>

using namespace std;

int main() {
    // 指定された高さと幅
    int h, w;
    cout << "高さと幅を入力してください (例: 4 5): ";
    cin >> h >> w;

    // ランダムな整数値の範囲を設定（0から100までの値を生成）
    const int minValue = 0;
    const int maxValue = 100;

    // ランダムな数値生成のためのエンジンと分布を設定
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(minValue, maxValue);

    // ファイルを開く
    ofstream file("input.txt");
    if (!file.is_open()) {
        cerr << "ファイルを開けませんでした: input.txt" << endl;
        return 1;
    }

    // 1行目に高さと幅を出力
    file << h << " " << w << endl;

    // 指定された高さと幅の2次元配列をランダムな整数値で生成し、ファイルに書き込む
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int value = dist(gen); // ランダムな整数値を生成
            file << value;         // ファイルに書き込む
            if (x < w - 1) {
                file << " "; // 幅がまだ続く場合はスペースを追加
            }
        }
        file << endl; // 各行の終わりに改行
    }

    // ファイルを閉じる
    file.close();
    cout << "input.txt ファイルが生成されました。" << endl;

    return 0;
}
