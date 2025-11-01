// グリッドグラフの使用例

#include <bits/stdc++.h>
using namespace std;

// template_with_input.cc のヘッダー部分をここに含める（省略）
// 以下は使用例のみ

// ========== グリッド問題の解法例 ==========

void example_basic_maze() {
    // 基本的な迷路問題
    // 入力:
    // 5 5
    // S....
    // ####.
    // .....
    // .####
    // ....G

    INT(h, w);
    GridGraph g(h, w);  // 自動的にグリッドを入力

    int ans = g.solve();  // S から G への最短経路

    cout << ans << endl;
}

void example_custom_passable() {
    // カスタム通過可能文字
    // 入力（o も通過可能）:
    // 5 5
    // So...
    // ####.
    // ooooo
    // .####
    // ....G

    INT(h, w);
    GRID(grid, h);

    GridGraph g(grid, ".SGoO");  // o と O も通過可能に設定

    int ans = g.solve();
    cout << ans << endl;
}

void example_multiple_goals() {
    // 複数のゴール候補
    // 入力（複数の宝箱 T を探す）:
    // 5 5
    // S....
    // ##.#.
    // ..T..
    // .#.#.
    // T...T

    INT(h, w);
    GRID(grid, h);

    GridGraph g(grid, ".ST");  // T も通過可能

    auto [sx, sy] = g.find_char('S');

    // 各宝箱への最短距離
    int min_dist = INT_MAX;
    rep(i, h) rep(j, w) {
        if (grid[i][j] == 'T') {
            int dist = g.bfs(sx, sy, i, j);
            if (dist != -1) {
                min_dist = min(min_dist, dist);
            }
        }
    }

    cout << min_dist << endl;
}

void example_with_obstacles() {
    // 障害物の種類が複数ある場合
    // #: 壁（通過不可）
    // *: 水（通過不可）
    // ^: 山（通過不可）
    // .: 道（通過可）

    INT(h, w);
    GRID(grid, h);

    // 通過可能な文字のみを指定
    GridGraph g(grid, ".SG");

    auto [sx, sy] = g.find_char('S');
    auto [gx, gy] = g.find_char('G');

    int ans = g.bfs(sx, sy, gx, gy);

    if (ans == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }
}

void example_counting_areas() {
    // 到達可能なマスを数える
    // 入力:
    // 5 5
    // S....
    // .###.
    // .#.#.
    // .#.#.
    // ...#.

    INT(h, w);
    GridGraph g(h, w);

    auto [sx, sy] = g.find_char('S');

    // BFSで到達可能なマスを探索
    vvi dist(h, vi(w, -1));
    queue<pii> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    int reachable = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        reachable++;

        rep(d, 4) {
            int nx = x + dx4[d];
            int ny = y + dy4[d];
            if (g.can_pass(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    cout << reachable << endl;
}

void example_path_restoration() {
    // 経路復元
    // 入力:
    // 5 5
    // S....
    // ####.
    // .....
    // .####
    // ....G

    INT(h, w);
    GridGraph g(h, w);

    auto [sx, sy] = g.find_char('S');
    auto [gx, gy] = g.find_char('G');

    // BFSで経路探索
    vvi dist(h, vi(w, -1));
    vvi prev_x(h, vi(w, -1));
    vvi prev_y(h, vi(w, -1));
    queue<pii> q;

    dist[sx][sy] = 0;
    q.push({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        rep(d, 4) {
            int nx = x + dx4[d];
            int ny = y + dy4[d];
            if (g.can_pass(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                prev_x[nx][ny] = x;
                prev_y[nx][ny] = y;
                q.push({nx, ny});
            }
        }
    }

    if (dist[gx][gy] == -1) {
        cout << "No path" << endl;
        return;
    }

    // 経路復元
    vector<pii> path;
    int x = gx, y = gy;

    while (x != sx || y != sy) {
        path.push_back({x, y});
        int px = prev_x[x][y];
        int py = prev_y[x][y];
        x = px;
        y = py;
    }
    path.push_back({sx, sy});

    reverse(all(path));

    cout << "Path length: " << dist[gx][gy] << endl;
    cout << "Path: ";
    for (auto [x, y] : path) {
        cout << "(" << x << "," << y << ") ";
    }
    cout << endl;
}

void example_dijkstra_on_grid() {
    // コスト付きグリッド（各マスに入るコストが異なる）
    // 入力:
    // 5 5
    // S....
    // .....
    // .....
    // .....
    // ....G
    // 1 2 3 4 5
    // 2 3 4 5 1
    // 3 4 5 1 2
    // 4 5 1 2 3
    // 5 1 2 3 4

    INT(h, w);
    GRID(grid, h);
    VVI(cost, h, w);

    // ダイクストラ法で最小コスト経路を探索
    auto [sx, sy] = find_char_in_grid(grid, 'S');
    auto [gx, gy] = find_char_in_grid(grid, 'G');

    vector<vll> dist(h, vll(w, LINF));
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<>> pq;

    dist[sx][sy] = 0;
    pq.push({0, sx, sy});

    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (dist[x][y] < d) continue;

        rep(dir, 4) {
            int nx = x + dx4[dir];
            int ny = y + dy4[dir];

            if (0 <= nx && nx < h && 0 <= ny && ny < w && grid[nx][ny] != '#') {
                ll new_cost = dist[x][y] + cost[nx][ny];
                if (new_cost < dist[nx][ny]) {
                    dist[nx][ny] = new_cost;
                    pq.push({new_cost, nx, ny});
                }
            }
        }
    }

    cout << dist[gx][gy] << endl;
}

// ヘルパー関数
pii find_char_in_grid(const vs& grid, char c) {
    int h = grid.size();
    int w = grid[0].size();
    rep(i, h) rep(j, w) {
        if (grid[i][j] == c) return {i, j};
    }
    return {-1, -1};
}

int main() {
    // 使いたい例を呼び出す
    // example_basic_maze();
    // example_custom_passable();
    // example_multiple_goals();
    // ...

    return 0;
}