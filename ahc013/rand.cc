#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
int dir_h[]={0, -1, 0, 1}, dir_w[]={-1, 0, 1, 0};

//焼きなましの定数
double TIME_LIMIT=2.9;
double start_temp=50.0;
double end_temp=10.0;

//入力
int n, k;
vector<vector<int>> c;

struct Pos{
    int h;
    int w;

    Pos();
    Pos(int x, int y){
        h=x;
        w=y;
    }
};

struct Move{
    Pos from;
    Pos to;

    Move();
    Move(Pos x, Pos y){
        from=x;
        to=y;
    }
};

struct Cone{
    Pos from;
    Pos to;

    Cone();
    Cone(Pos x, Pos y){
        from=x;
        to=y;
    }
};

// room struct
struct Room{
    vector<vector<int>> board;
    vector<Move> mv;
    vector<Cone> co;
    int score=0;

    Room(){
        board.resize(n);
        rep(i, n) board[i].resize(n);
    }
    void init(){
        rep(i, n){
            rep(j, n){
                board[i][j]=c[i][j];
            }
        }
    }
    void print(){
        cout<< mv.size() <<endl;
        rep(i, mv.size()) cout<< mv[i].from.h SP << mv[i].from.w SP << mv[i].to.h SP << mv[i].to.w <<endl;
        cout<< co.size() <<endl;
        rep(i, co.size()) cout<< co[i].from.h SP << co[i].from.w SP << co[i].to.h SP << co[i].to.w <<endl;
    }
};

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=10;
mt19937 mt(seed);

int main(){
    cin>> n >> k;
    c.resize(n);
    rep(i, n) c[i].resize(n);

    rep(i, n){
        string tmp;
        cin>> tmp;
        rep(j, n){
            c[i][j]=int(tmp[j]-'0');
        }
    }

    Room cur;
    cur.init();
    cur.print();

	return 0;
}