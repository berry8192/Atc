#include <iostream>
#include <map>
#include <set>

using namespace std;

int main() {
    long long n, ans = 0;
    map<long long, long long> mp;
    set<long long> st;

    cin >> n;
    mp[n] = 1;
    st.insert(n);

    while (!st.empty()) {
        auto itr = st.rbegin();
        long long key = *itr;
        long long val = mp[key];
        // cout<< key << " " << val <<endl;
        if (key == 1)
            break;
        mp[key / 2] += val;
        mp[(key + 1) / 2] += val;
        st.insert(key / 2);
        st.insert((key + 1) / 2);
        ans += key * val;
        st.erase(key);
    }

    cout << ans << endl;

    return 0;
}
