#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int N, T, sigma;

void inpt() { cin >> N >> T >> sigma; }

int main() {
    std::ofstream outputFile("log.csv", std::ios::app);

    inpt();

    outputFile << N << ", " << T << ", " << sigma << endl;

    outputFile.close();

    return 0;
}
