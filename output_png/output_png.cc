#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void saveGradientImage(const vector<vector<int>> &array, const char *filename) {
    // 画像の高さと幅を取得
    int height = array.size();
    int width = array[0].size();

    // 画像のデータを格納するバッファを作成
    vector<uint8_t> imageData(height * width * 3); // RGB カラーなので *3

    // グラデーションの計算
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int value = array[y][x];
            if (value < 0)
                value = 0;
            if (value > 100)
                value = 100;

            // 赤から緑へのグラデーション
            uint8_t red = (100 - value) * 255 / 100; // 0 -> 255
            uint8_t green = 0;                       // 0 -> 255
            uint8_t blue = value * 255 / 100;

            // 画像データにピクセル値を設定
            int index = (y * width + x) * 3;
            imageData[index] = red;
            imageData[index + 1] = green;
            imageData[index + 2] = blue;
        }
    }

    // 画像ファイルを保存
    stbi_write_png(filename, width, height, 3, imageData.data(), width * 3);
}

int main() {
    // ファイルの名前を指定
    const char *filename = "input.txt";

    // ファイルを開く
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ファイルを開けませんでした: " << filename << endl;
        return 1;
    }

    // 高さ(h)と幅(w)を読み取る
    int h, w;
    file >> h >> w;

    // 2次元配列を作成
    vector<vector<int>> array(h, vector<int>(w));

    // 2次元配列をファイルから読み取る
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            file >> array[y][x];
        }
    }

    // ファイルを閉じる
    file.close();

    saveGradientImage(array, "output.png");

    return 0;
}
