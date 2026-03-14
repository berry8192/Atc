#include <bits/stdc++.h>
using namespace std;

struct Move {
    int dir;
    int step;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> A(N, vector<int>(N));
    for (auto &r : A)
        for (auto &x : r)
            cin >> x;

    // 方向 (右 下 左 上)
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    // 渦巻き移動シーケンス
    vector<Move> seq = {
        {0, N - 1},   {1, N - 1},   {2, N - 1},   {3, N - 7},   {0, N - 7},
        {1, N - 13},  {2, N - 13},  {3, N - 19},  {0, N - 19},  {1, N - 25},
        {2, N - 25},  {3, N - 31},  {0, N - 31},  {1, N - 37},  {2, N - 37},
        {3, N - 43},  {0, N - 43},  {1, N - 49},  {2, N - 49},  {3, N - 55},
        {0, N - 55},  {1, N - 61},  {2, N - 61},  {3, N - 67},  {0, N - 67},
        {1, N - 73},  {2, N - 73},  {3, N - 79},  {0, N - 79},  {1, N - 85},
        {2, N - 85},  {3, N - 91},  {0, N - 91},  {1, N - 97},  {2, N - 97},
        {3, N - 103}, {0, N - 103}, {1, N - 109}, {2, N - 109}, {3, N - 115},
        {0, N - 115}, {1, N - 121}, {2, N - 121}, {3, N - 127}, {0, N - 127},
        {1, N - 133}, {2, N - 133}, {3, N - 139}, {0, N - 139}, {1, N - 145},
        {2, N - 145}, {3, N - 151}, {0, N - 151}, {1, N - 157}, {2, N - 157},
        {3, N - 163}, {0, N - 163}, {1, N - 169}, {2, N - 169}, {3, N - 175},
        {0, N - 175}, {1, N - 181}, {2, N - 181}, {3, N - 187}, {0, N - 187},
        {1, N - 193}, {2, N - 193}, {1, N - 197}, {3, N - 190}, {1, N - 181}};

    vector<pair<int, int>> path;
    path.reserve(N * N);

    int x = 0, y = 0;
    path.emplace_back(x, y);

    for (auto &m : seq) {
        for (int k = 0; k < m.step; k++) {
            x += dx[m.dir];
            y += dy[m.dir];
            if (x < 0 || x >= N || y < 0 || y >= N)
                continue;
            path.emplace_back(x, y);
        }
    }

    for (auto &p : path)
        cout << p.first << " " << p.second << "\n";
}