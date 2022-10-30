// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
int CANDY=100;
string TILT="RLFB";

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp=50.0;
double end_temp=10.0;
int lp=0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

//入力
int f[110];

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

// 構造体
struct Candys{
	int idx;
	int figure;

	bool operator<(const Candys &in) const{
		return figure>in.figure;
	};

    void print(){
        cout<< idx SP << figure <<endl;
    }
};

// グローバル
vector<Candys> candys(3);
int first_idx, second_idx, third_idx;
int priority_candy[4];
int last_LR=0;

struct Board{
    vector<vector<int>> grid;
    int invh[100], invw[100];
    vector<int> h_fill;

    void init(){
        rep(i, CANDY){
            invh[i]=i/10;
            invw[i]=i%10;
        }
        grid.resize(10);
        rep(i, 10) grid[i].resize(10);
        h_fill.resize(10);
    } 
    void insert(int idx, int figure){
        idx--;
        assert(0<figure && figure<4);
        grid[invh[idx]][invw[idx]]=figure;
        // rep3(i, CANDY-1, idx){
        //     invh[i]=invh[i+1];
        //     invw[i]=invw[i+1];
        // }
    }
    void tilt(int dir, bool out){
        if(out) cout<< TILT[dir] <<endl;
        if(dir==0){
            rep(i, 10){
                rep(lp, 10){
                    repr(j, 9){
                        if(grid[i][j]>0 && grid[i][j+1]==0){
                            swap(grid[i][j], grid[i][j+1]);
                        }
                    }
                }
            }
        }else if(dir==1){
            rep(i, 10){
                rep(lp, 10){
                    rep3(j, 10, 1){
                        if(grid[i][j]>0 && grid[i][j-1]==0){
                            swap(grid[i][j], grid[i][j-1]);
                        }
                    }
                }
            }
        }else if(dir==2){
            rep(i, 10){
                rep(lp, 10){
                    rep3(j, 10, 1){
                        if(grid[j][i]>0 && grid[j-1][i]==0){
                            swap(grid[j][i], grid[j-1][i]);
                        }
                    }
                }
            }
        }else{
            rep(i, 10){
                rep(lp, 10){
                    repr(j, 9){
                        if(grid[i][j]>0 && grid[j+1][i]==0){
                            swap(grid[i][j], grid[j+1][i]);
                        }
                    }
                }
            }
        }

        int id=0;
        rep(i, 10){
            rep(j, 10){
                if(grid[i][j]==0){
                    invh[id]=i;
                    invw[id]=j;
                    id++;
                }
            }
        }
    }
    // bool fill_10th(){
    //     rep3(i, 10, 1){
    //         int su=0;
    //         rep(j, 10){
    //             if(grid[i][j]) su++;
    //         }
    //         if(su==9){

    //             return true;
    //         }
    //     }
    //     return false;
    // }

    void print(){
        rep(i, 10){
            rep(j, 10){
                cout<< grid[i][j] SP;
            }
            cout<< endl;
        }
    }
    int score(){
        dsu g(100);
        rep(i, 10){
            rep(j, 9){
                if(grid[i][j]==grid[i][j+1]) g.merge(i*10+j, i*10+j+1);
            }
        }
        rep(i, 9){
            rep(j, 10){
                if(grid[i][j]==grid[i+1][j]) g.merge(i*10+j, (i+1)*10+j);
            }
        }

        double msco=0.0;
        rep(i, 3) msco+=candys[i].figure*candys[i].figure;

        double sco=0.0;
        rep(i, g.groups().size()){
            sco+=g.groups()[i].size()*g.groups()[i].size();
        }

        double rtn=1000000.0*sco/msco;
        return round(rtn);
    }
};

void inpt(){
    //cout<< "inpt" <<endl;
    rep(i, 3) candys[i].idx=i;

    rep(i, CANDY){
        cin>> f[i];
        candys[f[i]-1].figure++;
    }

    sort(all(candys));
    rep(i, 3){
        // candys[i].print();
        priority_candy[candys[i].idx+1]=i;
    }
}

ll score_dfs(Board board, int dep){
    if(dep==0) return board.score();

    ll sco=0;
    rep(j, dep){
        rep(i, 4){
            Board tmp=board;
            tmp.insert(dep+1, f[100-dep-1]);
            tmp.tilt(i, false);
            sco+=score_dfs(tmp, dep-1);
        }
    }
    return sco;
}

void solve(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    Board board;
    board.init();

    rep(lp, CANDY){
        int tmp;
        cin>> tmp;
        board.insert(tmp, f[lp]);
        if(lp==CANDY-1) break;

        if(lp>=CANDY-4){
            vector<Board> dfses(4, board);
            vector<ll> sco(4);
            ll ma=0;
            int mai;
            rep(i, 4){
                dfses[i].tilt(i, false);
                sco[i]=score_dfs(dfses[i], CANDY-lp-1);
                // cout<<sco[i]<<endl;
                if(ma<sco[i]){
                    ma=sco[i];
                    mai=i;
                }
            }
            board.tilt(mai, true);
            continue;
        }

        int current_type=f[lp];
        int next_type=f[lp+1];
        if(priority_candy[next_type]!=2){
            // last_LR=priority_candy[next_type];
            if(current_type==next_type){
                // cout<< TILT[2] <<endl;
                board.tilt(2, true);
            }else{
                // cout<< TILT[priority_candy[next_type]] <<endl;
                board.tilt(priority_candy[next_type], true);
            }
        }else{
            // if(mt()%15==0){
            //     cout<< TILT[priority_candy[next_type]+1] <<endl;
            // }else{
            //     cout<< TILT[priority_candy[next_type]] <<endl;
            // }
            // cout<< TILT[priority_candy[next_type]] <<endl;
            board.tilt(priority_candy[next_type], true);
        }
    }

    // board.print();
    // cout<< board.score() <<endl;
}

int main(){
    solve();
}
