// グリッド上のパス数え上げ path counting grid DFS memoization
// ABC378 D - Count Simple Paths 用

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

// ========== ライブラリ本体 ==========

// グリッド上での経路数え上げ（DFS + メモ化）
struct PathCounter {
    int h, w;
    vector<string> grid;
    int target_length;
    map<tuple<int, int, set<pair<int, int>>, int>, long long> memo;
    
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};
    
    PathCounter(int h, int w, vector<string>& g, int k) 
        : h(h), w(w), grid(g), target_length(k) {}
    
    bool valid(int x, int y) {
        return 0 <= x && x < h && 0 <= y && y < w && grid[x][y] == '.';
    }
    
    // 単純なDFS（小さいグリッド用）
    long long count_paths_simple(int sx, int sy) {
        set<pair<int, int>> visited;
        visited.insert({sx, sy});
        return dfs_simple(sx, sy, visited, 0);
    }
    
    long long dfs_simple(int x, int y, set<pair<int, int>>& visited, int len) {
        if (len == target_length) {
            return 1;
        }
        
        long long count = 0;
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (valid(nx, ny) && visited.find({nx, ny}) == visited.end()) {
                visited.insert({nx, ny});
                count += dfs_simple(nx, ny, visited, len + 1);
                visited.erase({nx, ny});
            }
        }
        
        return count;
    }
    
    // ビットマスクを使用した高速DFS
    long long count_paths_bitmask(int sx, int sy) {
        vector<vector<int>> cell_id(h, vector<int>(w, -1));
        int id = 0;
        
        // 通過可能セルにIDを割り当て
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (grid[i][j] == '.') {
                    cell_id[i][j] = id++;
                }
            }
        }
        
        if (cell_id[sx][sy] == -1) return 0;
        
        return dfs_bitmask(sx, sy, 1LL << cell_id[sx][sy], 0, cell_id);
    }
    
    long long dfs_bitmask(int x, int y, long long visited, int len, 
                         vector<vector<int>>& cell_id) {
        if (len == target_length) {
            return 1;
        }
        
        long long count = 0;
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (valid(nx, ny)) {
                int id = cell_id[nx][ny];
                if (!(visited & (1LL << id))) {
                    count += dfs_bitmask(nx, ny, visited | (1LL << id), 
                                       len + 1, cell_id);
                }
            }
        }
        
        return count;
    }
    
    // 全ての通過可能マスからのパス数
    long long count_all_paths() {
        long long total = 0;
        
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (grid[i][j] == '.') {
                    total += count_paths_simple(i, j);
                }
            }
        }
        
        return total;
    }
    
    // 最短路パス数（グリッド上でのマンハッタン距離）
    long long count_shortest_paths(int sx, int sy, int gx, int gy) {
        int dist = abs(gx - sx) + abs(gy - sy);
        if (dist != target_length) return 0;
        
        vector<vector<long long>> dp(h, vector<long long>(w, 0));
        dp[sx][sy] = 1;
        
        // 最短路のみを考慮
        for (int step = 0; step < dist; step++) {
            vector<vector<long long>> new_dp(h, vector<long long>(w, 0));
            
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (dp[i][j] == 0 || grid[i][j] != '.') continue;
                    
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];
                        
                        if (!valid(ni, nj)) continue;
                        
                        // ゴールに近づく方向のみ
                        int curr_dist = abs(gx - i) + abs(gy - j);
                        int next_dist = abs(gx - ni) + abs(gy - nj);
                        
                        if (next_dist < curr_dist) {
                            new_dp[ni][nj] += dp[i][j];
                        }
                    }
                }
            }
            
            dp = new_dp;
        }
        
        return dp[gx][gy];
    }
};

// ABC378 D 用: Kマス移動のパス数
long long solve_simple_paths(int h, int w, int k, vector<string>& grid) {
    PathCounter pc(h, w, grid, k);
    return pc.count_all_paths();
}

// ========== サンプルコード ==========

int main() {
    // 例1: 小さいグリッドでのパス数え上げ
    cout << "例1: 3x3 グリッドで K=2" << endl;
    vector<string> grid1 = {
        "...",
        ".#.",
        "..."
    };
    PathCounter pc1(3, 3, grid1, 2);
    cout << "グリッド:" << endl;
    for (const auto& row : grid1) {
        cout << row << endl;
    }
    cout << "全ての2ステップパス数: " << pc1.count_all_paths() << endl;
    cout << endl;
    
    // 例2: ABC378 D タイプ
    cout << "例2: ABC378 D タイプ" << endl;
    vector<string> grid2 = {
        "..#",
        "...",
        "#.."
    };
    int k = 4;
    cout << "グリッド:" << endl;
    for (const auto& row : grid2) {
        cout << row << endl;
    }
    cout << "K = " << k << endl;
    cout << "答え: " << solve_simple_paths(3, 3, k, grid2) << endl;
    cout << endl;
    
    // 例3: ビットマスク版（高速）
    cout << "例3: ビットマスクを使用" << endl;
    vector<string> grid3 = {
        "....",
        "....",
        "....",
        "...."
    };
    PathCounter pc3(4, 4, grid3, 5);
    cout << "4x4 グリッドで K=5" << endl;
    cout << "(0,0)から始まるパス数: " << pc3.count_paths_bitmask(0, 0) << endl;
    cout << endl;
    
    // 例4: 最短路パス数
    cout << "例4: 最短路のみのパス数" << endl;
    vector<string> grid4 = {
        "....",
        "....",
        "...."
    };
    PathCounter pc4(3, 4, grid4, 5);
    cout << "(0,0) から (2,3) へのマンハッタン距離 5 のパス数: " 
         << pc4.count_shortest_paths(0, 0, 2, 3) << endl;
    cout << "組み合わせ: C(5, 2) = 10" << endl;
    cout << endl;
    
    // 例5: 障害物が多い場合
    cout << "例5: 障害物が多いグリッド" << endl;
    vector<string> grid5 = {
        ".#.#.",
        "#...#",
        ".....",
        "#.#.#",
        "....."
    };
    PathCounter pc5(5, 5, grid5, 6);
    cout << "グリッド:" << endl;
    for (const auto& row : grid5) {
        cout << row << endl;
    }
    cout << "K=6 のパス数: " << pc5.count_all_paths() << endl;
    
    return 0;
}