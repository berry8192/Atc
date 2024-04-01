#include <bits/stdc++.h>

using namespace std;

unsigned int randxor() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629,
                        w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}
template <typename T> T rand(T a, T b) {
    assert(a <= b);
    long long len = (b - a + 1);
    return randxor() % len + a;
}

int main() {
    int loop = 1000000;
    int W, D, N;
    int a[50][50];
    cin >> W >> D >> N;

    vector<double> v(W);
    for (int lp = 0; lp < loop; lp++) {
        vector<int> tmp = {0, W * W};
        for (int i = 0; i < N - 1; i++) {
            tmp.push_back(rand(0, W * W - 1));
        }
        sort(tmp.begin(), tmp.end());
        vector<int> tmp2;
        for (int i = 0; i < N; i++) {
            tmp2.push_back(tmp[i + 1] - tmp[i]);
        }
        sort(tmp2.begin(), tmp2.end());
        for (int i = 0; i < N; i++) {
            v[i] += tmp2[i];
            // cout << v[i] << " ";
        }
        // cout << endl;
    }
    cout << fixed << setprecision(12);
    for (int i = 0; i < N; i++) {
        v[i] /= loop;
        cout << v[i] << " ";
    }
    cout << endl;

    return 0;
}
