// score1.cc — ちょうど 1 点になる出力を作る
//
// 戦略:
//   Turn1: op0(r,r,10) を r=0..9 並列 → 全出発線を空、siding r に Y[r][0..9]
//   Turn2: op1(g, rA, 1) → 線 g 位置0 に誤グループの車両 (0点)
//   Turn3: op1(g, rB, 1) → 線 g 位置1 に g 群の車両、ただし %10 != 1 (1点)
//   その他の出発線は空、残車両は siding 上 → 採点対象外。
// 合計: ちょうど 1 点。

#include <bits/stdc++.h>
using namespace std;

int main() {
    int R; cin >> R;
    vector<vector<int>> Y(R, vector<int>(10));
    for (int r = 0; r < R; r++)
        for (int c = 0; c < 10; c++)
            cin >> Y[r][c];

    int g = -1, rA = -1, rB = -1;
    for (int gg = 0; gg < R && g < 0; gg++) {
        for (int b = 0; b < R; b++) {
            if (Y[b][0] / 10 != gg) continue;
            if (Y[b][0] % 10 == 1) continue;
            for (int a = 0; a < R; a++) {
                if (a == b) continue;
                if (Y[a][0] / 10 == gg) continue;
                g = gg; rA = a; rB = b;
                break;
            }
            if (g >= 0) break;
        }
    }

    if (g < 0) {
        // 極めて稀な fallback: T=0 (この場合の点数は入力依存)
        cout << 0 << "\n";
        return 0;
    }

    cout << 3 << "\n";
    cout << R << "\n";
    for (int r = 0; r < R; r++) cout << "0 " << r << " " << r << " 10\n";
    cout << 1 << "\n";
    cout << "1 " << g << " " << rA << " 1\n";
    cout << 1 << "\n";
    cout << "1 " << g << " " << rB << " 1\n";
    return 0;
}
