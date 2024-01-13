#include <gmpxx.h>
#include <iomanip>
#include <iostream>

mpf_class dividePoint(const mpf_class &a, const mpf_class &b, mpf_class n) {
    // a + (b - a) * (1/n)
    mpf_class result = a + (b - a) / n;
    return result;
}

void zoomRectangle(const mpf_class &minX, const mpf_class &maxX,
                   const mpf_class &minY, const mpf_class &maxY,
                   const mpf_class imageWidth, const mpf_class imageHeight,
                   const mpf_class objX, const mpf_class objY,
                   const mpf_class &objZ, mpf_class &zoomedMinX,
                   mpf_class &zoomedMaxX, mpf_class &zoomedMinY,
                   mpf_class &zoomedMaxY) {

    // ズーム前の幅と高さを計算
    mpf_class width = maxX - minX;
    mpf_class height = maxY - minY;
    // std::cout << width << std::endl;
    // std::cout << height << std::endl;

    // ズーム後の中心座標を計算
    mpf_class zoomedCenterX = minX + width * (objX / imageWidth);
    mpf_class zoomedCenterY = minY + height * (objY / imageHeight);
    // std::cout << zoomedCenterX << std::endl;
    // std::cout << zoomedCenterY << std::endl;

    // // ズーム後の幅と高さを計算
    // mpf_class zoomedWidth = width / objZ;
    // mpf_class zoomedHeight = height / objZ;

    // ズーム後の領域の座標を計算
    zoomedMinX = dividePoint(zoomedCenterX, minX, objZ);
    zoomedMaxX = dividePoint(zoomedCenterX, maxX, objZ);
    zoomedMinY = dividePoint(zoomedCenterY, minY, objZ);
    zoomedMaxY = dividePoint(zoomedCenterY, maxY, objZ);
}

int main() {
    std::cout << std::fixed << std::setprecision(24);
    mpf_set_default_prec(1024);
    // 画像の幅と高さを受け取る
    mpf_class imageWidth, imageHeight;
    // std::cin >> imageWidth >> imageHeight;
    imageWidth = 3940;
    imageHeight = 2160;

    // minX, maxX, minY, maxYを標準入力から受け取る
    mpf_class minX, maxX, minY, maxY;
    std::cin >> minX >> maxX >> minY >> maxY;

    // objX, objY, objZを標準入力から受け取る
    mpf_class objX, objY;
    mpf_class objZ;
    std::cin >> objX >> objY >> objZ;

    // ズーム後の座標を計算
    mpf_class zoomedMinX, zoomedMaxX, zoomedMinY, zoomedMaxY;
    zoomRectangle(minX, maxX, minY, maxY, imageWidth, imageHeight, objX, objY,
                  objZ, zoomedMinX, zoomedMaxX, zoomedMinY, zoomedMaxY);

    // 結果の出力
    std::cout << "Zoomed Rectangle Coordinates:" << std::endl;
    std::cout << "std::string strMinX = " << '"' << zoomedMinX << '"' << ";"
              << std::endl;
    std::cout << "std::string strMaxX = " << '"' << zoomedMaxX << '"' << ";"
              << std::endl;
    std::cout << "std::string strMinY = " << '"' << zoomedMinY << '"' << ";"
              << std::endl;
    std::cout << "std::string strMaxY = " << '"' << zoomedMaxY << '"' << ";"
              << std::endl;

    return 0;
}
