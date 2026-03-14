#include <bits/stdc++.h>
using namespace std;

const int N = 200;
int A[N][N];

struct P {
    int x, y;
};

vector<P> path;

bool adj(P a, P b) { return max(abs(a.x - b.x), abs(a.y - b.y)) == 1; }

long long calc_delta(int l, int r) {
    long long delta = 0;
    for (int k = l; k <= r; k++) {
        int nx = l + r - k;
        delta += (long long)(nx - k) * A[path[k].x][path[k].y];
    }
    return delta;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];

    // 蛇行
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++)
                path.push_back({i, j});
        } else {
            for (int j = n - 1; j >= 0; j--)
                path.push_back({i, j});
        }
    }

    int M = n * n;

    auto start = chrono::steady_clock::now();

    double TL = 2.9;

    mt19937 rng(0);

    while (true) {

        auto now = chrono::steady_clock::now();
        double t = chrono::duration<double>(now - start).count();
        if (t > TL)
            break;

        int l = rng() % M;
        int len = rng() % 100;
        int r = l + len;
        if (r >= M)
            continue;
        if (l == 0 || r == M - 1)
            continue;

        P a = path[l - 1];
        P b = path[l];
        P c = path[r];
        P d = path[r + 1];

        if (!adj(a, c))
            continue;
        if (!adj(b, d))
            continue;

        long long delta = calc_delta(l, r);

        double temp = 1000 * (1 - t / TL);

        if (delta > 0 || exp(delta / temp) > (double)rng() / rng.max()) {
            reverse(path.begin() + l, path.begin() + r + 1);
        }
    }

    for (auto &p : path)
        cout << p.x << " " << p.y << "\n";
}