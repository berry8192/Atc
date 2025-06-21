#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

int N;
vector<vector<int>> w, d;

void read_input() {
    cin >> N;
    w.assign(N, vector<int>(N));
    d.assign(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> w[i][j];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> d[i][j];
}

string direct_path(pair<int, int> start, pair<int, int> goal) {
    string path = "";
    int x = start.first, y = start.second;
    int gx = goal.first, gy = goal.second;
    while (x < gx) {
        path += 'D';
        ++x;
    }
    while (x > gx) {
        path += 'U';
        --x;
    }
    while (y < gy) {
        path += 'R';
        ++y;
    }
    while (y > gy) {
        path += 'L';
        --y;
    }
    return path;
}

int main() {
    read_input();
    // 例: (0,0)から(1,1)への経路を出力
    string path = direct_path({0, 0}, {10, 4});
    rep(i, path.size()) { cout << path[i] << endl; }
    return 0;
}
