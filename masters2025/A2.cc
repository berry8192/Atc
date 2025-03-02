#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(x) x.begin(), x.end()
typedef long long ll;
// using mint = modint;
using P = pair<int, int>;

const ll INF = 1LL << 60;
const int Inf = 1000000000;
const int MaxOperation = 10000;

const int di[] = {0, 1, 0, -1}, dj[] = {1, 0, -1, 0};
const char DIR[] = {'R', 'D', 'L', 'U'};

template <typename T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}

unsigned int randxor() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629,
                        w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}
template <typename T> T rand(T a, T b) {
    assert(a <= b);
    ll len = (b - a + 1);
    return randxor() % len + a;
}

class Timer {
  private:
    static const int LAZY_MASK = 0xFF;

    chrono::system_clock::time_point start;
    int call_cnt = 0;
    int prev_time;
    bool is_lazy;

  public:
    Timer(bool is_lazy = false) : is_lazy(is_lazy) {
        start = chrono::system_clock::now();
    }

    int get_ms() {
        if (!is_lazy || (call_cnt & LAZY_MASK) == 0) {
            auto end = chrono::system_clock::now();
            prev_time = chrono::duration_cast<chrono::milliseconds>(end - start)
                            .count();
        }
        call_cnt++;
        return prev_time;
    }
};

int main() {

    int N, M;
    cin >> N >> M;
    vector<string> S(N);
    vector<int> Remains(3);
    vector<pair<int, int>> Goals(3);
    rep(i, N) cin >> S[i];

    vector<vector<int>> dist(N, vector<int>(N, Inf));

    priority_queue<tuple<int, int, int>> que;
    queue<pair<int, int>> targets;
    vector<vector<int>> graph(N * N);

    rep(i, N) rep(j, N) {
        if (S[i][j] == 'A') {
            dist[i][j] = 0;
            que.push({0, i, j});
        }

        if (S[i][j] == 'a')
            Remains[0]++;
        if (S[i][j] == 'A')
            Goals[0] = {i, j};
    }

    while (!que.empty()) {
        auto [d, now_i, now_j] = que.top();
        que.pop();
        d *= -1;
        if (dist[now_i][now_j] < d)
            continue;

        if (S[now_i][now_j] == 'a' || S[now_i][now_j] == '@')
            targets.push({now_i, now_j});

        rep(dir, 4) {
            int nxt_i = now_i + di[dir];
            int nxt_j = now_j + dj[dir];
            if (nxt_i < 0 || N <= nxt_i || nxt_j < 0 || N <= nxt_j)
                continue;

            if (S[nxt_i][nxt_j] == '@' && chmin(dist[nxt_i][nxt_j], d + 1)) {
                que.push({-d - 1, nxt_i, nxt_j});
                graph[nxt_i * N + nxt_j].push_back(now_i * N + now_j);
            } else if (S[nxt_i][nxt_j] != '@' && chmin(dist[nxt_i][nxt_j], d)) {
                que.push({-d, nxt_i, nxt_j});
                graph[nxt_i * N + nxt_j].push_back(now_i * N + now_j);
            }
        }
    }

    set<pair<int, int>> needRemoves;
    rep(i, N) rep(j, N) {
        if (S[i][j] != 'a')
            continue;

        int now_i = i, now_j = j;
        while (now_i != Goals[0].first || now_j != Goals[0].second) {
            auto nxt = graph[now_i * N + now_j][0];
            int nxt_i = nxt / N;
            int nxt_j = nxt % N;
            if (S[nxt_i][nxt_j] == '@')
                needRemoves.insert({nxt_i, nxt_j});
            now_i = nxt_i;
            now_j = nxt_j;
        }
    }

    auto getRoute = [&](int pos_i, int pos_j) -> vector<char> {
        vector<char> ret;
        queue<pair<int, int>> bfs;
        vector<vector<int>> seen(N, vector<int>(N, Inf));
        seen[pos_i][pos_j] = 0;
        bfs.push({pos_i, pos_j});

        while (!bfs.empty()) {
            auto [now_i, now_j] = bfs.front();
            bfs.pop();
            rep(dir, 4) {
                int nxt_i = now_i + di[dir];
                int nxt_j = now_j + dj[dir];
                if (nxt_i < 0 || N <= nxt_i || nxt_j < 0 || N <= nxt_j)
                    continue;
                if (S[nxt_i][nxt_j] != 'A' && S[nxt_i][nxt_j] != '.')
                    continue;

                if (chmin(seen[nxt_i][nxt_j], seen[now_i][now_j] + 1))
                    bfs.push({nxt_i, nxt_j});
            }
        }

        int gi = Goals[0].first;
        int gj = Goals[0].second;

        while (gi != pos_i || gj != pos_j) {
            rep(dir, 4) {
                int nxt_i = gi + di[dir];
                int nxt_j = gj + dj[dir];
                if (nxt_i < 0 || N <= nxt_i || nxt_j < 0 || N <= nxt_j)
                    continue;
                if (seen[nxt_i][nxt_j] == seen[gi][gj] - 1) {
                    ret.push_back(DIR[(dir + 2) % 4]);
                    gi = nxt_i;
                    gj = nxt_j;
                    break;
                }
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    };

    // 操作列
    vector<pair<int, char>> ans;

    int pos_i = Goals[0].first, pos_j = Goals[0].second;
    while (!targets.empty()) {
        auto [target_i, target_j] = targets.front();
        targets.pop();
        if (S[target_i][target_j] == '.')
            continue;
        if (S[target_i][target_j] == '@' &&
            needRemoves.find(make_pair(target_i, target_j)) ==
                needRemoves.end())
            continue;

        while (pos_i < target_i)
            ans.push_back({1, 'D'}), pos_i++;
        while (pos_i > target_i)
            ans.push_back({1, 'U'}), pos_i--;
        while (pos_j < target_j)
            ans.push_back({1, 'R'}), pos_j++;
        while (pos_j > target_j)
            ans.push_back({1, 'L'}), pos_j--;

        auto ret = getRoute(target_i, target_j);
        for (auto c : ret) {
            ans.push_back({2, c});
        }
        char last_op = ans.back().second;
        int cnt = 0;
        while (ans.back().second == last_op && ans.back().first == 2) {
            ans.pop_back();
            cnt++;
        }
        if (cnt)
            ans.push_back({3, last_op});

        if (S[target_i][target_j] == 'a')
            Remains[0]--;
        S[target_i][target_j] = '.';
        pos_i = Goals[0].first;
        pos_j = Goals[0].second;
        if (last_op == 'U')
            pos_i += cnt;
        if (last_op == 'D')
            pos_i -= cnt;
        if (last_op == 'L')
            pos_j += cnt;
        if (last_op == 'R')
            pos_j -= cnt;

        if (Remains[0] == 0 || int(ans.size()) >= MaxOperation)
            break;
    }

    for (auto [op, c] : ans) {
        cout << op << " " << c << endl;
    }

    return 0;
}
