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
ll lmax=9223372036854775807;
int icos[]={1, 0, -1, 0};
int isin[]={0, 1, 0, -1};

//焼きなましの定数
double TIME_LIMIT=5900.0;
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
            print();
            return true;
        }
        return false;
    }
    void print(){
        cout<< "(" << x << ", " << y << ", " << z << ")";
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.x=x+pos.x;
        rtn.y=y+pos.y;
        rtn.z=z+pos.z;
        return rtn;
    }
};
Pos d6[]={{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};

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
    int type;
    matrix rot;
    vector<Pos> cubes;

    Blocks(){}
    Blocks(int ftype, Pos ipos){
        type=ftype;
        cubes.push_back(ipos);
        if(type==2) rot=get_rot(mt()%4, mt()%4, mt()%4);
        else rot=get_rot(0, 0, 0);
    }
};

struct Field{
    int type;
    vector<vector<vector<int>>> val; //-1のときNG、0のとき空、それ以外block
    vector<Blocks> blocks;

    Field(){}
    Field(int ftype, vector<vector<int>> sif, vector<vector<int>> sir){
        type=ftype;
        val.resize(D);
        rep(i, D) val[i].resize(D);
        rep(i, D) rep(j, D) val[i][j].resize(D);

        rep(i, D){
            rep(j, D){
                if(sif[i][j]==0){
                    rep(k, D) val[j][k][i]=-1;
                }
                if(sir[i][j]==0){
                    rep(k, D) val[k][j][i]=-1;
                }
            }
        }
    }

    void random_set(int id){
        int lp=0;
        while(1){
            int x=mt()%D;
            int y=mt()%D;
            int z=mt()%D;
            lp++;
            if(val[x][y][z]==0){
                // cout<< lp <<endl;
                int dup1=0, dup2=0, dup;
                rep(i, D){
                    if(val[i][y][z]>0) dup1=1;
                    if(val[x][i][z]>0) dup2=1;
                }
                dup=dup1+dup2;
                if(dup*D*D*D>lp) continue;
                val[x][y][z]=id;
                blocks.push_back({type, {x, y, z}});
                break;
            }
        }
    }
    Pos f1_fetch_space(int block_id){
        int lp=0;
        while(1){
            int cube_id=mt()%blocks[block_id].cubes.size();
            lp++;
            Pos pos=blocks[block_id].cubes[cube_id];
            rep(i, 6){
                Pos npos=pos+d6[i];
                if(npos.is_out_of_bounce()) continue;
                if(val[npos.x][npos.y][npos.z]==0) return npos;
            }
            if(lp>100) return {-1, -1, -1};
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

    void random_set(){
        idx++;
        f1.random_set(idx);
        f2.random_set(idx);
    }
    void random_extend(){
        int idx=mt()%f1.blocks.size();
        Pos pos=f1.f1_fetch_space(idx);
        if(pos.is_out_of_bounce()) return;
        f1.random_set(idx);
        f2.random_set(idx);
    }
    bool check_complete(){
        rep(i, D){
            rep(j, D){
                if(f[0][i][j]==0){
                    rep(k, D){
                        if(f1.val[j][k][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f1.val[j][k][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        rep(i, D){
            rep(j, D){
                if(f[1][i][j]==0){
                    rep(k, D){
                        if(f2.val[j][k][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f2.val[j][k][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        rep(i, D){
            rep(j, D){
                if(r[0][i][j]==0){
                    rep(k, D){
                        if(f1.val[k][j][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f1.val[k][j][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        rep(i, D){
            rep(j, D){
                if(r[1][i][j]==0){
                    rep(k, D){
                        if(f2.val[k][j][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f2.val[k][j][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        return true;
    }
    void print_ans(){
        cout<< idx <<endl;
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
    start = chrono::system_clock::now();

    init();
    // get_argv(argc, argv);
    Puzzle puzzle;
    rep3(i, 3000, 1){
        // cout<< i <<endl;
        puzzle.random_set();
        if(puzzle.check_complete()) break;
    }

    puzzle.print_ans();

    return 0;
}

