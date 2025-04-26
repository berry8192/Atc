#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// 定数
int N;
int M;
const int di[4] = {-1, 1, 0, 0}; // U, D, L, R
const int dj[4] = {0, 0, -1, 1};
const char dir_char[4] = {'U', 'D', 'L', 'R'};

// グローバル入力
int start_i, start_j;
vector<pair<int, int>> goals(40);

// スケートリンクの状態
struct Link {
    vector<vector<bool>> block;
    int ci, cj;             // 現在位置
    vector<string> actions; // 出力用アクション列

    Link(int si, int sj) : ci(si), cj(sj), block(N, vector<bool>(N, false)) {}

    // 愚直に移動だけでゴールを目指す
    void gutyoku() {
        for (const auto &[gi, gj] : goals) {
            move_naive(gi, gj);
        }
    }

    // 単純な移動 (上下左右で1歩ずつ移動)
    void move_naive(int ti, int tj) {
        while (ci != ti || cj != tj) {
            if (ci < ti) {
                ci++;
                actions.push_back("M D");
            } else if (ci > ti) {
                ci--;
                actions.push_back("M U");
            } else if (cj < tj) {
                cj++;
                actions.push_back("M R");
            } else if (cj > tj) {
                cj--;
                actions.push_back("M L");
            }
        }
    }

    void output_actions() const {
        for (const auto &act : actions) {
            cout << act << '\n';
        }
    }
};

int main() {
    // 入力読み取り
    cin >> N >> M;
    cin >> start_i >> start_j;
    for (int i = 0; i < M; ++i) {
        cin >> goals[i].first >> goals[i].second;
    }

    // Linkインスタンス生成し、愚直移動実行
    Link link(start_i, start_j);
    link.gutyoku();

    // 行動列出力
    link.output_actions();

    return 0;
}
