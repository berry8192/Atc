#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>
using namespace std;

// 定数
int N, M;
const int di[4] = {-1, 1, 0, 0}; // U, D, L, R
const int dj[4] = {0, 0, -1, 1};
const char dir_char[4] = {'U', 'D', 'L', 'R'};

// グローバル入力
int start_i, start_j;
vector<pair<int, int>> goals(40);

// 乱数生成器
random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> chance(1, 100);

// スケートリンクの状態
struct Link {
    vector<vector<bool>> block;
    int ci, cj;
    vector<string> actions;

    Link(int si, int sj) : ci(si), cj(sj), block(N, vector<bool>(N, false)) {}

    void solve() {
        for (const auto &[gi, gj] : goals) {
            move_with_slide(gi, gj);
        }
    }

    void move_with_slide(int ti, int tj) {
        struct State {
            int i, j;
            vector<string> path;
        };

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<State> q;
        q.push({ci, cj, {}});
        visited[ci][cj] = true;

        while (!q.empty()) {
            State s = q.front();
            q.pop();

            if (s.i == ti && s.j == tj) {
                for (const string &a : s.path) {
                    maybe_toggle_block();
                    actions.push_back(a);
                    maybe_toggle_block();
                }
                ci = ti;
                cj = tj;
                return;
            }

            // 普通の移動 (M)
            for (int d = 0; d < 4; ++d) {
                int ni = s.i + di[d], nj = s.j + dj[d];
                if (is_in(ni, nj) && !block[ni][nj] && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    auto new_path = s.path;
                    new_path.push_back("M "s + dir_char[d]);
                    q.push({ni, nj, new_path});
                }
            }

            // 滑走 (S)
            for (int d = 0; d < 4; ++d) {
                int ni = s.i, nj = s.j;
                while (is_in(ni + di[d], nj + dj[d]) &&
                       !block[ni + di[d]][nj + dj[d]]) {
                    ni += di[d];
                    nj += dj[d];
                }
                if ((ni != s.i || nj != s.j) && !visited[ni][nj]) {
                    visited[ni][nj] = true;
                    auto new_path = s.path;
                    new_path.push_back("S "s + dir_char[d]);
                    q.push({ni, nj, new_path});
                }
            }
        }
    }

    void maybe_toggle_block() {
        if (chance(mt) <= 5) { // 5% の確率でブロック操作
            for (int d = 0; d < 4; ++d) {
                int ni = ci + di[d], nj = cj + dj[d];
                if (is_in(ni, nj)) {
                    block[ni][nj] = !block[ni][nj];
                    actions.push_back("A "s + dir_char[d]);
                    break;
                }
            }
        }
    }

    bool is_in(int i, int j) { return 0 <= i && i < N && 0 <= j && j < N; }

    void output_actions() const {
        for (const auto &act : actions) {
            cout << act << '\n';
        }
    }
};

int main() {
    cin >> N >> M;
    cin >> start_i >> start_j;
    for (int i = 0; i < M; ++i) {
        cin >> goals[i].first >> goals[i].second;
    }

    Link link(start_i, start_j);
    link.solve();
    link.output_actions();

    return 0;
}
