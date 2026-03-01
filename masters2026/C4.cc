#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> wall_v, wall_h;
int dx[4] = {-1, 0, 1, 0}; // U R D L
int dy[4] = {0, 1, 0, -1};
const char* dc = "URDL";

bool can_go(int x, int y, int d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= N || ny < 0 || ny >= N) return false;
    if (d == 0) return wall_h[nx][ny] == '0';
    if (d == 2) return wall_h[x][y] == '0';
    if (d == 1) return wall_v[x][y] == '0';
    if (d == 3) return wall_v[x][ny] == '0';
    return false;
}

struct CState { int x, y, dir, turn; };

// ランダム探索: 始点(sx,sy,sd)から壁で回転を繰り返し、巡回路を検出
// 戻り値: {巡回路の状態列, カバーセル数}
pair<vector<CState>, int> try_find(int sx, int sy, int sd, mt19937& rng) {
    vector<int> seen(N * N * 4, -1);
    vector<CState> states;
    // 各状態がカバーするセルを記録
    vector<vector<int>> state_cells;

    int x = sx, y = sy, d = sd;

    for (int step = 0; step < 1700; step++) {
        int key = (x * N + y) * 4 + d;
        if (seen[key] >= 0) {
            int start = seen[key];
            vector<CState> cycle(states.begin() + start, states.end());
            // カバレッジ計算
            vector<bool> cv(N * N, false);
            int cnt = 0;
            for (int i = start; i < step; i++)
                for (int c : state_cells[i])
                    if (!cv[c]) { cv[c] = true; cnt++; }
            return {cycle, cnt};
        }
        seen[key] = step;

        // 壁まで直進
        vector<int> cells;
        int cx = x, cy = y;
        cells.push_back(cx * N + cy);
        while (can_go(cx, cy, d)) {
            cx += dx[d]; cy += dy[d];
            cells.push_back(cx * N + cy);
        }
        state_cells.push_back(cells);

        // 壁で回転（ランダムにR/L）
        int turn = rng() % 2;
        states.push_back({x, y, d, turn});

        x = cx; y = cy;
        d = turn == 0 ? (d + 1) % 4 : (d + 3) % 4;
    }
    return {{}, 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int AK, AM, AW;
    cin >> N >> AK >> AM >> AW;
    wall_v.resize(N);
    wall_h.resize(N - 1);
    for (int i = 0; i < N; i++) cin >> wall_v[i];
    for (int i = 0; i < N - 1; i++) cin >> wall_h[i];

    mt19937 rng(42);
    int best_M = INT_MAX;
    vector<CState> best_cycle;
    int best_cov = 0;

    auto t0 = chrono::steady_clock::now();
    int iter = 0, found = 0;

    while (chrono::duration_cast<chrono::milliseconds>(
               chrono::steady_clock::now() - t0).count() < 1800) {
        int sx = rng() % N, sy = rng() % N, sd = rng() % 4;
        auto [cycle, cov] = try_find(sx, sy, sd, rng);
        iter++;
        best_cov = max(best_cov, cov);
        if (cov == N * N) {
            found++;
            int M = (int)cycle.size();
            if (M < best_M) {
                best_M = M;
                best_cycle = cycle;
            }
        }
    }
    cerr << "iter=" << iter << " found=" << found
         << " best_M=" << best_M << " best_cov=" << best_cov << endl;

    if (best_cycle.empty()) {
        // フォールバック: 全マスに1台ずつ
        cerr << "FALLBACK" << endl;
        cout << N * N << "\n";
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                cout << "1 " << i << " " << j << " U\n";
                cout << "R 0 R 0\n";
            }
    } else {
        int M = best_M;
        cout << 1 << "\n";
        cout << M << " " << best_cycle[0].x << " " << best_cycle[0].y
             << " " << dc[best_cycle[0].dir] << "\n";
        for (int i = 0; i < M; i++) {
            char tc = best_cycle[i].turn == 0 ? 'R' : 'L';
            int nxt = (i + 1) % M;
            cout << "F " << i << " " << tc << " " << nxt << "\n";
        }
    }
    for (int i = 0; i < N; i++) cout << string(N - 1, '0') << "\n";
    for (int i = 0; i < N - 1; i++) cout << string(N, '0') << "\n";
    return 0;
}
