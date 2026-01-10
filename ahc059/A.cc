#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> grid;
vector<pair<int, int>> card_pos[200]; // 各カード番号の位置を保存
string ans;

// 現在位置から目標位置への最短経路を求めて移動
void move_to(int cur_h, int cur_w, int tar_h, int tar_w) {
    // 縦方向の移動
    while (cur_h < tar_h) {
        ans += 'D';
        cur_h++;
    }
    while (cur_h > tar_h) {
        ans += 'U';
        cur_h--;
    }
    // 横方向の移動
    while (cur_w < tar_w) {
        ans += 'R';
        cur_w++;
    }
    while (cur_w > tar_w) {
        ans += 'L';
        cur_w--;
    }
}

int main() {
    cin >> N;
    grid.resize(N, vector<int>(N));

    // グリッドの入力とカード位置の記録
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            card_pos[grid[i][j]].push_back({i, j});
        }
    }

    // 現在位置
    int cur_h = 0, cur_w = 0;

    // 0番からN*N/2-1番まで順番に回収
    for (int card_num = 0; card_num < N * N / 2; card_num++) {
        // 1枚目のカードの位置に移動
        int h1 = card_pos[card_num][0].first;
        int w1 = card_pos[card_num][0].second;
        move_to(cur_h, cur_w, h1, w1);
        cur_h = h1;
        cur_w = w1;

        // 1枚目を取る
        ans += 'Z';

        // 2枚目のカードの位置に移動
        int h2 = card_pos[card_num][1].first;
        int w2 = card_pos[card_num][1].second;
        move_to(cur_h, cur_w, h2, w2);
        cur_h = h2;
        cur_w = w2;

        // 2枚目を取る（自動的にペアが消える）
        ans += 'Z';
    }

    // 結果を出力
    for (char c : ans) {
        cout << c << endl;
    }

    return 0;
}
