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

// 定数周り
int INF=1000000000;
int imax=2147483647;
ll lb32=2147483648;
ll lmax=9223372036854775807;
int icos[]={1, 0, -1, 0};
int isin[]={0, 1, 0, -1};

//焼きなましの定数
double TIME_LIMIT=5900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}
template <class T> void PS(T ps) {
    cout<< "{";
	for(auto itr = ps.begin(); itr != ps.end(); ++itr) cout<< *itr SP;
	cout<< "}" <<endl;
}

//入力
int D;
vector<vector<vector<int>>> f, r;

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> D;

    f.resize(2);
    rep(i, 2) f[i].resize(D);
    rep(i, 2) rep(j, D) f[i][j].resize(D);
    r.resize(2);
    rep(i, 2) r[i].resize(D);
    rep(i, 2) rep(j, D) r[i][j].resize(D);

    string s;
    rep(i, 2){
        rep(j, D){
            cin>> s;
            rep(k, D){
                f[i][j][k]=int(s[k]-'0');
            }
        }
        rep(j, D){
            cin>> s;
            rep(k, D){
                r[i][j][k]=int(s[k]-'0');
            }
        }
    }
}

// 構造体
struct Pos{
    int x;
    int y;
    int z;

    Pos(){};
    Pos(int xx, int yy, int zz){
        x=xx;
        y=yy;
        z=zz;
    }

    bool is_out_of_bounce(){
        //cout<< "out_of_bounce" <<endl;
        if(x<0 || D<=x || y<0 || D<=y || z<0 || D<=z){
            // print();
            return true;
        }
        return false;
    }
    int get_id(int id){
        // print();
        return 3375*id+225*x+15*y+z;
    }
    void print(){
        cout<< "(" << x << ", " << y << ", " << z << ")" <<endl;
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.x=x+pos.x;
        rtn.y=y+pos.y;
        rtn.z=z+pos.z;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.x=x-pos.x;
        rtn.y=y-pos.y;
        rtn.z=z-pos.z;
        return rtn;
    }
};
Pos d6[]={{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}};

struct Space{
    ll prio;
    Pos pos;
    int bid;

    Space(){}
    Space(Pos ipos, int ibid=-1){
        prio=mt();
        // cout<< prio <<endl;
        pos=ipos;
        bid=ibid;
    }

    bool operator<(const Space &in) const{
		return prio!=in.prio ? prio<in.prio : bid<in.bid;
	};
};

struct matrix {
    vector<vector<int>> data;

    matrix(){}
    matrix(vector<vector<int>> mat){
        data=mat;
    }

    matrix operator*(const matrix &in) const {
        matrix res(vector<vector<int>>(3, vector<int>(3)));
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                for (int k=0;k<3;k++){
                    res.data[i][j]+=data[i][k]*in.data[k][j];
                }
            }
        }
        return res;
    }
    Pos operator*(const Pos &in) const {
        int x=data[0][0]*in.x+data[0][1]*in.y+data[0][2]*in.z;
        int y=data[1][0]*in.x+data[1][1]*in.y+data[1][2]*in.z;
        int z=data[2][0]*in.x+data[2][1]*in.y+data[2][2]*in.z;
        return {x, y, z};
    }
    void print(){
        rep(i, 3){
            rep(j, 3){
                cout<< data[i][j] SP;
            }
            cout<< endl;
        }
    }
};

