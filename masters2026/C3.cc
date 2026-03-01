#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> wall_v, wall_h;
int dx[4] = {-1, 0, 1, 0}; // U R D L
int dy[4] = {0, 1, 0, -1};

bool can_go(int x, int y, int d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= N || ny < 0 || ny >= N) return false;
    if (d == 0) return wall_h[nx][ny] == '0';
    if (d == 2) return wall_h[x][y] == '0';
    if (d == 1) return wall_v[x][y] == '0';
    if (d == 3) return wall_v[x][ny] == '0';
    return false;
}

int cell(int x, int y) { return x * N + y; }

// BFS最短路 (セル列を返す、始点含まず)
vector<int> bfs_path(int sc, int gc) {
    vector<int> dist(N * N, -1);
    vector<int> prev(N * N, -1);
    queue<int> q;
    dist[sc] = 0;
    q.push(sc);
    while (!q.empty()) {
        int c = q.front(); q.pop();
        if (c == gc) break;
        int x = c / N, y = c % N;
        for (int d = 0; d < 4; d++) {
            if (!can_go(x, y, d)) continue;
            int nc = cell(x + dx[d], y + dy[d]);
            if (dist[nc] >= 0) continue;
            dist[nc] = dist[c] + 1;
            prev[nc] = c;
            q.push(nc);
        }
    }
    vector<int> path;
    for (int c = gc; c != sc; c = prev[c]) path.push_back(c);
    reverse(path.begin(), path.end());
    return path;
}

// DFSオイラーツアー (セル番号列、始点含む、最後に始点に戻る)
vector<int> dfs_euler_tour(int start) {
    vector<bool> vis(N * N, false);
    vector<int> tour;
    tour.push_back(start);
    function<void(int)> dfs = [&](int c) {
        vis[c] = true;
        int x = c / N, y = c % N;
        for (int d = 0; d < 4; d++) {
            if (!can_go(x, y, d)) continue;
            int nc = cell(x + dx[d], y + dy[d]);
            if (vis[nc]) continue;
            tour.push_back(nc);
            dfs(nc);
            tour.push_back(c);
        }
    };
    dfs(start);
    return tour;
}

// 巡回路からステップ数(=状態数)を計算
int count_states(const vector<int>& tour) {
    int states = 0;
    int dir = 1; // 初期方向 R
    for (size_t i = 1; i < tour.size(); i++) {
        int px = tour[i-1] / N, py = tour[i-1] % N;
        int cx = tour[i] / N, cy = tour[i] % N;
        int nd;
        if (cx == px-1) nd = 0;
        else if (cy == py+1) nd = 1;
        else if (cx == px+1) nd = 2;
        else nd = 3;
        // ターン数
        int diff = (nd - dir + 4) % 4;
        if (diff == 1) states += 1;      // R
        else if (diff == 3) states += 1; // L
        else if (diff == 2) states += 2; // R,R or L,L
        // forward
        states += 1;
        dir = nd;
    }
    // 初期方向に戻す
    int diff = (1 - dir + 4) % 4;
    if (diff == 1) states += 1;
    else if (diff == 3) states += 1;
    else if (diff == 2) states += 2;
    return states;
}

