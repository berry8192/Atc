#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <gmpxx.h> // GMP C++ bindings
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> iter_mat;

string getCurrentDateTimeString() {
    // 現在の時刻を取得
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());

    // tm 構造体に変換
    tm tmStruct = *localtime(&now);

    // 文字列に変換
    stringstream ss;
    ss << put_time(&tmStruct, "%Y%m%d%H%M%S");

    return ss.str();
}

void hsvToRgb(double h, double s, double v, double &r, double &g, double &b) {
    double c = v * s;
    double x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
    double m = v - c;

    if (h >= 0 && h < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (h >= 60 && h < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (h >= 180 && h < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (h >= 240 && h < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    r += m;
    g += m;
    b += m;
}

void createMandelbrotImage(const char *filename, int width, int height,
                           double minX, double maxX, double minY, double maxY,
                           int maxIterations) {
    // Allocate memory for image data
    unsigned char *image =
        (unsigned char *)malloc(width * height * 3); // 3 channels (RGB)

    // Set precision for GMP
    mpf_set_default_prec(64); // 64-bit precision, adjust as needed

    // GMP variables for arbitrary precision arithmetic
    mpf_class real, imag, zReal, zImag, newReal, newImag;
    mpf_class two("2.0");
    mpf_class four("4.0");

    // Generate Mandelbrot set
    for (int y = 0; y < height; ++y) {
        if (y % (height / 100) == 0)
            cout << "progress: " << 100 * y / height << "%" << endl;
        // printf("progress: %.1lf%\n", 100.0 * y / height);
        for (int x = 0; x < width; ++x) {
            // Calculate the index for the current pixel
            int index = (y * width + x) * 3;

            // Map pixel coordinates to complex plane using GMP
            real = minX + (maxX - minX) * x / (width - 1);
            imag = minY + (maxY - minY) * y / (height - 1);

            // Mandelbrot set iteration
            zReal = real;
            zImag = imag;
            int iteration = 0;

            while (iteration < maxIterations) {
                mpf_class zRealSquared = zReal * zReal;
                mpf_class zImagSquared = zImag * zImag;

                if (zRealSquared + zImagSquared > four) {
                    break;
                }

                newReal = zRealSquared - zImagSquared + real;
                newImag = two * zReal * zImag + imag;

                zReal = newReal;
                zImag = newImag;

                ++iteration;
            }
            iter_mat[y][x] = iteration;

            // Assign color based on the number of iterations
            double t = static_cast<double>(iteration) / maxIterations;
            unsigned char color = static_cast<unsigned char>(255 * (1 - t));
            // unsigned char color = static_cast<unsigned char>(iteration %
            // 256);

            double r, g, b;
            hsvToRgb(color, 255, color, r, g, b);
            // Assign color to RGB channels
            image[index] = r;     // Red
            image[index + 1] = g; // Green
            image[index + 2] = b; // Blue
        }
    }

    // Save the image to a file
    stbi_write_png(filename, width, height, 3, image, width * 3);

    // Free allocated memory
    free(image);
}

int main() {
    chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();
    int width = 2160;
    int height = 2160;
    // int width = 3840;
    // int height = 2160;
    iter_mat.resize(height, vector<int>(width));

    // Define strings for minX, maxX, minY, maxY
    // edge
    std::string strMinX = "-2";
    std::string strMaxX = "1";
    std::string strMinY = "-1.5";
    std::string strMaxY = "1.5";
    // std::string strMinX = "-0.528543859221658206429780";
    // std::string strMaxX = "-0.528541192554991539763113";
    // std::string strMinY = "-0.669064586805555555555556";
    // std::string strMaxY = "-0.669063086805555555555556";
    // center
    // string strCenterX = "-0.53";
    // string strCenterY = "-0.68";
    // string strWidth = "-0.006";
    // string strHeight = "-0.006";

    // Create mpf_class variables using the defined strings
    mpf_class minX(strMinX);
    mpf_class maxX(strMaxX);
    mpf_class minY(strMinY);
    mpf_class maxY(strMaxY);
    string filename = "mandelbrot_" + strMinX + "_" + strMaxX + "_" + strMinY +
                      "_" + strMaxY + "_" + getCurrentDateTimeString() + ".png";

    ofstream outputFile("mandelbrot_" + strMinX + "_" + strMaxX + "_" +
                            strMinY + "_" + strMaxY + "_" +
                            getCurrentDateTimeString() + ".txt",
                        ios::app);

    int maxIterations = 1000;

    createMandelbrotImage(filename.c_str(), width, height, minX.get_d(),
                          maxX.get_d(), minY.get_d(), maxY.get_d(),
                          maxIterations);

    outputFile << height << " " << width << endl;
    outputFile << strMinX << " " << strMaxX << " " << strMinY << " " << strMaxY
               << endl;
    outputFile << maxIterations << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            outputFile << iter_mat[i][j] << " ";
        }
        outputFile << endl;
    }

    current = chrono::system_clock::now();
    cout << "time: "
         << chrono::duration_cast<chrono::milliseconds>(current - start)
                    .count() /
                1000.0
         << endl;

    return 0;
}

// g++ mandelbrot.cc -lgmp -lgmpxx && ./a.out && mv mandelbrot_*
// /mnt/c/Users/berry/OneDrive/画像/マンデルブロ
