// グリッドグラフ grid_graph 迷路 maze BFS DFS

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

// ========== ライブラリ本体 ==========

// グリッドグラフクラス
class GridGraph {
public:
    int h, w;
    vector<string> grid;
    set<char> passable;  // 通過可能な文字
    set<char> impassable;  // 通過不可能な文字

    // 4方向・8方向の移動
    vector<int> dx4 = {0, 1, 0, -1};
    vector<int> dy4 = {1, 0, -1, 0};
    vector<int> dx8 = {0, 1, 1, 1, 0, -1, -1, -1};
    vector<int> dy8 = {1, 1, 0, -1, -1, -1, 0, 1};

    // コンストラクタ
    GridGraph(int h, int w) : h(h), w(w), grid(h) {
        // デフォルトの通過可能文字
        passable = {'.', 'S', 'G', 's', 'g', 'o', 'O'};
        impassable = {'#', 'x', 'X', '*'};
    }

    GridGraph(vector<string>& g) : h(g.size()), w(g[0].size()), grid(g) {
        passable = {'.', 'S', 'G', 's', 'g', 'o', 'O'};
        impassable = {'#', 'x', 'X', '*'};
    }

    // 通過可能文字の設定
    void set_passable(const string& chars) {
        passable.clear();
        for (char c : chars) passable.insert(c);
    }

    void add_passable(char c) {
        passable.insert(c);
        impassable.erase(c);
    }

    // 通過不可能文字の設定
    void set_impassable(const string& chars) {
        impassable.clear();
        for (char c : chars) impassable.insert(c);
    }

    void add_impassable(char c) {
        impassable.insert(c);
        passable.erase(c);
    }

    // 座標が有効か判定
    bool is_valid(int x, int y) const {
        return 0 <= x && x < h && 0 <= y && y < w;
    }

    // 通過可能か判定
    bool is_passable(int x, int y) const {
        if (!is_valid(x, y)) return false;

        char c = grid[x][y];

        // 通過可能文字リストがある場合はそれを優先
        if (!passable.empty()) {
            return passable.count(c) > 0;
        }

        // 通過不可能文字リストで判定
        return impassable.count(c) == 0;
    }

    // 1次元インデックスに変換
    int to_index(int x, int y) const {
        return x * w + y;
    }

    // 2次元座標に変換
    pair<int, int> to_coord(int idx) const {
        return {idx / w, idx % w};
    }

