#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int W, D, N, su = 0;
int a[50][50];

void inpt() {
    cin >> W >> D >> N;

    for (int i = 0; i < D; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
            su += a[i][j];
        }
    }
}

int main() {
    std::ofstream outputFile("log.csv", std::ios::app);

    inpt();

    outputFile << W << ", " << D << ", " << N << ", " << 1.0 * su / D / W / W
               << endl;

    outputFile.close();

    return 0;
}
