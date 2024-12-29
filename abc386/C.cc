#include <iostream>
#include <string>

using namespace std;

int main() {
    int k;
    cin >> k;
    string s, t;
    cin >> s;
    cin >> t;

    if (s.size() != t.size()) {
        if (s.size() < t.size()) {
            swap(s, t);
        }
        string s2 = s;
        s2.pop_back();
        if (s2 == t) {
            cout << "Yes" << endl;
            return 0;
        }
        int pos = 0;
        for (int i = 0; i < s.size(); i++) {
            if (pos == t.size()) {
                cout << "No" << endl;
                return 0;
            }
            if (s[i] == t[pos]) {
                pos++;
            }
        }
        if (pos == s.size() - 1) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    } else if (s.size() == t.size()) {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) {
                cnt++;
            }
        }
        if (cnt <= 1) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        return 0;
    }
    cout << "No" << endl;

    return 0;
}
