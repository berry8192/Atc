#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main() {
    std::ofstream outputFile("log.csv", std::ios::app);

    int n, m;
    double eps;
    cin >> n >> m >> eps;
    outputFile << n << ", " << m << ", " << eps << endl;

    outputFile.close();

    return 0;
}
