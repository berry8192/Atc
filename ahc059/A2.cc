#include <bits/stdc++.h>
using namespace std;

int N;
const int BLOCK_SIZE = 5;
vector<vector<int>> grid;
map<int, vector<pair<int, int>>> card_pos;

string ans;
int cur_h = 0, cur_w = 0;
set<pair<int, int>> removed_positions; // 既に回収した位置
stack<int> deck;                       // 山札

void move_to(int th, int tw) {
    while (cur_h < th) {
        ans += 'D';
        cur_h++;
    }
    while (cur_h > th) {
        ans += 'U';
        cur_h--;
    }
    while (cur_w < tw) {
        ans += 'R';
        cur_w++;
    }
    while (cur_w > tw) {
        ans += 'L';
        cur_w--;
    }
}

void pick_card(int h, int w) {
    ans += 'Z';
    int card = grid[h][w];
    removed_positions.insert({h, w});

    // 山札の最上位と同じカードなら両方消える
    if (!deck.empty() && deck.top() == card) {
        deck.pop();
    } else {
        deck.push(card);
    }
}

// 経路の総距離を計算
int calc_path_distance(int start_h, int start_w,
                       const vector<pair<int, int>> &path, int goal_h,
                       int goal_w) {
    int dist = 0;
    int h = start_h, w = start_w;

    for (int i = 0; i < path.size(); i++) {
        dist += abs(h - path[i].first) + abs(w - path[i].second);
        h = path[i].first;
        w = path[i].second;
    }

    dist += abs(h - goal_h) + abs(w - goal_w);
    return dist;
}

// 焼きなまし法で経路を最適化
vector<int>
optimize_collection_order(int start_h, int start_w,
                          const vector<pair<int, pair<int, int>>> &targets,
                          int goal_h, int goal_w) {
    if (targets.empty())
        return vector<int>();

    int n = targets.size();
    vector<int> order(n);
    for (int i = 0; i < n; i++)
        order[i] = i;

    // 初期解: 貪欲法
    vector<int> current_order;
    vector<bool> used(n, false);
    int ch = start_h, cw = start_w;

    for (int i = 0; i < n; i++) {
        int best = -1;
        int best_dist = 1e9;
        for (int j = 0; j < n; j++) {
            if (used[j])
                continue;
            int dist = abs(ch - targets[j].second.first) +
                       abs(cw - targets[j].second.second);
            if (dist < best_dist) {
                best_dist = dist;
                best = j;
            }
        }
        current_order.push_back(best);
        used[best] = true;
        ch = targets[best].second.first;
        cw = targets[best].second.second;
    }

    vector<pair<int, int>> path;
    for (int idx : current_order) {
        path.push_back(targets[idx].second);
    }
    int best_dist = calc_path_distance(start_h, start_w, path, goal_h, goal_w);
    vector<int> best_order = current_order;

    // 焼きなまし
    mt19937 rng(42);
    double temp = 100.0;
    double temp_end = 1.0;
    int iterations = min(10000, n * n * 100);

    for (int iter = 0; iter < iterations; iter++) {
        double progress = (double)iter / iterations;
        temp = temp_end + (temp - temp_end) * (1.0 - progress);

        vector<int> new_order = current_order;

        // 2-opt or swap
        if (n >= 2) {
            int i = rng() % n;
            int j = rng() % n;
            if (i > j)
                swap(i, j);

            if (rng() % 2 == 0 && i != j) {
                // 2-opt
                reverse(new_order.begin() + i, new_order.begin() + j + 1);
            } else {
                // swap
                swap(new_order[i], new_order[j]);
            }
        }

        path.clear();
        for (int idx : new_order) {
            path.push_back(targets[idx].second);
        }
        int new_dist =
            calc_path_distance(start_h, start_w, path, goal_h, goal_w);

        double delta = new_dist - best_dist;
        if (delta < 0 ||
            exp(-delta / temp) > (double)(rng() % 10000) / 10000.0) {
            current_order = new_order;
            if (new_dist < best_dist) {
                best_dist = new_dist;
                best_order = new_order;
            }
        }
    }

    return best_order;
}

