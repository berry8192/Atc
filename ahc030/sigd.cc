#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main() {
    std::ofstream outputFile("log.csv", std::ios::app);

    int n, m;
    double eps;
    cin >> n >> m >> eps;
    int dsum = 0;
    for (int i = 0; i < m; i++) {
        int d;
        cin >> d;
        dsum += d;
        for (int j = 0; j < d; j++) {
            int tmp;
            cin >> tmp;
            cin >> tmp;
        }
    }
    outputFile << dsum << endl;

    outputFile.close();

    return 0;
}
