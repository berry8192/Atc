#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, k;
vector<pair<int, int>> ab, cd;

bool compare_ab(const pair<int, int>& x, const pair<int, int>& y) {
    return x.first > y.first;
}

bool compare_cd(const pair<int, int>& x, const pair<int, int>& y) {
    return x.second > y.second;
}

bool check(double x) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        double a = ab[i].first, b = ab[i].second;
        if (a / b < x) continue;
        cnt += lower_bound(cd.begin(), cd.end(), make_pair((int)(x * b + 1e-9), 0), compare_cd) - cd.begin();
    }
    return cnt >= k;
}

int main() {
    cin >> n >> m >> k;
    ab.resize(n);
    cd.resize(m);
    for (int i = 0; i < n; i++) {
        cin >> ab[i].first >> ab[i].second;
    }
    for (int i = 0; i < m; i++) {
        cin >> cd[i].first >> cd[i].second;
    }
    sort(ab.begin(), ab.end(), compare_ab);
    sort(cd.begin(), cd.end(), compare_cd);

	double left = 0, right = 100;
for (int i = 0; i < 100; i++) {
    double mid = (left + right) / 2;
    if (check(mid)) {
        left = mid;
    } else {
        right = mid;
    }
}
printf("%.10f\n", left);
}