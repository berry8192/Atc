#include <bits/stdc++.h>
using namespace std;

int N, M, T;
vector<string> v_wall, h_wall;
const int di[] = {-1, 0, 1, 0};
const int dj[] = {0, 1, 0, -1};
vector<int> cage_r, cage_c;

bool canMove(int r, int c, int dir) {
    if (dir == 0)
        return r > 0 && h_wall[r - 1][c] == '0';
    if (dir == 1)
        return c < N - 1 && v_wall[r][c] == '0';
    if (dir == 2)
        return r < N - 1 && h_wall[r][c] == '0';
    return c > 0 && v_wall[r][c - 1] == '0';
}

vector<int> bfsPath(int sr, int sc, int tr, int tc) {
    if (sr == tr && sc == tc)
        return {};
    vector<vector<array<int, 3>>> prev(N,
                                       vector<array<int, 3>>(N, {-1, -1, -1}));
    queue<pair<int, int>> q;
    q.push({sr, sc});
    prev[sr][sc] = {sr, sc, -1};
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++) {
            if (!canMove(r, c, d))
                continue;
            int nr = r + di[d], nc = c + dj[d];
            if (prev[nr][nc][0] != -1)
                continue;
            prev[nr][nc] = {r, c, d};
            if (nr == tr && nc == tc) {
                // 復元
                vector<int> path;
                int cr = tr, cc = tc;
                while (!(cr == sr && cc == sc)) {
                    auto [pr, pc, dd] = prev[cr][cc];
                    path.push_back(dd);
                    cr = pr;
                    cc = pc;
                }
                reverse(path.begin(), path.end());
                return path;
            }
            q.push({nr, nc});
        }
    }
    return {};
}

struct RobotState {
    int r, c, dir;
    int holding;
    int basic_count;
    vector<pair<int, int>> ball_pos; // (-2,-2)=手持ち中, (-1,-1)=かご済み
    vector<bool> done;
};

// 基本操作1つ適用
void applyBasic(RobotState &s, char op) {
    s.basic_count++;
    if (op == 'F') {
        if (canMove(s.r, s.c, s.dir)) {
            s.r += di[s.dir];
            s.c += dj[s.dir];
        }
    } else if (op == 'R') {
        s.dir = (s.dir + 1) % 4;
    } else if (op == 'L') {
        s.dir = (s.dir + 3) % 4;
    } else if (op == 'S') {
        int on_ground = -1;
        for (int k = 0; k < M; k++) {
            if (s.ball_pos[k].first == s.r && s.ball_pos[k].second == s.c) {
                on_ground = k;
                break;
            }
        }
        if (s.holding == -1 && on_ground != -1) {
            s.holding = on_ground;
            s.ball_pos[on_ground] = {-2, -2};
        } else if (s.holding != -1 && on_ground == -1) {
            s.ball_pos[s.holding] = {s.r, s.c};
            if (s.r == cage_r[s.holding] && s.c == cage_c[s.holding]) {
                s.ball_pos[s.holding] = {-1, -1};
                s.done[s.holding] = true;
            }
            s.holding = -1;
        } else if (s.holding != -1 && on_ground != -1) {
            s.ball_pos[on_ground] = {-2, -2};
            s.ball_pos[s.holding] = {s.r, s.c};
            if (s.r == cage_r[s.holding] && s.c == cage_c[s.holding]) {
                s.ball_pos[s.holding] = {-1, -1};
                s.done[s.holding] = true;
            }
            s.holding = on_ground;
        }
    }
}

// 向き変更操作を出力に追加しながら適用
void addTurn(RobotState &s, int targetDir, vector<char> &ops) {
    int right = (targetDir - s.dir + 4) % 4;
    int left = (s.dir - targetDir + 4) % 4;
    if (right <= left) {
        for (int i = 0; i < right; i++) {
            ops.push_back('R');
            applyBasic(s, 'R');
        }
    } else {
        for (int i = 0; i < left; i++) {
            ops.push_back('L');
            applyBasic(s, 'L');
        }
    }
}

// macro_len個のFを移動する(Pで置換可能なら置換)
// macro_len==0 はマクロなし
void moveForward(RobotState &s, int steps, int macro_len, vector<char> &ops) {
    int remaining = steps;
    while (remaining > 0 && s.basic_count < T) {
        if (macro_len > 0 && remaining >= macro_len) {
            // Pで置換: macro_len回Fを1つずつシミュレート
            ops.push_back('P');
            for (int i = 0; i < macro_len && s.basic_count < T; i++) {
                applyBasic(s, 'F');
            }
            remaining -= macro_len;
        } else {
            ops.push_back('F');
            applyBasic(s, 'F');
            remaining--;
        }
    }
}

