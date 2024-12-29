#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int ans = 0;

    for (int i = 0; i < s.size(); i++) {
        ans++;
        if (i + 1 < s.size() && s[i] == '0' && s[i + 1] == '0') {
            i++;
        }
    }

    cout << ans << endl;

    return 0;
}
