#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a, b, d;

    cin >> a >> b >> d;

    for (int i = a; i <= b; i += d) {
        cout << i << endl;
    }

    return 0;
}
