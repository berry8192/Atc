// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

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
int d8x[]={1, 1, 0, -1, -1, -1, 0, 1}, d8y[]={0, 1, 1, 1, 0, -1, -1, -1};

//焼きなましの定数
double TIME_LIMIT=4950;
double start_temp=50.0;
double end_temp=10.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

//入力
int n, m;
int x[350], y[350];

// 構造体
struct Pos{
    int x;
    int y;

    Pos(){};
    Pos(int xx, int yy){
        x=xx;
        y=yy;
    }
    int weight(){
        return (x-n/2)*(x-n/2)+(y-n/2)*(y-n/2)+1;
    }

    void print(){
        cout<< "(" << x << ", " << y << ")";
    }
};

struct Point{
    int par;
    Pos pos;
    int next_to[8]={-1, -1, -1, -1, -1, -1, -1, -1};
    //8bit分をintで持つ
    int connectable=0;

    Point(){};
    Point(int parent, Pos position){
        par=parent;
        pos=position;
    }

    void print(){
        cout<< "parent: " << par SP;
        pos.print();
        cout<< " nextto: ";
        rep(i, 8) cout<< next_to[i] SP;
        cout<< endl;
    }
};

struct Paper{
    vector<vector<int>> inv_board;
    vector<Point> poi;
    int score=0;
    set<int> connectable;

    Paper(){
    }
    void init(){
        inv_board.resize(n, vector<int>(n, -1));
        rep(i, m){
            add_point(-1, Pos(x[i], y[i]));
        }
        search_line();
    }
    void add_point(int parent, Pos position){
        // idを振るための採番をしている
        inv_board[position.x][position.y]=poi.size();
        poi.emplace_back(Point(parent, position));
    }
    void search_line(){
        //左から右
        rep(i, n){
            int prev=-1;
            rep(j, n){
                int inv_idx=inv_board[i][j];
                if(inv_idx!=-1){
                    if(prev!=-1){
                        poi[inv_idx].next_to[4]=prev;
                        poi[prev].next_to[0]=inv_idx;
                    }
                    prev=inv_idx;
                }
            }
        }
        //上から下
        rep(i, n){
            int prev=-1;
            rep(j, n){
                int inv_idx=inv_board[j][i];
                if(inv_idx!=-1){
                    if(prev!=-1){
                        poi[inv_idx].next_to[2]=prev;
                        poi[prev].next_to[6]=inv_idx;
                    }
                    prev=inv_idx;
                }
            }
        }
        //左上から
        rep(i, n){
            int prev1=-1;
            int prev2=-1;
            rep(j, n-i){
                int inv_idx=inv_board[i+j][j];
                if(inv_idx!=-1){
                    if(prev1!=-1){
                        poi[inv_idx].next_to[3]=prev1;
                        poi[prev1].next_to[7]=inv_idx;
                    }
                    prev1=inv_idx;
                }
            }
            if(i==0) continue;
            rep(j, n-i){
                int inv_idx=inv_board[j][i+j];
                if(inv_idx!=-1){
                    if(prev2!=-1){
                        poi[inv_idx].next_to[3]=prev2;
                        poi[prev2].next_to[7]=inv_idx;
                    }
                    prev2=inv_idx;
                }
            }
        }
        //左下から
        rep(i, n){
            int prev1=-1;
            int prev2=-1;
            rep(j, n-i){
                int inv_idx=inv_board[n-1-(i+j)][j];
                if(inv_idx!=-1){
                    if(prev1!=-1){
                        poi[inv_idx].next_to[5]=prev1;
                        poi[prev1].next_to[1]=inv_idx;
                    }
                    prev1=inv_idx;
                }
            }
            if(i==0) continue;
            rep(j, n-i){
                int inv_idx=inv_board[n-1-j][i+j];
                if(inv_idx!=-1){
                    if(prev2!=-1){
                        poi[inv_idx].next_to[5]=prev2;
                        poi[prev2].next_to[1]=inv_idx;
                    }
                    prev2=inv_idx;
                }
            }
        }
    }
    void search_connect(){
        rep(i, poi.size()){
            rep(j, 8){
                if(poi[i].next_to[j]!=-1 && poi[i].next_to[(j+2)%8]!=-1){
                    if(point_add(poi[i].next_to[j], poi[i].next_to[(j+2)%8], i)){
                        poi[i].connectable+=(1<<j);
                        connectable.insert(i);
                    }
                }
            }
        }
    }
    bool point_add(int a, int b, int c){
        double x=(poi[a].pos.x+poi[b].pos.x)/2.0;
        double y=(poi[a].pos.y+poi[b].pos.y)/2.0;
        x+=x-poi[c].pos.x;
        y+=y-poi[c].pos.y;
        int xx=round(x);
        int yy=round(y);
        
        return ;
    }

    void print_board(){
        rep(i, n){
            rep(j, n){
                if(inv_board[i][j]==-1) cout<< -1 SP;
                else printf("%02d ", inv_board[i][j]);
            }
            cout<< endl;
        }
    }
    void print_point(){
        rep(i, poi.size()){
            poi[i].print();
        }
    }
    void print_out(){
        // cout<< mv.size() <<endl;
        // rep(i, mv.size()) cout<< mv[i].from.h SP << mv[i].from.w SP << mv[i].to.h SP << mv[i].to.w <<endl;
        // cout<< co.size() <<endl;
        // rep(i, co.size()) cout<< co[i].from.h SP << co[i].from.w SP << co[i].to.h SP << co[i].to.w <<endl;
    }
};

void inpt(){
    cin>> n >> m;
    rep(i, m) cin>> x[i] >> y[i];
}

int output_validation(Paper paper){
    int rtn=0;
    vector<vector<int>> test_board(n, vector<int>(n));
    return rtn;
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    Paper best;
    best.init();
    best.print_board();
    best.print_point();
return 0;

    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
        //cout<< lp <<endl;
    }

    //best.print_out();
    //cout<< "lp:" << lp <<endl;

	return 0;
}
// todo