matrix get_rot(int rx, int ry, int rz){
    matrix rtn({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    matrix matx({{1, 0, 0}, {0, icos[rx], -isin[rx]}, {0, isin[rx], icos[rx]}});
    matrix maty({{icos[ry], 0, isin[ry]}, {0, 1, 0}, {-isin[ry], 0, icos[ry]}});
    matrix matz({{icos[rz], -isin[rz], 0}, {isin[rz], icos[rz], 0}, {0, 0, 1}});
    return rtn*matx*maty*matz;
}

struct Blocks{
    int id;
    int type;
    matrix rot;
    // matrix rotinv;
    Pos pos;
    vector<Pos> cubes;

    Blocks(){}
    Blocks(int iid, int ftype, Pos ipos){
        id=iid;
        type=ftype;
        pos=ipos;
        cubes.push_back({0, 0, 0});
        if(type==2){
            int rnd=mt();
            int rx=(rnd&3);
            rnd=(rnd>>3);
            int ry=(rnd&3);
            rnd=(rnd>>3);
            int rz=(rnd&3);
            rot=get_rot(rx, ry, rz);
            // rx=(4-rx)%4;
            // ry=(4-ry)%4;
            // rz=(4-rz)%4;
            // rotinv=get_rot(rx, ry, rz);
        }else{
            // rot=get_rot(0, 0, 0);
            // rotinv=rot;
        }
    }

    bool operator<(const Blocks &in) const{
		return id<in.id;
	};
};

struct Field{
    int type;
    vector<vector<vector<int>>> val; //-1のときNG、0のとき空、それ以外block
    vector<Blocks> blocks;
    set<Space> spaces;
    vector<vector<int>> front_count, right_count;
    int front_remain=0, right_remain=0;
    // set<LeftBlock> left_blocks;

    Field(){}
    Field(int ftype, vector<vector<int>> sif, vector<vector<int>> sir){
        type=ftype;
        // cout<< type <<endl;
        val.resize(D);
        rep(i, D) val[i].resize(D);
        rep(i, D) rep(j, D) val[i][j].resize(D);
        front_count.resize(D);
        rep(i, D) front_count[i].resize(D);
        right_count.resize(D);
        rep(i, D) right_count[i].resize(D);

        rep(i, D){
            rep(j, D){
                if(sif[i][j]==0){
                    rep(k, D) val[j][k][i]=-1;
                }else{
                    front_remain++;
                }
                if(sir[i][j]==0){
                    rep(k, D) val[k][j][i]=-1;
                }else{
                    right_remain++;
                }
            }
        }
        
        rep(i, D){
            rep(j, D){
                rep(k, D){
                    if(val[i][j][k]==0) spaces.insert({{i, j, k}});
                    // cout<< val[i][j][k] SP;
                }
            }
        }
    }
    // Field vector<vector<int>> front_count, right_count を作り、シルエットに対応しているブロックが何個存在するか(0~D)をメモしておく。
    // Field front_remain, right_remainで埋めたいけど埋められていないシルエット数を求める
    // fは[x][y][z]=[z][x], rは[x][y][z]=[z][y]
    void set_val(Pos pos, int value){
        // cout<< type SP << "set_val: " << value <<endl;
        // cout<< "pos: ";
        // pos.print();
        // assert(!pos.is_out_of_bounce());
        // 変化がないのはおかしい
        // cout<< val[pos.x][pos.y][pos.z] SP << value <<endl;
        // assert(val[pos.x][pos.y][pos.z]!=value);
        int effect=1;
        if(value==0) effect=-1;
        val[pos.x][pos.y][pos.z]=value;

        front_count[pos.z][pos.x]+=effect;
        int tmpf=front_count[pos.z][pos.x];
        // assert(tmpf>=0);
        // assert(tmpf<=D);
        if(tmpf==0) front_remain++;
        else if(tmpf==1 && value) front_remain--;
        // assert(front_remain>=0);

        right_count[pos.z][pos.y]+=effect;
        int tmpr=right_count[pos.z][pos.y];
        // assert(tmpr>=0);
        // assert(tmpr<=D);
        if(tmpr==0) right_remain++;
        else if(tmpr==1 && value) right_remain--;
        // assert(right_remain>=0);
        // cout<< "end set_val" <<endl;
    }
    bool shuffle_set(int id){
        // cout<< type SP << "shuffle_set" <<endl;
        if(spaces.empty()) return false;
        auto itr=spaces.begin();
        Space spa=*itr;
        Pos pos=spa.pos;
        spaces.erase(itr);
        set_val(pos, id);
        // blocks[id]=Blocks({id, type, pos});
        return true;
    }
    bool make_block(int id){
        int lp=0;
        while(lp<10000){
            lp++;
            int x=mt()%D;
            int y=mt()%D;
            int z=mt()%D;
            if(val[x][y][z]==-2){
                blocks.push_back({id, type, {x, y, z}});
                val[x][y][z]=id;
                return true;
            }
        }
        return false;
    }
    void remap_blocks(){
        // cout<< "remap_blocks " << blocks.size() <<endl;
        rep(i, blocks.size()){
            Pos base=blocks[i].pos;
            rep(j, blocks[i].cubes.size()){
                Pos pos=base+blocks[i].cubes[j];
                // cout<< i SP << j SP;
                // pos.print();
                assert(!pos.is_out_of_bounce());
                val[pos.x][pos.y][pos.z]=blocks[i].id;
            }
        }
    }
    void print_val(){
        rep(i, D) rep(j, D) rep(k, D){
            if(val[i][j][k]==-1) cout<< "0 ";
            else cout<< val[i][j][k] SP;
        }
        cout<<endl;
    }
};

struct Puzzle{
    Field f1=Field(1, f[0], r[0]), f2=Field(2, f[1], r[1]);
    int idx=0;

    void init_block_list(){
        while(f1.front_remain || f1.right_remain){
            f1.shuffle_set(-2);
        }
    }
    void make_block(int fig){
        // cout<< "make_block " << fig <<endl;
        rep(i, fig){
            idx++;
            f1.make_block(idx);
        }
    }
    void remap_blocks(int type=-1){
        if(type!=1) f2.remap_blocks();
        if(type!=2) f1.remap_blocks();
    }
    bool check_complete(){
        // cout<< f1.front_remain SP << f1.right_remain SP << f2.front_remain SP << f2.right_remain <<endl;
        return (!f1.front_remain && !f1.right_remain && !f2.front_remain && !f2.right_remain);
    }
    ll calc_score(){
        double base=1000000000.0;
        double sig=0.0;
        // cout<< f1.blocks.size() <<endl;
        rep(i, f1.blocks.size()){
            // cout<< (*itr).first SP;
            sig+=1.0/f1.blocks[i].cubes.size();
        }
        // cout<< endl;
        ll rtn=round(base*sig);
        return rtn;
    }
    void print_ans(){
        int mi=999;
        rep(i, D) rep(j, D) rep(k, D){
            if(f1.val[i][j][k]>0){
                mi=min(mi, f1.val[i][j][k]);
            }
        }
        cout<< idx <<endl;
        // cout<< idx-mi <<endl;
        f1.print_val();
        f2.print_val();
    }
};

// グローバル
// vector<vector<vector<matrix>>> rot;

void init(){
    inpt();
}

void get_argv(int argc, char* argv[]){
    vector<double> args;
    rep3(i, argc, 1){
        string tmp;
        tmp.assign(argv[i]);
        args.push_back(stof(tmp));
        // cout<< args[i-1] <<endl;
    }
}

int main(int argc, char* argv[]){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    init();
    // get_argv(argc, argv);
    ll best_score=lmax;
    int lp=0;

    Puzzle best;

    while (true){
        lp++;
        // if(lp>1) break;
        current = chrono::system_clock::now(); // 現在時刻
        delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if(delta > TIME_LIMIT) break;
 
        Puzzle puzzle;
        puzzle.init_block_list();
        // cout<< "puzzle.init_block_list();" <<endl;
        puzzle.make_block(D);
        // cout<< "puzzle.make_block(D);" <<endl;
        puzzle.remap_blocks(1);
        // cout<< "puzzle.remap_blocks(1);" <<endl;
        puzzle.print_ans();
        return 0;
 
        if(puzzle.check_complete()){
            // puzzle.print_ans();
            ll score=puzzle.calc_score();
            // cout<< "lp: " << lp SP << score <<endl;
            if(score<best_score){
                best_score=score;
                best=puzzle;
                // cout<< "lp: " << lp SP << best_score <<endl;
                // puzzle.print_ans();
            }
            // break;
        }
        // if(best_score!=lmax) break;
    }

    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    return 0;
}
