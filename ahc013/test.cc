#include <bits/stdc++.h>
#include <experimental/filesystem>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
namespace fs = std::filesystem;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
int dir_h[]={0, -1, 0, 1}, dir_w[]={-1, 0, 1, 0};

//焼きなましの定数
double TIME_LIMIT=2.9;
double start_temp=50.0;
double end_temp=10.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=10;
mt19937 mt(seed);

// 構造体
struct Pos{
    int h;
    int w;

    Pos(){};
    Pos(int x, int y){
        h=x;
        w=y;
    }
    void print(){
        cout<< "(" << h << ", " << w << ")";
    }
};

//入力
int n, k;
vector<vector<int>> c;
vector<vector<Pos>> cpu;

struct Move{
    Pos from;
    Pos to;

    Move(){};
    Move(Pos x, Pos y){
        from=x;
        to=y;
    }
    void print(){
        from.print();
        cout<< "->";
        to.print();
    }
};

struct Cone{
    Pos from;
    Pos to;

    Cone(){};
    Cone(Pos x, Pos y){
        from=x;
        to=y;
    }
    void print(){
        from.print();
        cout<< "<->";
        to.print();
    }
};

struct Room{
    vector<vector<int>> board;
    vector<vector<Pos>> comp;
    vector<Move> mv;
    vector<Cone> co;
    int score=0;

    Room(){
        board.resize(n);
        rep(i, n) board[i].resize(n);
        comp.resize(k);
        rep(i, k) comp[i].resize(100);
    }
    void init(){
        board=c;
        comp=cpu;
    }
    int hand(){
        return mv.size()+co.size();
    }
    void add_mv(){
        mt()%k;
        mt()%100;
    }
    void add_co(int x1, int y1, int x2, int y2){
        // cout<< x1 SP << y1 SP << x2 SP << y2 <<endl;
        int from=board[x1][y1];
        int to=board[x2][y2];
        // for文のために右か下方向に伸ばすようにする
        if(x1>x2) swap(x1, x2);
        if(y1>y2) swap(y1, y2);
        // 別の種類のコンピュータを繋ごうとしていないか確認
        assert(from==to);
        // 同一コンピュータを繋ごうとしていないか確認
        assert(!(x1==x2 && y1==y2));
        // 直線で結べない位置にいないか確認
        assert(!(x1!=x2 && y1!=y2));
        // 間に負の値でケーブルをつなぐ
        if(x1!=x2){
            // 間をケーブルが通っていないか確認
            rep3(i, x2, x1+1){
                assert(board[i][y1]==0);
            }
            rep3(i, x2, x1+1){
                board[i][y1]=-from;
            }
        }else{
            // 間をケーブルが通っていないか確認
            rep3(i, y2, y1+1){
                assert(board[x1][i]==0);
            }
            rep3(i, y2, y1+1){
                board[x1][i]=-from;
            }
        }
        // coに追加
        co.push_back({{x1, y1}, {x2, y2}});
    }
    bool between_zero(int x1, int y1, int x2, int y2){
        if(x1!=x2){
            rep3(i, x2, x1+1){
                if(board[i][y1]!=0) return false;
            }
        }else{
            rep3(i, y2, y1+1){
                if(board[x1][i]!=0) return false;
            }
        }
        return true;
    }
    void print_board(){
        rep(i, n){
            rep(j, n){
                if(board[i][j]>0) printf("%02d ", board[i][j]);
                else cout<< board[i][j] SP;
            }
            cout<< endl;
        }
    }
    void print_out(){
        cout<< mv.size() <<endl;
        rep(i, mv.size()) cout<< mv[i].from.h SP << mv[i].from.w SP << mv[i].to.h SP << mv[i].to.w <<endl;
        cout<< co.size() <<endl;
        rep(i, co.size()) cout<< co[i].from.h SP << co[i].from.w SP << co[i].to.h SP << co[i].to.w <<endl;
    }
};

void inpt(){
    cin>> n >> k;
    c.resize(n);
    rep(i, n) c[i].resize(n);
    cpu.resize(k);

    rep(i, n){
        string tmp;
        cin>> tmp;
        rep(j, n){
            int fig=int(tmp[j]-'0');
            c[i][j]=fig;
            if(fig){
                cpu[fig-1].push_back({i, j});
            }
        }
    }
}

int score(Room room){
    vector<vector<int>> cc=c;
    rep(i, room.mv.size()){
        assert(room.board[room.mv[i].to.h][room.mv[i].to.w]==0);
        assert(room.board[room.mv[i].from.h][room.mv[i].from.w]>0);
        swap(room.board[room.mv[i].to.h][room.mv[i].to.w], room.board[room.mv[i].from.h][room.mv[i].from.w]);
    }
    rep(i, room.co.size()){
        room.add_co(room.co[i].from.h, room.co[i].from.w, room.co[i].to.h, room.co[i].to.w);
    }
}

int main(){
    string path = "testcases/";
    vector<string> file_in_paths;
    for (const auto & file : fs::directory_iterator(path)){
        string tmp=file.path();
        file_in_paths.push_back(tmp);
    }
    sort(all(file_in_paths));
    rep(testcase, file_in_paths.size()){
        std::ifstream ifs(file_in_paths[testcase]);
        if (!ifs)
        {
            std::cout << file_in_paths[testcase] << " 読み込み失敗" << std::endl;
            continue;
        }
        cout<< "opened " << file_in_paths[testcase] <<endl;

        // ~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~


        //開始時間の計測
        std::chrono::system_clock::time_point start, current;
        start = chrono::system_clock::now();
        // posting inpt here
        // replace cin -> ifs
        // add c&cpu clear
        ifs>> n >> k;
        c.clear();
        cpu.clear();
        c.resize(n);
        rep(i, n) c[i].resize(n);
        cpu.resize(k);

        rep(i, n){
            string tmp;
            ifs>> tmp;
            rep(j, n){
                int fig=int(tmp[j]-'0');
                c[i][j]=fig;
                if(fig){
                    cpu[fig-1].push_back({i, j});
                }
            }
        }
        // inot end

        Room cur, best;
        cur.init();

        rep(i, n){
            rep(j, n){
                int tmp=cur.board[i][j];
                if(tmp<=0) continue;
                rep3(l, min(i+n/5, n), i+1){
                    if(cur.board[l][j]==0){
                        continue;
                    }else if(cur.board[l][j]==tmp){
                        if(cur.between_zero(i, j, l, j)) cur.add_co(i, j, l, j);
                        break;
                    }else{
                        break;
                    }
                }
                rep3(l, min(j+n/5, n), j+1){
                    if(cur.board[i][l]<=0){
                        continue;
                    }else if(cur.board[i][l]==tmp){
                        if(cur.between_zero(i, j, i, l)) cur.add_co(i, j, i, l);
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
        
        // cur.print_board();
        cur.print_out();
        // cout<< cur.co.size() <<endl;


        // ~~~~~~~~~~~~main~~~~~~~~~~~~
    }

	return 0;
}

// uf木セット
