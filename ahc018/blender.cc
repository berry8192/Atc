// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
// using namespace atcoder;

//グローバル
int N, W, K, C;
int S[210][210]; //testtest

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> N >> W >> K >> C;
    rep(i, 200){
        rep(j, 200){
            cin>> S[i][j];
            cout<< S[i][j];
            if(j!=199) cout SP;
            else cout<< endl;
        }
    }
}

int main(){
    inpt();

    return 0;
}