// (tr,tc)まで移動してS操作
void moveAndSwap(RobotState &s, int tr, int tc, int macro_len,
                 vector<char> &ops) {
    vector<int> path = bfsPath(s.r, s.c, tr, tc);

    int i = 0;
    while (i < (int)path.size() && s.basic_count < T) {
        int dir = path[i];

        // 同じ方向のF連続数を数える
        int frun = 0;
        while (i + frun < (int)path.size() && path[i + frun] == dir)
            frun++;

        // 向き変更
        if (s.basic_count >= T)
            break;
        addTurn(s, dir, ops);

        // 前進
        if (s.basic_count >= T)
            break;
        moveForward(s, frun, macro_len, ops);

        i += frun;
    }

    if (s.basic_count < T) {
        ops.push_back('S');
        applyBasic(s, 'S');
    }
}

// Greedy解を生成する
// macro_len > 0 の場合、先頭にM[F*macro_len]Mを付けてPを使う
vector<char> solveGreedy(const vector<pair<int, int>> &ball_pos_init,
                         int macro_len) {
    RobotState s;
    s.r = 0;
    s.c = 0;
    s.dir = 1;
    s.holding = -1;
    s.basic_count = 0;
    s.ball_pos = ball_pos_init;
    s.done.assign(M, false);

    vector<char> ops;

    // マクロ登録
    if (macro_len > 0) {
        ops.push_back('M');
        for (int i = 0; i < macro_len && s.basic_count < T; i++) {
            ops.push_back('F');
            applyBasic(s, 'F'); // 記録中も実行される
        }
        ops.push_back('M');
        // ロボットはマクロ登録中に動いてしまうので(0,0)から動いている
        // 登録後に元の位置(0,0)へ戻す
        // BFSで戻る
        int home_r = 0, home_c = 0;
        if (s.r != home_r || s.c != home_c) {
            // macro_lenのFで右に移動しているはずなので左に戻る
            // ただし壁がある可能性があるのでBFSで戻る
            vector<int> back = bfsPath(s.r, s.c, home_r, home_c);
            for (int d : back) {
                if (s.basic_count >= T)
                    break;
                addTurn(s, d, ops);
                if (s.basic_count >= T)
                    break;
                ops.push_back('F');
                applyBasic(s, 'F');
            }
        }
    }

    // Greedy: 手ぶら→最寄りボール、持ち→かご
    while (s.basic_count < T) {
        bool all_done = true;
        for (int k = 0; k < M; k++)
            if (!s.done[k]) {
                all_done = false;
                break;
            }
        if (all_done)
            break;

        if (s.holding == -1) {
            // 最寄りの未完了ボールを探す
            int best = -1, bestDist = INT_MAX;
            for (int k = 0; k < M; k++) {
                if (s.done[k])
                    continue;
                vector<int> path = bfsPath(s.r, s.c, s.ball_pos[k].first,
                                           s.ball_pos[k].second);
                if ((int)path.size() < bestDist) {
                    bestDist = (int)path.size();
                    best = k;
                }
            }
            if (best == -1)
                break;
            moveAndSwap(s, s.ball_pos[best].first, s.ball_pos[best].second,
                        macro_len, ops);
        } else {
            int k = s.holding;
            moveAndSwap(s, cage_r[k], cage_c[k], macro_len, ops);
        }
    }

    return ops;
}

// 操作列の中で最長のF連続区間の長さを返す(最初のscan_len文字のみ見る)
int findBestMacroLen(const vector<char> &ops, int scan_len) {
    int best = 0, cur = 0;
    int limit = min((int)ops.size(), scan_len);
    for (int i = 0; i < limit; i++) {
        if (ops[i] == 'F') {
            cur++;
            best = max(best, cur);
        } else {
            cur = 0;
        }
        if (best >= N / 2)
            break;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> T;
    v_wall.resize(N);
    for (auto &s : v_wall)
        cin >> s;
    h_wall.resize(N - 1);
    for (auto &s : h_wall)
        cin >> s;

    cage_r.resize(M);
    cage_c.resize(M);
    vector<pair<int, int>> ball_pos_init(M);
    for (int k = 0; k < M; k++) {
        int br, bc;
        cin >> br >> bc >> cage_r[k] >> cage_c[k];
        ball_pos_init[k] = {br, bc};
    }

    // フェーズ1: マクロなし愚直解
    vector<char> naive = solveGreedy(ball_pos_init, 0);

    // フェーズ2: 最初の4N文字から最長F連続を探してマクロ長決定
    int macro_len = findBestMacroLen(naive, 4 * N);

    vector<char> result = naive; // デフォルトはnaive

    if (macro_len >= 2) {
        // フェーズ3: マクロありで再構築
        vector<char> with_macro = solveGreedy(ball_pos_init, macro_len);

        // スコア比較: 短い方を採用(ただし全完了しているか確認)
        // 簡易チェック: ops長で比較
        if (with_macro.size() < naive.size()) {
            result = with_macro;
        }
    }

    for (char c : result)
        cout << c << '\n';
    return 0;
}