    // 隣接リストを生成（4方向）
    vector<vector<int>> to_adjacency_list_4() const {
        int n = h * w;
        vector<vector<int>> adj(n);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (!is_passable(i, j)) continue;

                int from = to_index(i, j);

                for (int d = 0; d < 4; d++) {
                    int ni = i + dx4[d];
                    int nj = j + dy4[d];

                    if (is_passable(ni, nj)) {
                        int to = to_index(ni, nj);
                        adj[from].push_back(to);
                    }
                }
            }
        }

        return adj;
    }

    // 隣接リストを生成（8方向）
    vector<vector<int>> to_adjacency_list_8() const {
        int n = h * w;
        vector<vector<int>> adj(n);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (!is_passable(i, j)) continue;

                int from = to_index(i, j);

                for (int d = 0; d < 8; d++) {
                    int ni = i + dx8[d];
                    int nj = j + dy8[d];

                    if (is_passable(ni, nj)) {
                        int to = to_index(ni, nj);
                        adj[from].push_back(to);
                    }
                }
            }
        }

        return adj;
    }

    // 特定文字の位置を検索
    pair<int, int> find_char(char c) const {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (grid[i][j] == c) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    // 全ての特定文字の位置を検索
    vector<pair<int, int>> find_all_chars(char c) const {
        vector<pair<int, int>> result;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (grid[i][j] == c) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }

    // BFS（最短経路）
    vector<vector<int>> bfs(int sx, int sy, bool use_8dir = false) {
        vector<vector<int>> dist(h, vector<int>(w, -1));
        queue<pair<int, int>> q;

        dist[sx][sy] = 0;
        q.push({sx, sy});

        auto& dx = use_8dir ? dx8 : dx4;
        auto& dy = use_8dir ? dy8 : dy4;
        int dirs = use_8dir ? 8 : 4;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < dirs; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (is_passable(nx, ny) && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        return dist;
    }

    // 最短経路（スタートからゴール）
    int shortest_path(int sx, int sy, int gx, int gy, bool use_8dir = false) {
        auto dist = bfs(sx, sy, use_8dir);
        return dist[gx][gy];
    }

    // 最短経路（S から G）
    int shortest_path_sg(bool use_8dir = false) {
        auto [sx, sy] = find_char('S');
        auto [gx, gy] = find_char('G');

        if (sx == -1 || gx == -1) return -1;

        return shortest_path(sx, sy, gx, gy, use_8dir);
    }

    // 経路復元
    vector<pair<int, int>> restore_path(int sx, int sy, int gx, int gy, bool use_8dir = false) {
        auto dist = bfs(sx, sy, use_8dir);

        if (dist[gx][gy] == -1) return {};

        vector<pair<int, int>> path;
        int x = gx, y = gy;

        auto& dx = use_8dir ? dx8 : dx4;
        auto& dy = use_8dir ? dy8 : dy4;
        int dirs = use_8dir ? 8 : 4;

        while (x != sx || y != sy) {
            path.push_back({x, y});

            for (int d = 0; d < dirs; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (is_valid(nx, ny) && dist[nx][ny] == dist[x][y] - 1) {
                    x = nx;
                    y = ny;
                    break;
                }
            }
        }

        path.push_back({sx, sy});
        reverse(path.begin(), path.end());

        return path;
    }

    // 連結成分の数を数える
    int count_components(bool use_8dir = false) {
        vector<vector<bool>> visited(h, vector<bool>(w, false));
        int components = 0;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (is_passable(i, j) && !visited[i][j]) {
                    components++;

                    // BFSで連結成分を探索
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;

                    auto& dx = use_8dir ? dx8 : dx4;
                    auto& dy = use_8dir ? dy8 : dy4;
                    int dirs = use_8dir ? 8 : 4;

                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        for (int d = 0; d < dirs; d++) {
                            int nx = x + dx[d];
                            int ny = y + dy[d];

                            if (is_passable(nx, ny) && !visited[nx][ny]) {
                                visited[nx][ny] = true;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
            }
        }

        return components;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な迷路
    cout << "例1: 基本的な迷路" << endl;
    vector<string> maze1 = {
        "S..#.",
        "##.#.",
        "...#.",
        ".#...",
        ".#..G"
    };

    GridGraph g1(maze1);

    int dist = g1.shortest_path_sg();
    cout << "S から G への最短距離: " << dist << endl;

    // 経路復元
    auto [sx, sy] = g1.find_char('S');
    auto [gx, gy] = g1.find_char('G');
    auto path = g1.restore_path(sx, sy, gx, gy);

    cout << "経路: ";
    for (auto [x, y] : path) {
        cout << "(" << x << "," << y << ") ";
    }
    cout << endl << endl;

    // 例2: カスタム通過可能文字
    cout << "例2: カスタム通過可能文字" << endl;
    vector<string> maze2 = {
        "So.##",
        "##.##",
        "oo.oo",
        ".#...",
        ".#ooG"
    };

    GridGraph g2(maze2);
    g2.add_passable('o');  // 'o' も通過可能に

    dist = g2.shortest_path_sg();
    cout << "S から G への最短距離: " << dist << endl << endl;

    // 例3: 隣接リストへの変換
    cout << "例3: グラフへの変換" << endl;
    vector<string> small_maze = {
        "S..",
        "#.#",
        "..G"
    };

    GridGraph g3(small_maze);
    auto adj = g3.to_adjacency_list_4();

    cout << "隣接リスト:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int idx = g3.to_index(i, j);
            cout << "(" << i << "," << j << ")[" << idx << "]: ";
            for (int next : adj[idx]) {
                auto [nx, ny] = g3.to_coord(next);
                cout << "(" << nx << "," << ny << ") ";
            }
            cout << endl;
        }
    }
    cout << endl;

    // 例4: 連結成分
    cout << "例4: 連結成分の数" << endl;
    vector<string> maze4 = {
        "..#..",
        "..#..",
        "#####",
        "..#..",
        "..#.."
    };

    GridGraph g4(maze4);
    int components = g4.count_components();
    cout << "連結成分の数: " << components << endl;

    return 0;
}