#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // 画像を書き出すために追加

const int STAGE_HEIGHT = 9; // ステージの高さ
const int STAGE_WIDTH = 12; // ステージの幅
const int CELL_SIZE = 15;   // 各マスのサイズ
const int OFFSET = 5;       // 画像の上下左右のオフセット

// ユークリッド距離を計算する関数
double calculateDistance(int x, int y) {
    return std::sqrt(std::pow(x - 7, 2) + std::pow(y - 7, 2));
}

// 画像を読み込む関数
std::vector<unsigned char> loadImage(const std::string &imagePath, int &width,
                                     int &height, int &channels) {
    unsigned char *imgData =
        stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (!imgData) {
        std::cerr << "Error: Could not open or find the image! Path: "
                  << imagePath << std::endl;
        return {};
    }

    std::vector<unsigned char> data(imgData,
                                    imgData + (width * height * channels));
    stbi_image_free(imgData);
    return data;
}

// 画像を書き出す関数
void saveImage(const std::string &outputPath, unsigned char *data, int width,
               int height) {
    // 画像データはRGB形式で保存
    stbi_write_png(outputPath.c_str(), width, height, 3, data, width * 3);
}

// 色の差を計算する関数
void calculateColorDifference(const unsigned char *cellRGB,
                              const unsigned char *sourceRGB,
                              unsigned char *outputRGB) {
    for (int i = 0; i < CELL_SIZE * CELL_SIZE; ++i) {
        int index = i * 3; // RGBのインデックス
        outputRGB[index + 0] =
            std::abs(cellRGB[index + 0] - sourceRGB[index + 0]); // R
        outputRGB[index + 1] =
            std::abs(cellRGB[index + 1] - sourceRGB[index + 1]); // G
        outputRGB[index + 2] =
            std::abs(cellRGB[index + 2] - sourceRGB[index + 2]); // B
    }
}

void extractStageData(const std::string &imagePath,
                      const std::string &outputPath,
                      const std::string &sourceDir) {
    int width, height, channels;

    // ステージ画像を読み込む
    unsigned char *stageData =
        stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (!stageData) {
        std::cerr << "Error: Could not open or find the stage image! Path: "
                  << imagePath << std::endl;
        return;
    }

    // 出力用のマスの状態を保存するベクトル
    std::vector<std::string> cellStates(STAGE_HEIGHT * STAGE_WIDTH);

    // ソース画像の読み込み
    std::vector<std::string> sourceImages;
    std::vector<std::vector<unsigned char>> sourceRGBs;

    for (const auto &entry : std::filesystem::directory_iterator(sourceDir)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            int sourceWidth, sourceHeight, sourceChannels;
            auto rgbData =
                loadImage(filePath, sourceWidth, sourceHeight, sourceChannels);
            if (!rgbData.empty()) {
                // 拡張子を除いたファイル名を追加
                sourceImages.push_back(
                    entry.path().filename().replace_extension("").string());
                sourceRGBs.push_back(std::move(rgbData));
            }
        }
    }

    // 各マスのRGB値を取得する
    for (int i = 0; i < STAGE_HEIGHT; ++i) {
        for (int j = 0; j < STAGE_WIDTH; ++j) {
            unsigned char cellRGB[CELL_SIZE * CELL_SIZE * 3];

            // マスのRGB値を取得
            for (int x = 0; x < CELL_SIZE; ++x) {
                for (int y = 0; y < CELL_SIZE; ++y) {
                    int index = ((OFFSET + i * CELL_SIZE + x) * width +
                                 (OFFSET + j * CELL_SIZE + y)) *
                                channels;
                    int cellIndex =
                        (x * CELL_SIZE + y) * 3; // 3つのチャンネル (R, G, B)
                    cellRGB[cellIndex + 0] = stageData[index + 0]; // R
                    cellRGB[cellIndex + 1] = stageData[index + 1]; // G
                    cellRGB[cellIndex + 2] = stageData[index + 2]; // B
                }
            }

            // 最小誤差の初期化
            double minError = std::numeric_limits<double>::max();
            std::string bestMatch;
            unsigned char colorDifference[CELL_SIZE * CELL_SIZE *
                                          3]; // 色差を保存する配列

            // 各ソース画像との誤差を計算
            for (size_t k = 0; k < sourceRGBs.size(); ++k) {
                // 色の差を計算
                calculateColorDifference(cellRGB, sourceRGBs[k].data(),
                                         colorDifference);

                double error = 0.0;
                // 各ピクセルに対して、距離に基づいた重み付けを行う
                for (int x = 0; x < CELL_SIZE; ++x) {
                    for (int y = 0; y < CELL_SIZE; ++y) {
                        int index = (x * CELL_SIZE + y) * 3;
                        double distance = calculateDistance(x, y);
                        double weight =
                            1.0 /
                            (1.0 + distance); // 距離が大きいほど重みを小さく

                        // 各チャンネルの色差の平方和をエラーに加算
                        error +=
                            weight * (std::pow(colorDifference[index + 0], 2) +
                                      std::pow(colorDifference[index + 1], 2) +
                                      std::pow(colorDifference[index + 2], 2));
                    }
                }

                if (error < minError) {
                    minError = error;
                    bestMatch =
                        sourceImages[k]; // 拡張子を除いたファイル名を記録
                }
            }

            // マスの状態を記録
            cellStates[i * STAGE_WIDTH + j] = bestMatch;
        }
    }

    // 結果をテキストファイルに書き出す
    std::ofstream outFile(outputPath);
    if (!outFile) {
        std::cerr << "Error: Could not open the output file!" << std::endl;
        return;
    }

    // 各マスの状態を出力
    int row_count = 0;
    for (const auto &state : cellStates) {
        outFile << state;
        row_count++;
        if (row_count % STAGE_WIDTH == 0) {
            outFile << std::endl;
        }
    }

    outFile.close();
    std::cout << "Cell states have been written to " << outputPath << std::endl;

    // メモリ解放
    stbi_image_free(stageData);
}

int main() {
    std::string imagePath =
        "./txtToPng/chochorocket/ccrm03.png";    // ステージ画像のパス
    std::string outputPath = "stage_states.txt"; // 出力ファイルのパス
    std::string sourceDir = "./txtToPng/source"; // ソース画像のディレクトリ

    extractStageData(imagePath, outputPath, sourceDir);

    return 0;
}
