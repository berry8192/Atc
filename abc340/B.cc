#include <iostream>
#include <vector>

using namespace std;

int main() {
    int q, type, xk;
    vector<int> v;

    cin >> q;

    for (int i = 0; i < q; i++) {
        cin >> type >> xk;
        if (type == 1) {
            v.push_back(xk);
        } else {
            auto itr = v.end();
            for (int j = 0; j < xk; j++)
                itr--;
            cout << *itr << endl;
        }
    }

    return 0;
}
