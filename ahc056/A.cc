#include <bits/stdc++.h>
using namespace std;

struct Cell {
    bool wall_up, wall_down, wall_left, wall_right;
};

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const char dirc[4] = {'U', 'D', 'L', 'R'};

// BFSで(start→goal)の最短経路を返す
vector<pair<int, int>> bfs_path(const vector<vector<Cell>> &grid, int N,
                                pair<int, int> start, pair<int, int> goal) {
    vector<vector<pair<int, int>>> prev(N, vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    q.push(start);
    prev[start.first][start.second] = start;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (make_pair(x, y) == goal)
            break;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (d == 0 && grid[x][y].wall_up)
                continue;
            if (d == 1 && grid[x][y].wall_down)
                continue;
            if (d == 2 && grid[x][y].wall_left)
                continue;
            if (d == 3 && grid[x][y].wall_right)
                continue;
            if (prev[nx][ny].first != -1)
                continue;
            prev[nx][ny] = {x, y};
            q.push({nx, ny});
        }
    }

    // 経路復元
    vector<pair<int, int>> path;
    pair<int, int> cur = goal;
    while (cur != start) {
        path.push_back(cur);
        cur = prev[cur.first][cur.second];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, T;
    cin >> N >> K >> T;

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++)
        cin >> v[i];
    for (int i = 0; i < N - 1; i++)
        cin >> h[i];

    vector<pair<int, int>> goals(K);
    for (int i = 0; i < K; i++)
        cin >> goals[i].first >> goals[i].second;

    // 壁情報の構築
    vector<vector<Cell>> grid(N, vector<Cell>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j].wall_left = (j == 0) || (v[i][j - 1] == '1');
            grid[i][j].wall_right = (j == N - 1) || (v[i][j] == '1');
            grid[i][j].wall_up = (i == 0) || (h[i - 1][j] == '1');
            grid[i][j].wall_down = (i == N - 1) || (h[i][j] == '1');
        }
    }

    // 目的地間の経路を連結
    vector<pair<int, int>> full_path;
    for (int i = 0; i + 1 < K; i++) {
        auto path = bfs_path(grid, N, goals[i], goals[i + 1]);
        if (i > 0)
            path.erase(path.begin()); // 重複防止
        for (auto &p : path)
            full_path.push_back(p);
    }

    int C = 1;                     // 色数
    int Q = (int)full_path.size(); // 状態数（経路長）
    int M = Q;                     // 遷移規則数

    cout << C << " " << Q << " " << M << "\n";

    // 初期盤面（全部色0）
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << 0 << (j + 1 == N ? '\n' : ' ');
        }
    }

    // 経路に従って遷移規則を作る
    for (int i = 0; i < Q; i++) {
        char move = 'S'; // デフォルトは停止
        if (i + 1 < Q) {
            auto [x1, y1] = full_path[i];
            auto [x2, y2] = full_path[i + 1];
            if (x2 == x1 - 1)
                move = 'U';
            else if (x2 == x1 + 1)
                move = 'D';
            else if (y2 == y1 - 1)
                move = 'L';
            else if (y2 == y1 + 1)
                move = 'R';
        }
        // 色0、状態i → 色0、状態i+1、方向move
        cout << 0 << " " << i << " " << 0 << " " << min(i + 1, Q - 1) << " "
             << move << "\n";
    }

    return 0;
}
