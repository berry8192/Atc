#include <bits/stdc++.h>
using namespace std;

struct Forest {
    int N;
    int ti, tj;          // 花の位置
    vector<string> grid; // マップ（'.' = 空き, 'T' = 木）

    // 冒険者の状態
    int pi, pj;                     // 現在位置
    vector<vector<bool>> confirmed; // 確認済みマス

    Forest(int n, int t_i, int t_j, const vector<string> &g)
        : N(n), ti(t_i), tj(t_j), grid(g) {
        confirmed.assign(N, vector<bool>(N, false));
        pi = pj = -1; // 未設定
    }

    bool inBounds(int i, int j) const {
        return (0 <= i && i < N && 0 <= j && j < N);
    }

    void confirmCell(int i, int j) {
        if (inBounds(i, j))
            confirmed[i][j] = true;
    }

    // ✅ 確認済みには置けないように修正
    bool canPlaceTreant(int i, int j) const {
        if (!inBounds(i, j))
            return false;
        if (confirmed[i][j])
            return false; // 確認済みなら不可
        if (grid[i][j] != '.')
            return false; // 空きマスでなければ不可
        return true;
    }

    void placeTreant(int i, int j) {
        if (canPlaceTreant(i, j)) {
            grid[i][j] = 'T';
        }
    }

    // 経路チェック: (x,y) を塞いだ後でも入口から花まで行けるか
    bool pathExistsAfter(int x, int y) {
        if (!canPlaceTreant(x, y))
            return false;
        vector<vector<bool>> vis(N, vector<bool>(N, false));
        queue<pair<int, int>> q;
        int si = 0, sj = N / 2; // 入口
        if (grid[si][sj] == 'T')
            return false;
        q.push({si, sj});
        vis[si][sj] = true;
        int di[4] = {-1, 1, 0, 0};
        int dj[4] = {0, 0, -1, 1};
        while (!q.empty()) {
            pair<int, int> pos = q.front();
            q.pop();
            int i = pos.first, j = pos.second;
            if (i == ti && j == tj)
                return true;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (!inBounds(ni, nj))
                    continue;
                if (vis[ni][nj])
                    continue;
                if (grid[ni][nj] == 'T')
                    continue;
                if (ni == x && nj == y)
                    continue; // 仮置きトレント
                vis[ni][nj] = true;
                q.push({ni, nj});
            }
        }
        return false;
    }

    // (x,y) に置いた場合の次ターン視界シミュレーション
    vector<pair<int, int>> simulateVisionAfter(int x, int y) {
        vector<pair<int, int>> newCells;
        auto isTree = [&](int i, int j) -> bool {
            if (!inBounds(i, j))
                return true; // 外周は木
            if (i == x && j == y)
                return true; // 仮置きトレント
            return grid[i][j] == 'T';
        };
        int di[4] = {-1, 1, 0, 0};
        int dj[4] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            int ni = pi, nj = pj;
            while (true) {
                ni += di[d];
                nj += dj[d];
                if (!inBounds(ni, nj))
                    break;
                if (!confirmed[ni][nj])
                    newCells.push_back({ni, nj});
                if (isTree(ni, nj))
                    break;
            }
        }
        return newCells;
    }

    // 情報量評価
    double evaluateInfoAfter(int x, int y) {
        // BFS で各セルから花までの距離を計算
        vector<vector<int>> dist(N, vector<int>(N, -1));
        queue<pair<int, int>> q;
        q.push({ti, tj});
        dist[ti][tj] = 0;
        int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, -1, 1};
        while (!q.empty()) {
            pair<int, int> pos = q.front();
            q.pop();
            int i = pos.first, j = pos.second;
            for (int d = 0; d < 4; d++) {
                int ni = i + di[d], nj = j + dj[d];
                if (!inBounds(ni, nj))
                    continue;
                if (grid[ni][nj] == 'T')
                    continue;
                if (ni == x && nj == y)
                    continue; // 仮置き
                if (dist[ni][nj] != -1)
                    continue;
                dist[ni][nj] = dist[i][j] + 1;
                q.push({ni, nj});
            }
        }

        // 新規確認済みマスを取得
        auto newCells = simulateVisionAfter(x, y);

        double info = 0.0;
        for (const auto &cell : newCells) {
            int ci = cell.first, cj = cell.second;
            if (dist[ci][cj] >= 0) {
                double d = dist[ci][cj] + 0.001;
                info += 1.0 / d;
                // --- 指数減衰版 (試すならコメント解除) ---
                // double alpha = 0.2;
                // info += exp(-alpha * dist[ci][cj]);
            }
        }
        return info;
    }

    bool updateTurn() {
        int n;
        if (!(cin >> pi >> pj))
            return true;
        if (pi == ti && pj == tj)
            return true;
        cin >> n;
        for (int k = 0; k < n; k++) {
            int x, y;
            cin >> x >> y;
            confirmCell(x, y);
        }
        return false;
    }

    void placeTreantsAndOutput() {
        vector<pair<int, int>> placements;

        // 複数トレントを貪欲に配置
        while (true) {
            double bestInfo = 1e18;
            pair<int, int> best = {-1, -1};

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (!canPlaceTreant(i, j))
                        continue;
                    if (!pathExistsAfter(i, j))
                        continue;
                    double info = evaluateInfoAfter(i, j);
                    if (info < bestInfo) {
                        bestInfo = info;
                        best = {i, j};
                    }
                }
            }

            // これ以上置けるトレントがない場合は終了
            if (best.first == -1) {
                break;
            }

            // トレントを実際に配置して状態を更新
            placeTreant(best.first, best.second);
            placements.push_back(best);

            // 情報量の改善が小さい場合は追加配置を停止
            if (bestInfo > 0.01) {
                break;
            }
        }

        // 出力
        cout << placements.size();
        for (const auto &placement : placements) {
            cout << " " << placement.first << " " << placement.second;
        }
        cout << "\n";
        cout.flush();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, ti, tj;
    cin >> N >> ti >> tj;

    vector<string> grid(N);
    for (int i = 0; i < N; i++)
        cin >> grid[i];

    Forest forest(N, ti, tj, grid);

    if (forest.updateTurn())
        return 0;

    while (true) {
        forest.placeTreantsAndOutput();
        if (forest.updateTurn())
            break;
    }
    return 0;
}
