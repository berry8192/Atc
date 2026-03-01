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

vector<vector<short>> all_dist;

void precompute_distances() {
    int V = N * N;
    all_dist.assign(V, vector<short>(V, -1));
    for (int s = 0; s < V; s++) {
        auto& d = all_dist[s];
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int c = q.front(); q.pop();
            int x = c / N, y = c % N;
            for (int dir = 0; dir < 4; dir++) {
                if (!can_go(x, y, dir)) continue;
                int nc = cell(x + dx[dir], y + dy[dir]);
                if (d[nc] >= 0) continue;
                d[nc] = d[c] + 1;
                q.push(nc);
            }
        }
    }
}

vector<int> bfs_path(int sc, int gc) {
    if (sc == gc) return {};
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

int count_states(const vector<int>& tour) {
    int states = 0;
    int dir = 1;
    for (size_t i = 1; i < tour.size(); i++) {
        int px = tour[i-1] / N, py = tour[i-1] % N;
        int cx = tour[i] / N, cy = tour[i] % N;
        int nd;
        if (cx == px-1) nd = 0;
        else if (cy == py+1) nd = 1;
        else if (cx == px+1) nd = 2;
        else nd = 3;
        int diff = (nd - dir + 4) % 4;
        if (diff == 1) states += 1;
        else if (diff == 3) states += 1;
        else if (diff == 2) states += 2;
        states += 1;
        dir = nd;
    }
    int diff = (1 - dir + 4) % 4;
    if (diff == 1) states += 1;
    else if (diff == 3) states += 1;
    else if (diff == 2) states += 2;
    return states;
}

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
    turn(1);

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

    int V = N * N;
    precompute_distances();

    auto tour = dfs_euler_tour(cell(0, 0));
    int best_states = count_states(tour);
    auto best_tour = tour;
    cerr << "DFS: len=" << tour.size() << " states=" << best_states << endl;

    mt19937 rng(42);
    auto start_time = chrono::steady_clock::now();
    auto elapsed_ms = [&]() {
        return chrono::duration_cast<chrono::milliseconds>(
            chrono::steady_clock::now() - start_time).count();
    };

    vector<int> cnt(V, 0);
    for (int c : tour) cnt[c]++;

    int iter = 0, accept = 0;

    while (elapsed_ms() < 1800) {
        iter++;
        int L = tour.size();
        if (L <= V + 1) break;

        int max_span = min(L - 1, 100);
        if (max_span < 3) continue;
        int span = 3 + rng() % (max_span - 2);
        int i = rng() % (L - span);
        int j = i + span;

        // 必須セル（cnt==1、セグメント内で1回のみ出現するセル）
        vector<int> req;
        for (int k = i + 1; k < j; k++) {
            if (cnt[tour[k]] == 1) req.push_back(tour[k]);
        }
        sort(req.begin(), req.end());
        req.erase(unique(req.begin(), req.end()), req.end());

        if ((int)req.size() > 12) continue;

        int old_dist = j - i;
        int new_dist = 0;
        vector<int> wps;

        if (req.empty()) {
            new_dist = all_dist[tour[i]][tour[j]];
            if (new_dist < 0 || new_dist >= old_dist) continue;
            wps = {tour[i], tour[j]};
        } else {
            // 最近傍法
            vector<bool> used(req.size(), false);
            vector<int> ordered;
            int cur = tour[i];
            bool fail = false;
            for (int r = 0; r < (int)req.size(); r++) {
                int best = -1, best_d = INT_MAX;
                for (int k = 0; k < (int)req.size(); k++) {
                    if (used[k]) continue;
                    int d = all_dist[cur][req[k]];
                    if (d >= 0 && d < best_d) { best_d = d; best = k; }
                }
                if (best < 0) { fail = true; break; }
                used[best] = true;
                ordered.push_back(req[best]);
                cur = req[best];
            }
            if (fail) continue;

            wps.push_back(tour[i]);
            for (int c : ordered) wps.push_back(c);
            wps.push_back(tour[j]);

            bool ok = true;
            for (int k = 0; k + 1 < (int)wps.size(); k++) {
                int d = all_dist[wps[k]][wps[k+1]];
                if (d < 0) { ok = false; break; }
                new_dist += d;
            }
            if (!ok || new_dist >= old_dist) continue;
        }

        // 実パスを構築
        vector<int> new_path;
        new_path.reserve(new_dist);
        for (int k = 0; k + 1 < (int)wps.size(); k++) {
            auto seg = bfs_path(wps[k], wps[k+1]);
            for (int c : seg) new_path.push_back(c);
        }

        // 新しいtourを構成
        vector<int> new_tour;
        new_tour.reserve(L - old_dist + new_dist);
        for (int k = 0; k <= i; k++) new_tour.push_back(tour[k]);
        for (int c : new_path) new_tour.push_back(c);
        for (int k = j + 1; k < L; k++) new_tour.push_back(tour[k]);

        // カバレッジ確認
        vector<int> new_cnt(V, 0);
        for (int c : new_tour) new_cnt[c]++;
        bool ok = true;
        for (int c = 0; c < V; c++) {
            if (new_cnt[c] == 0) { ok = false; break; }
        }
        if (!ok) continue;

        int new_states = count_states(new_tour);
        if (new_states < best_states) {
            tour = new_tour;
            cnt = new_cnt;
            best_states = new_states;
            best_tour = tour;
            accept++;
        }
    }

    cerr << "SA iter=" << iter << " accept=" << accept
         << " len=" << best_tour.size()
         << " states=" << best_states << endl;

    output(best_tour);
    return 0;
}
