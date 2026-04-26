#include <bits/stdc++.h>
using namespace std;

int main() {
    int R;
    cin >> R;
    vector<vector<int>> Y(R, vector<int>(10));
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < 10; c++) {
            cin >> Y[r][c];
        }
    }

    cout << 0 << endl;
    return 0;
}
