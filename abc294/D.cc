#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    // 未呼び出しの人を管理する優先度付きキュー
    set<int> st;

    // 最後に呼び出した人の番号
    int last_called = 1;

    for (int i = 0; i < q; i++) {
        int event;
        cin >> event;

        if (event == 1) { // 未呼び出しの人のうち最も小さい番号を呼び出す
            st.insert(last_called);
			last_called++;
        } else if (event == 2) { // x番目の人を呼び出す
            int x;
            cin >> x;
            st.erase(x);
        } else { // 呼び出されたことがある人のうち最も小さい番号を呼び出す
            cout << *st.begin() << endl;
        }
    }

    return 0;
}
