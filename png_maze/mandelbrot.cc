#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <cstdlib>
#include <gmpxx.h> // GMP C++ bindings
#include <iostream>
#include <string>

void hsvToRgb(double h, double s, double v, double &r, double &g, double &b) {
    double c = v * s;
    double x = c * (1 - std::abs(std::fmod(h / 60.0, 2) - 1));
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
        if (y % (height / 10) == 0)
            std::cout << "progress: " << 100 * y / height << "%" << std::endl;
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

            // Assign color based on the number of iterations
            double t = static_cast<double>(iteration) / maxIterations;
            unsigned char color = static_cast<unsigned char>(iteration % 256);

            // Assign color to RGB channels
            image[index] = color;     // Red
            image[index + 1] = color; // Green
            image[index + 2] = color; // Blue
        }
    }

    // Save the image to a file
    stbi_write_png(filename, width, height, 3, image, width * 3);

    // Free allocated memory
    free(image);
}

int main() {
    int width = 800;
    int height = 800;

    // Define strings for minX, maxX, minY, maxY
    // std::string strMinX = "-2.0";
    // std::string strMaxX = "1.0";
    // std::string strMinY = "-1.5";
    // std::string strMaxY = "1.5";
    std::string strMinX = "-0.533";
    std::string strMaxX = "-0.527";
    std::string strMinY = "-0.671";
    std::string strMaxY = "-0.665";

    // Create mpf_class variables using the defined strings
    mpf_class minX(strMinX);
    mpf_class maxX(strMaxX);
    mpf_class minY(strMinY);
    mpf_class maxY(strMaxY);
    std::string filename = "mandelbrot_" + strMinX + "_" + strMaxX + "_" +
                           strMinY + "_" + strMaxY + ".png";

    int maxIterations = 200;

    createMandelbrotImage(filename.c_str(), width, height, minX.get_d(),
                          maxX.get_d(), minY.get_d(), maxY.get_d(),
                          maxIterations);

    return 0;
}

// g++ mandelbrot.cc -lgmp -lgmpxx && ./a.out && mv mandelbrot_*
// /mnt/c/Users/berry/OneDrive/画像/マンデルブロ