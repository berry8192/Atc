#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, a = 0, b = 0, c = 0;

    cin >> n;

    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        c = b;
        b = a;
        a = 0;
        if (t[1] == 'w')
            a = 1;
        if (b + c == 2) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}
