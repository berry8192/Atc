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
            for (int i = 0; i < block_cards.size(); i++) {
                int card = block_cards[i].first;
                pair<int, int> block_pos = block_cards[i].second;
                // ブロック外のこのカードを探す
                for (int k = 0; k < card_pos[card].size(); k++) {
                    int h = card_pos[card][k].first;
                    int w = card_pos[card][k].second;
                    if (removed_positions.count({h, w}))
                        continue;
                    if (h == block_pos.first && w == block_pos.second)
                        continue;

                    if (h < block_h || h >= bh_end || w < block_w ||
                        w >= bw_end) {
                        move_to(h, w);
                        pick_card(h, w);
                        break;
                    }
                }
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
