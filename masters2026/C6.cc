#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 20;
constexpr int BEAM_WIDTH = 10;
constexpr int MAX_STEP = 300;

// 方向: 0=U,1=R,2=D,3=L
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int N;
vector<string> wall_v, wall_h;

bool can_go(int x, int y, int d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (nx < 0 || nx >= N || ny < 0 || ny >= N)
        return false;
    if (d == 0)
        return wall_h[nx][ny] == '0'; // 上
    if (d == 2)
        return wall_h[x][y] == '0'; // 下
    if (d == 1)
        return wall_v[x][y] == '0'; // 右
    if (d == 3)
        return wall_v[x][y - 1] == '0'; // 左
    return false;
}

struct State {
    int x, y, dir;
    bitset<400> visited;
    int score;
};

State apply_L(const State &s) {
    State t = s;
    t.dir = (t.dir + 3) % 4;
    return t;
}

State apply_R(const State &s) {
    State t = s;
    t.dir = (t.dir + 1) % 4;
    return t;
}

bool apply_F1(State &t) {
    if (!can_go(t.x, t.y, t.dir))
        return false;
    t.x += dx[t.dir];
    t.y += dy[t.dir];
    t.visited.set(t.x * N + t.y);
    t.score = t.visited.count();
    return true;
}

State apply_FW(const State &s) {
    State t = s;
    while (can_go(t.x, t.y, t.dir)) {
        t.x += dx[t.dir];
        t.y += dy[t.dir];
        t.visited.set(t.x * N + t.y);
    }
    t.score = t.visited.count();
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int AK, AM, AW;
    cin >> N >> AK >> AM >> AW;

    wall_v.resize(N);
    wall_h.resize(N - 1);
    for (int i = 0; i < N; i++)
        cin >> wall_v[i];
    for (int i = 0; i < N - 1; i++)
        cin >> wall_h[i];

    // 初期状態（左上・右向き）
    State init;
    init.x = 0;
    init.y = 0;
    init.dir = 1;
    init.visited.reset();
    init.visited.set(0);
    init.score = 1;

    vector<State> beam;
    beam.push_back(init);

    for (int step = 0; step < MAX_STEP; step++) {
        vector<State> cand;

        for (auto &s : beam) {
            // L
            cand.push_back(apply_L(s));
            // R
            cand.push_back(apply_R(s));
            // F1
            {
                State t = s;
                if (apply_F1(t))
                    cand.push_back(t);
            }
            // FW
            cand.push_back(apply_FW(s));
        }

        // 同一状態除去
        unordered_map<string, State> best;
        for (auto &s : cand) {
            string key;
            key.reserve(420);
            key.push_back(char(s.x));
            key.push_back(char(s.y));
            key.push_back(char(s.dir));
            for (int i = 0; i < N * N; i++)
                key.push_back(s.visited[i] ? '1' : '0');

            if (!best.count(key) || best[key].score < s.score)
                best[key] = s;
        }

        cand.clear();
        for (auto &p : best)
            cand.push_back(p.second);

        sort(cand.begin(), cand.end(),
             [](const State &a, const State &b) { return a.score > b.score; });

        if ((int)cand.size() > BEAM_WIDTH)
            cand.resize(BEAM_WIDTH);

        beam = cand;

        // 伸びなくなったら終了
        if (beam[0].score == beam.back().score) {
            // 全員同じスコアで停滞
            break;
        }
    }

    // 結果確認用（stderr）
    cerr << "Best visited = " << beam[0].score << " / " << N * N << "\n";

    // ---- ここから下は仮出力（通す用） ----
    // ロボット1台、何もしない周期
    cout << 1 << "\n";
    cout << 1 << " 0 0 R\n";
    cout << "L 0 L 0\n";

    // 壁追加なし
    for (int i = 0; i < N; i++)
        cout << string(N - 1, '0') << "\n";
    for (int i = 0; i < N - 1; i++)
        cout << string(N, '0') << "\n";

    return 0;
}