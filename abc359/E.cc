#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    int n;
    vector<int> h;
    vector<int> ak;
    vector<long long> av;
    vector<long long> ans;
    map<int, vector<int>> mp;

    cin >> n;

    h.resize(n + 1);
    ak.resize(n + 1);
    av.resize(n + 1);
    ans.resize(n + 1);
    h[0] = 2000000000;
    for (int i = 0; i < n; i++) {
        cin >> h[i + 1];
    }
    ans[0] = 1;

    for (int i = n; i >= 0; i--) {
        auto itr = mp.lower_bound(h[i]);
        vector<int> del_keys;
        // cout << i << endl;
        while (itr != mp.begin()) {
            itr--;
            int key = (*itr).first;
            // cout << key << endl;
            vector<int> v = (*itr).second;
            for (int j = 0; j < v.size(); j++) {
                ak[v[j]] = i;
                av[v[j]] = 1LL * (v[j] - i) * key;
            }
            del_keys.push_back(key);
        }
        for (int j = 0; j < del_keys.size(); j++) {
            mp.erase(del_keys[j]);
        }
        mp[h[i]].push_back(i);
    }

    for (int i = 1; i < n + 1; i++) {
        ans[i] = ans[ak[i]] + av[i];
        // cout << ans[ak[i]] << " " << av[i] << endl;
    }

    for (int i = 1; i < n + 1; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}
