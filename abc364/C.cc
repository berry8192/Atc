#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    long long x, y;

    cin >> n >> x >> y;
    vector<int> a(n), b(n);

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());
    for (int i = 0; i < n; i++) {
        x -= a[i];
        y -= b[i];
        if (x < 0 || y < 0) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << n << endl;

    return 0;
}
