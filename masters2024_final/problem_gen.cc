#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

int si, sj, ti, tj, tmp;
int dis[20][20];
vector<string> h(20), v(19);
queue<int> qh, qw;
vector<char> ad;
vector<int> al;

int main(){
    
    srand((unsigned)time( NULL ));
    si=int(rand())%5;
    sj=int(rand())%5;
    ti=int(rand())%5+15;
    tj=int(rand())%5+15;
    double p=0.2;
    cout<< si SP << sj SP << ti SP << tj SP << p <<endl;

    rep(i, 20){
        rep(j, 19){
            tmp=int(rand())%4/3;
            cout<< tmp;
        }
        cout<< endl;
    }
    rep(i, 19){
        rep(j, 20){
            tmp=int(rand())%4/3;
            cout<< tmp;
        }
        cout<< endl;
    }
    cout<< endl;

	return 0;
}