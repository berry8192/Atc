#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, AK, AM, AW;
    cin >> N >> AK >> AM >> AW;

    // wall_v[i][j]: (i,j)-(i,j+1)間の壁 (N行, N-1列)
    vector<string> wall_v(N), wall_h(N - 1);
    for (int i = 0; i < N; i++) cin >> wall_v[i];
    for (int i = 0; i < N - 1; i++) cin >> wall_h[i];

    // 愚直解: 全マスに1台ずつ、m=1のロボットを配置
    // 右手法: 前方が空いていたら前進、壁なら右折
    // 状態2: s=0で前進試行、壁ならs=1に遷移して右折、s=1で右折してs=0に戻る
    // これで壁にぶつかるとUターンする動き
    int K = N * N;
    cout << K << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // m=1, その場で右回転 (確実に警備)
            cout << "1 " << i << " " << j << " U\n";
            cout << "R 0 R 0\n";
        }
    }
    // 壁追加なし
    for (int i = 0; i < N; i++) cout << string(N - 1, '0') << "\n";
    for (int i = 0; i < N - 1; i++) cout << string(N, '0') << "\n";

    return 0;
}