int main() {
    cin >> N;
    grid.resize(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            card_pos[grid[i][j]].push_back({i, j});
        }
    }

    // ブロックごとに処理
    for (int block_h = 0; block_h < N; block_h += BLOCK_SIZE) {
        for (int block_w = 0; block_w < N; block_w += BLOCK_SIZE) {
            int bh_end = min(block_h + BLOCK_SIZE, N);
            int bw_end = min(block_w + BLOCK_SIZE, N);

            // フェーズ1: ブロック内のカードを記録（回収しない）
            vector<pair<int, pair<int, int>>> block_cards; // {card_num, {h, w}}
            set<int> processed_cards; // 処理済みのカード番号

            for (int h = block_h; h < bh_end; h++) {
                for (int w = block_w; w < bw_end; w++) {
                    if (removed_positions.count({h, w}))
                        continue;

                    int card = grid[h][w];

                    // 既に処理済みのカードはスキップ
                    if (processed_cards.count(card))
                        continue;

                    // このカードの2枚の位置を確認
                    int count_in_block = 0;
                    vector<pair<int, int>> in_block_positions;

                    for (int k = 0; k < card_pos[card].size(); k++) {
                        int ph = card_pos[card][k].first;
                        int pw = card_pos[card][k].second;
                        if (removed_positions.count({ph, pw}))
                            continue;

                        if (ph >= block_h && ph < bh_end && pw >= block_w &&
                            pw < bw_end) {
                            count_in_block++;
                            in_block_positions.push_back({ph, pw});
                        }
                    }

                    // 2枚ともブロック内にある場合、1枚だけ回収
                    if (count_in_block == 2) {
                        move_to(in_block_positions[0].first,
                                in_block_positions[0].second);
                        pick_card(in_block_positions[0].first,
                                  in_block_positions[0].second);
                        // もう1枚の位置を記録
                        block_cards.push_back({card, in_block_positions[1]});
                        processed_cards.insert(card);
                    } else if (count_in_block == 1) {
                        // 1枚だけブロック内 → 位置だけ記録
                        block_cards.push_back({card, {h, w}});
                        processed_cards.insert(card);
                    }
                }
            }

            // フェーズ2: ブロック外から対応するカードを回収
            // 回収すべきカードの位置を収集
            vector<pair<int, pair<int, int>>>
                outside_targets; // {card_num, {h, w}}
            for (int i = 0; i < block_cards.size(); i++) {
                int card = block_cards[i].first;
                pair<int, int> block_pos = block_cards[i].second;

                for (int k = 0; k < card_pos[card].size(); k++) {
                    int h = card_pos[card][k].first;
                    int w = card_pos[card][k].second;
                    if (removed_positions.count({h, w}))
                        continue;
                    if (h == block_pos.first && w == block_pos.second)
                        continue;

                    if (h < block_h || h >= bh_end || w < block_w ||
                        w >= bw_end) {
                        outside_targets.push_back({card, {h, w}});
                        break;
                    }
                }
            }

            // ゴール地点（ブロックの中心）
            int goal_h = block_h + BLOCK_SIZE / 2;
            int goal_w = block_w + BLOCK_SIZE / 2;

            // 焼きなまし法で最適な回収順序を決定
            vector<int> optimal_order = optimize_collection_order(
                cur_h, cur_w, outside_targets, goal_h, goal_w);

            // 最適順序でカードを回収
            for (int idx : optimal_order) {
                int h = outside_targets[idx].second.first;
                int w = outside_targets[idx].second.second;
                move_to(h, w);
                pick_card(h, w);
            }

            // フェーズ3: 山札が空になるまでブロック内のカードを回収
            while (!deck.empty()) {
                int top_card = deck.top();
                bool found = false;

                // block_cardsから山札の最上位と一致するカードを探す
                for (int i = 0; i < block_cards.size(); i++) {
                    int card = block_cards[i].first;
                    pair<int, int> pos = block_cards[i].second;

                    if (removed_positions.count(pos))
                        continue;

                    if (card == top_card) {
                        move_to(pos.first, pos.second);
                        pick_card(pos.first, pos.second);
                        found = true;
                        break;
                    }
                }

                // 見つからなかった場合は無限ループを防ぐために終了
                if (!found) {
                    break;
                }
            }
        }
    }

    for (char c : ans) {
        cout << c << endl;
    }

    return 0;
}
