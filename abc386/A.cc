#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v(4);
    for (int i = 0; i < 4; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());
    if (v[0] == v[1] && v[1] != v[2] && v[2] == v[3]) {
        cout << "Yes" << endl;
    } else if (v[0] == v[1] && v[1] == v[2] && v[2] != v[3]) {
        cout << "Yes" << endl;
    } else if (v[0] != v[1] && v[1] == v[2] && v[2] == v[3]) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