// 出力
void output(const vector<int>& tour) {
    struct Step { char act; };
    vector<Step> steps;
    int dir = 1;
    auto turn = [&](int nd) {
        while (dir != nd) {
            if ((dir + 1) % 4 == nd) {
                steps.push_back({'R'});
                dir = (dir + 1) % 4;
            } else {
                steps.push_back({'L'});
                dir = (dir + 3) % 4;
            }
        }
    };
    for (size_t i = 1; i < tour.size(); i++) {
        int px = tour[i-1] / N, py = tour[i-1] % N;
        int cx = tour[i] / N, cy = tour[i] % N;
        int nd;
        if (cx == px-1) nd = 0;
        else if (cy == py+1) nd = 1;
        else if (cx == px+1) nd = 2;
        else nd = 3;
        turn(nd);
        steps.push_back({'F'});
    }
    turn(1); // 初期方向に戻す

    int M = steps.size();
    int sx = tour[0] / N, sy = tour[0] % N;
    cout << 1 << "\n";
    cout << M << " " << sx << " " << sy << " R\n";
    for (int i = 0; i < M; i++) {
        char a = steps[i].act;
        int nxt = (i + 1) % M;
        char wa = (a == 'F') ? 'R' : a;
        cout << a << " " << nxt << " " << wa << " " << nxt << "\n";
    }
    for (int i = 0; i < N; i++) cout << string(N-1, '0') << "\n";
    for (int i = 0; i < N-1; i++) cout << string(N, '0') << "\n";
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

    // Phase 1: DFSオイラーツアー（初期解）
    auto tour = dfs_euler_tour(cell(0, 0));
    int best_states = count_states(tour);
    auto best_tour = tour;
    cerr << "DFS initial: len=" << tour.size() << " states=" << best_states << endl;

    // Phase 2: SA的短縮
    // 操作: tour[i]→...→tour[j] をBFS最短路で置換
    // 条件: 削除される区間のセルが他でもカバーされていること
    mt19937 rng(42);
    auto start_time = chrono::steady_clock::now();
    auto elapsed_ms = [&]() {
        return chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start_time).count();
    };

    // cnt[c] = tourでのセルcの出現回数
    vector<int> cnt(N * N, 0);
    for (int c : tour) cnt[c]++;

    int iter = 0;
    double T = 50.0;

    while (elapsed_ms() < 1800) {
        iter++;
        int L = tour.size();
        if (L <= 401) break; // ハミルトン閉路+帰還に近い

        // ランダムに区間 [i, j] を選ぶ (i < j, 区間長2〜L/2)
        int i = rng() % L;
        int max_span = min((int)(L / 2), 40); // 区間長上限
        if (max_span < 2) continue;
        int span = 2 + rng() % (max_span - 1);
        int j = (i + span) % L;

        // 環状なのでi < jに正規化（簡単のため環状を避ける）
        if (j <= i) continue;

        // 削除区間: tour[i+1] ... tour[j-1] のセルがcnt>=2か確認
        bool removable = true;
        for (int k = i + 1; k < j; k++) {
            if (cnt[tour[k]] <= 1) { removable = false; break; }
        }
        if (!removable) continue;

        // BFS最短路 tour[i] → tour[j]
        auto bp = bfs_path(tour[i], tour[j]);
        // 新区間: tour[i], bp[0], bp[1], ..., bp.back()=tour[j]
        int old_len = j - i; // 旧区間の辺数
        int new_len = (int)bp.size(); // 新区間の辺数

        if (new_len >= old_len) continue; // 短くならない

        // 新しいtourを構成
        vector<int> new_tour;
        new_tour.reserve(L - old_len + new_len);
        for (int k = 0; k <= i; k++) new_tour.push_back(tour[k]);
        for (int c : bp) new_tour.push_back(c);
        for (int k = j + 1; k < L; k++) new_tour.push_back(tour[k]);

        // カバレッジ確認
        vector<int> new_cnt(N * N, 0);
        for (int c : new_tour) new_cnt[c]++;
        bool ok = true;
        for (int c = 0; c < N * N; c++) {
            if (new_cnt[c] == 0) { ok = false; break; }
        }
        if (!ok) continue;

        int new_states = count_states(new_tour);

        // SA判定
        int delta = new_states - best_states;
        if (delta < 0 || (T > 0.1 && rng() % 1000 < 1000 * exp(-delta / T))) {
            tour = new_tour;
            cnt = new_cnt;
            if (new_states < best_states) {
                best_states = new_states;
                best_tour = tour;
            }
        }

        // 温度を下げる
        if (iter % 1000 == 0) {
            T *= 0.995;
        }
    }
    cerr << "SA iter=" << iter << " tour_len=" << best_tour.size()
         << " states=" << best_states << endl;

    output(best_tour);
    cerr << "final states=" << best_states << endl;
    return 0;
}
