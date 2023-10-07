#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Player {
    int id;
    int wins;
};

bool comparePlayers(const Player& p1, const Player& p2) {
    if (p1.wins == p2.wins) {
        return p1.id < p2.id;
    }
    return p1.wins > p2.wins;
}

int main() {
    int N;
    cin >> N;
    
    vector<Player> players(N);
    
    // 入力を受け取り、勝利数をカウント
    for (int i = 0; i < N; i++) {
        players[i].id = i + 1;
        players[i].wins = 0;
        string s;
        cin >> s;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                if (s[j] == 'o') {
                    players[i].wins++;
                }
            }
        }
    }
    
    // 順位を計算してソート
    std::sort(players.begin(), players.end(), comparePlayers);
    
    // 順位を出力
    for (int i = 0; i < N; i++) {
        cout << players[i].id << " ";
    }
    
    return 0;
}
