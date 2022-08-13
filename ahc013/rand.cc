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

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=10;
mt19937 mt(seed);

// 構造体
struct UnionFind {
    vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2
	vector<int> siz; // siz[i]:iの属する木に含まれる点の数

    void init(int N){ //最初は全てが根であるとして初期化
        par.resize(N);
        for(int i = 0; i < N; i++) par[i] = i;
		siz.resize(par.size(), 1); //最初は全てサイズ1
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

	int tsize(int x){ // siz[x]の木の根を見に行き、サイズを返す
		return siz[root(x)];
	}

    void unite(int x, int y) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
        if(siz[rx]<siz[ry]) swap(rx,ry);
        par[ry] = rx; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[rx]+=siz[ry]; //根で管理
    }

    bool same(int x, int y){
        return root(x)==root(y);
    }
};

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

struct Num{
    int type;
    int idx;

    Num(){};
    Num(int x, int y){
        type=x;
        idx=y;
    }
    void print(){
        if(type>=0) printf("%02d", type);
        else cout<< type SP;
    }
};

//入力
int n, k;
vector<vector<Num>> c;
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
    vector<vector<Num>> board;
    vector<vector<Pos>> comp;
    vector<Move> mv;
    vector<Cone> co;
    UnionFind uf;
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
        uf.init(k*100);
        // rep(i, n){
        //     rep(j, n){
        //         if(board[i][j].type>0) cout<< board[i][j].idx SP;
        //     }
        //     cout<< endl;
        // }
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
        int from=board[x1][y1].type;
        int to=board[x2][y2].type;
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
                assert(board[i][y1].type==0);
            }
            rep3(i, x2, x1+1){
                board[i][y1].type=-from;
            }
        }else{
            // 間をケーブルが通っていないか確認
            rep3(i, y2, y1+1){
                assert(board[x1][i].type==0);
            }
            rep3(i, y2, y1+1){
                board[x1][i].type=-from;
            }
        }
        // coに追加
        co.push_back({{x1, y1}, {x2, y2}});
        uf.unite(board[x1][y1].idx, board[x2][y2].idx);
    }
    bool between_zero(int x1, int y1, int x2, int y2){
        if(x1!=x2){
            rep3(i, x2, x1+1){
                if(board[i][y1].type!=0) return false;
            }
        }else{
            rep3(i, y2, y1+1){
                if(board[x1][i].type!=0) return false;
            }
        }
        return true;
    }
    void nomove_connect(int num, int length){
        rep(i, n){
            rep(j, n){
                int tmp=board[i][j].type;
                if(tmp!=num) continue;
                // if(tmp>1) continue;
                rep3(l, min(i+1+length, n), i+1){
                    if(board[l][j].type==0){
                        continue;
                    }else if(board[l][j].type==tmp){
                        if(!uf.same(board[i][j].idx, board[l][j].idx) && between_zero(i, j, l, j)) add_co(i, j, l, j);
                        break;
                    }else{
                        break;
                    }
                }
                rep3(l, min(j+1+length, n), j+1){
                    if(board[i][l].type<=0){
                        continue;
                    }else if(board[i][l].type==tmp){
                        if(!uf.same(board[i][j].idx, board[i][l].idx) && between_zero(i, j, i, l)) add_co(i, j, i, l);
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
    }
    // bool board_connect(int x1, int y1, int x2, int y2){
        
    // }
    void print_board(){
        rep(i, n){
            rep(j, n){
                board[i][j].print();
                cout SP;
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
    int cnt=0;

    rep(i, n){
        string tmp;
        cin>> tmp;
        rep(j, n){
            int fig=int(tmp[j]-'0');
            c[i][j]=Num(fig, cnt);
            if(fig){
                cnt++;
                cpu[fig-1].push_back({i, j});
            }
        }
    }
    // rep(i, k){
    //     rep(j, 100){
    //         cpu[i][j].print();
    //         cout SP;
    //     }
    //     cout<< endl;
    // }
}

// int score(Room room){
//     vector<vector<Num>> cc=c;
//     rep(i, room.mv.size()){
//         int th=room.mv[i].to.h;
//         int tw=room.mv[i].to.w;
//         int fh=room.mv[i].from.h;
//         int fw=room.mv[i].from.w;
//         assert(room.board[th][tw].type==0);
//         assert(room.board[fh][fw].type>0);
//         swap(room.board[th][tw], room.board[fh][fw]);
//     }
//     rep(i, room.co.size()){
//         room.add_co(room.co[i].from.h, room.co[i].from.w, room.co[i].to.h, room.co[i].to.w);
//     }
// }

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();

    Room cur, best;
    cur.init();

    // cur.nomove_connect(1);
    // cur.nomove_connect(2);
    // cur.nomove_connect(3);
    // cur.nomove_connect(4);
    // cur.nomove_connect(5);
    rep(i, k) cur.nomove_connect(i+1, 100);

    cur.print_board();
    cur.print_out();

	return 0;
}

// uf木セット
// Room.score関数作成
// 通り道の邪魔な別種CPUをどかす処理
// 近くでたむろしている同種CPUの接続