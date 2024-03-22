#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main() {
    std::ofstream outputFile("log.csv", std::ios::app);

    int W, D, N;
    cin >> W >> D >> N;
    outputFile << W << ", " << D << ", " << N << endl;

    outputFile.close();

    return 0;
}
