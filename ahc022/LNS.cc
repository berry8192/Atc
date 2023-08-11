#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(){
    std::ofstream outputFile("log.csv", std::ios::app);

    int l, n, s;
    cin>> l >> n >> s;
    outputFile<< l << ", " << n << ", " << s <<endl;

    outputFile.close();

    return 0;
}

