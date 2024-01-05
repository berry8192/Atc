#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> iter_mat;

void createGrayImage(string filename, int width, int height,
                     vector<vector<int>> &iter_mat, int maxIterations) {
    // Allocate memory for image data
    unsigned char *image =
        (unsigned char *)malloc(width * height * 3); // 3 channels (RGB)

    // Generate colored noise
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate the index for the current pixel
            int index = (y * width + x) * 3;
            // white
            image[index] = 255.0 * iter_mat[y][x] / maxIterations;     // Red
            image[index + 1] = 255.0 * iter_mat[y][x] / maxIterations; // Green
            image[index + 2] = 255.0 * iter_mat[y][x] / maxIterations; // Blue
            // Assign random values to RGB channels
            // if (iter_mat[y][x] == 1)
            //     image[index] = 0; // Red
            // if (iter_mat[y][x] >= 1)
            //     image[index + 1] = 0; // Green
            // if (iter_mat[y][x] >= 1)
            //     image[index + 2] = 0; // Blue
        }
    }
    filename += "_gray.png";
    stbi_write_png(filename.c_str(), width, height, 3, image, width * 3);

    // Free allocated memory
    free(image);
}

int main(int argc, char *argv[]) {
    // 引数が足りない場合のエラーチェック
    if (argc != 2) {
        std::cerr << "ファイル名を指定してください。" << std::endl;
        return 1;
    }

    // ファイル名を引数から取得
    std::string fileName = argv[1];

    // ファイルを開く
    ifstream inputFile(fileName);

    // 変数の宣言
    int height, width, maxIterations;
    string strMinX, strMaxX, strMinY, strMaxY;

    if (inputFile.is_open()) {
        // データの読み込み
        inputFile >> height >> width;
        inputFile >> strMinX >> strMaxX >> strMinY >> strMaxY;
        inputFile >> maxIterations;

        // iter_mat の読み込み
        iter_mat.resize(height, vector<int>(width));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                inputFile >> iter_mat[i][j];
            }
        }

        // ファイルを閉じる
        inputFile.close();

        // 読み込んだデータの利用
        // 例えば、読み込んだデータを表示する場合
        // cout << "Height: " << height << endl;
        // cout << "Width: " << width << endl;
        // cout << "strMinX: " << strMinX << " strMaxX: " << strMaxX
        //      << " strMinY: " << strMinY << " strMaxY: " << strMaxY << endl;
        // cout << "Max Iterations: " << maxIterations << endl;
        // cout << "iter_mat:" << endl;
        // for (int i = 0; i < height; i++) {
        //     for (int j = 0; j < width; j++) {
        //         cout << iter_mat[i][j] << " ";
        //     }
        //     cout << endl;
        // }
    } else {
        cerr << "ファイルを開けませんでした。" << endl;
        return 1;
    }

    string fileNameBase = fileName;
    fileNameBase.pop_back();
    fileNameBase.pop_back();
    fileNameBase.pop_back();

    createGrayImage(fileNameBase, width, height, iter_mat, maxIterations);

    return 0;
}
