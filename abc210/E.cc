#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> v(M);

    for (int i = 0; i < M; i++) {
        int A, C;
        cin >> A >> C;
        v[i] = make_pair(C, A);
    }

    sort(v.begin(), v.end());

    long long ans=0;
    for (int i = 0; i < M; i++) {
        // cout << v[i].second << " " << v[i].first << endl;
        long long a, b;
        a=__gcd(uint(N), uint(v[i].second));
        b=N/a-1;
        N=a;
        ans+=a*b*v[i].first;
    }
    if(N!=1) ans=-1;
    cout<< ans <<endl;

    return 0;
}
