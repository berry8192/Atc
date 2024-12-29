#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, char>> v(m);

    for (int i = 0; i < m; i++) {
        int h, w;
        char c;
        cin >> h >> w >> c;
        v[i] = make_tuple(h, w, c);
    }

    sort(v.begin(), v.end());
    int min_white = n + 1;
    for (int i = 0; i < m; i++) {
        // cout<< v[i].first << v[i].second <<endl;
        int h, w;
        char c;
        h = get<0>(v[i]);
        w = get<1>(v[i]);
        c = get<2>(v[i]);
        if (c == 'W') {
            min_white = min(min_white, w);
        } else if (min_white <= w) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;

    return 0;
}
