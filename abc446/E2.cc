void solve() {
    int m, a, b;
    cin >> m >> a >> b;

    map<long long, int> mp;
    int ans = 0;

    rep(i, m) {
        rep(j, m) {
            int x = i, y = j;

            vector<long long> path; // 今回の探索経路

            while (1) {
                long long key = 1LL * x * 1000000 + y;

                // すでに確定済み
                if (mp[key] == 2) {
                    for (auto k : path)
                        mp[k] = 2;
                    break;
                }
                if (mp[key] == -1) {
                    for (auto k : path)
                        mp[k] = -1;
                    break;
                }

                // 閉路検出 → 安全
                if (mp[key] == 1) {
                    for (auto k : path)
                        mp[k] = 2;
                    break;
                }

                // 探索中にする
                mp[key] = 1;
                path.push_back(key);

                // 0 到達 → 危険
                if (x == 0 || y == 0) {
                    for (auto k : path)
                        mp[k] = -1;
                    break;
                }

                // 次へ
                int z = (1LL * a * y + 1LL * b * x) % m;
                x = y;
                y = z;
            }
        }
    }

    // 最後に数える
    for (auto &[k, v] : mp) {
        if (v == 2)
            ans++;
    }

    cout << ans << endl;
}