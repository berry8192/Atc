#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int h, w, sh, sw;
    ;
    cin >> h >> w >> sh >> sw;
    sh--;
    sw--;
    vector<string> c(h);
    string x;

    for (int i = 0; i < h; i++) {
        cin >> c[i];
    }
    cin >> x;

    for (int i = 0; i < x.size(); i++) {
        if (x[i] == 'L' && sw > 0 && c[sh][sw - 1] != '#')
            sw--;
        if (x[i] == 'U' && sh > 0 && c[sh - 1][sw] != '#')
            sh--;
        if (x[i] == 'R' && sw + 1 < w && c[sh][sw + 1] != '#')
            sw++;
        if (x[i] == 'D' && sh + 1 < h && c[sh + 1][sw] != '#')
            sh++;
    }

    cout << sh + 1 << " " << sw + 1 << endl;

    return 0;
}
