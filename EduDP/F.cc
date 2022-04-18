#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
//using mint = modint=998244353;

// LCS 最長増加部分列
string LCS(const string& a, const string& b) {
    const int n = a.size(), m = b.size();
    vector< vector<int> > X(n+1, vector<int>(m+1));
    vector< vector<int> > Y(n+1, vector<int>(m+1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                X[i+1][j+1] = X[i][j] + 1;
                Y[i+1][j+1] = 0;
            } else if (X[i+1][j] < X[i][j+1]) {
                X[i+1][j+1] = X[i][j+1];
                Y[i+1][j+1] = +1;
            } else {
                X[i+1][j+1] = X[i+1][j];
                Y[i+1][j+1] = -1;
            }
        }
    }
    string c;
    for (int i = n, j = m; i > 0 && j > 0; ) {
        if      (Y[i][j] > 0) --i;
        else if (Y[i][j] < 0) --j;
        else { c.push_back(a[i-1]); --i; --j; }
    }
    reverse(c.begin(), c.end());
    return c;
}

int main(){

	string s, t;

	cin>> s >> t;

	cout<< LCS(s, t) << endl;
 
	return 0;
}