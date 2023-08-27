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

int imax=2147483647;
long long llimax=9223372036854775807;

// std::ofstream outputFile("log.csv");

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			if(pvv[i][j]!=imax) cout << pvv[i][j] SP;
            else cout<< -1 SP;
		}
		cout << endl;
	}
}
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

//焼きなましの定数
double TIME_LIMIT=3900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

int d, n;

// 構造体
struct Pos{
    int y;
    int x;
    int em=-1;

    Pos(){};
    Pos(int yy, int xx){
        y=yy;
        x=xx;
        // em=enter_manhattan();
    }

    bool is_oob(){
		// assert(0<=h);
		// assert(h<n);
		// assert(0<=w);
		// assert(w<=h);
		return !(0<=y && y<d && 0<=x && x<d);
	}
    int manhattan(Pos a){
        // cout<< "manhattan" <<endl;
        if(a.is_oob()){
            a.print();
            assert(!a.is_oob());
        }
        if(is_oob()){
            print();
            assert(!is_oob());
        }
        return (abs(a.x-x)+abs(a.y-y));
    }
    // int enter_manhattan(){
    //     // cout<< "enter_manhattan" <<endl;
    //     return (y+abs(4-x));
    // }
    void print(){
        cout<< y << " " << x <<endl;
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.y=y+pos.y;
        rtn.x=x+pos.x;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.y=y-pos.y;
        rtn.x=x-pos.x;
        return rtn;
    }
    bool operator==(const Pos &in) const{
		return x==in.x && y==in.y;
	};
    bool operator<(const Pos &in) const{
		return em!=in.em ? em>in.em : y!=in.y ? y<in.y : x<in.x;
		// return y!=in.y ? y<in.y : x<in.x;
	};
};

Pos d4[]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

Pos obstacles[110];

struct Warehouse{
    Pos obs[110]; // 入力をコピーしてくる
    set<Pos> left_cell; // まだ置ける場所
    vector<vector<int>> enter_dist; // 入口からの道のり
    vector<vector<int>> board; // 倉庫の状況
    vector<Pos> container; // 荷物の状況
    vector<vector<int>> carrable; // 運び出せるもの
    vector<int> ideal_perm; // 運びだしたい順番

    void init(){
        // cout<< "init" <<endl;
        rep(i, 110) obs[i]=obstacles[i];
        // search_left_cell();
        container.resize(100);
        board.resize(d, vector<int>(d, 100));
        board[0][4]=-2;
        rep(i, n){
            board[obs[i].y][obs[i].x]=-1;
        }
        calc_enter_dist();
        // search_left_cell_from_dist();
    }

    void calc_enter_dist(){
        // cout<< "calc_enter_dist" <<endl;
        // PVV(board);
        enter_dist.clear();
        enter_dist.resize(d, vector<int>(d, imax));
        queue<Pos> q;
        q.push({0, 4});
        enter_dist[0][4]=0;
        while(!q.empty()){
            Pos pos=q.front();
            q.pop();
            rep(i, 4){
                Pos npos=pos+d4[i];
                // cout<< "#";
                // npos.print();
                if(npos.is_oob()) continue;
                if(board[npos.y][npos.x]!=100) continue;
                if(enter_dist[npos.y][npos.x]!=imax) continue;

                enter_dist[npos.y][npos.x]=enter_dist[pos.y][pos.x]+1;
                q.push(npos);
            }
        }
        // PVV(enter_dist);
    }
    void search_left_cell_from_dist(){
        rep(i, d){
            rep(j, d){
                if(i==0 && j==4) continue;
                int flg=1;
                rep(k, n){
                    if(Pos({i, j})==obs[k]){
                        flg=0;
                        break;
                    }
                }
                Pos ipos={i, j};
                ipos.em=enter_dist[i][j];
                if(flg) left_cell.insert(ipos);
            }
        }
    }
    void search_left_cell(){
        rep(i, d){
            rep(j, d){
                if(i==0 && j==4) continue;
                int flg=1;
                rep(k, n){
                    if(Pos({i, j})==obs[k]){
                        flg=0;
                        break;
                    }
                }
                if(flg) left_cell.insert({i, j});
            }
        }
    }
    bool is_connect(){
        rep(i, d){
            rep(j, d){
                if(board[i][j]==100 && enter_dist[i][j]==imax){
                    // cout<< "not_connect" <<endl;
                    return false;
                }
            }
        }
        return true;
    }
    void nearest_placement(){
        // cout<< "nearest_placement" <<endl;
        int inid;
        cin>> inid;
        ideal_perm.push_back(inid);
        double allow=0.0;
        vector<int> board_ng(100);
        while(1){
            int ry=mt()%d;
            int rx=mt()%d;
            int board_idx=ry*d+rx;
            // cout<< board_idx <<endl;
            if(board_ng[board_idx]) continue;
            if(board[ry][rx]!=100) continue;
            calc_enter_dist();
            int err=abs(enter_dist[ry][rx]-inid/4);
            if(err<allow){
                // cout<< ry SP << rx SP << inid <<endl;
                // cout<< "board" <<endl;
                board[ry][rx]=inid;
                // PVV(board);
                calc_enter_dist();
                // cout<< "calcd" <<endl;
                // PVV(enter_dist);
                if(!is_connect()){
                    board[ry][rx]=100;
                    board_ng[board_idx]=1;
                    continue;
                }
                board[ry][rx]=inid;
                container[inid]={ry, rx};
                cout<< ry << " " << rx <<endl;
                calc_enter_dist();
                return;
            }
            allow+=0.1;
            // cout<< allow <<endl;
        }
    }
    void dist_placement(){
        // cout<< "random_placement" <<endl;
        int inid;
        cin>> inid;
        Pos pos=*left_cell.begin();
        left_cell.erase(left_cell.begin());
        pos.print();
    }
    void nearest_carryout(){
        // cout<< "nearest_carryout" <<endl;
        vector<int> carryable_cells;
        // PVV(board);
        rep(i, d){
            rep(j, d){
                if(board[i][j]==100 || board[i][j]==-2){
                    Pos pos={i, j};
                    rep(k, 4){
                        Pos npos=pos+d4[k];
                        if(npos.is_oob()) continue;
                        if(board[npos.y][npos.x]<0) continue;
                        if(board[npos.y][npos.x]>=100) continue;
                        if(board[npos.y][npos.x]==0){
                            int flg=0;
                            rep(l, 4){
                                Pos nnpos=npos+d4[l];
                                if(nnpos.is_oob()) continue;
                                if(board[nnpos.y][nnpos.x]==100) flg=1;
                            }
                            if(flg==0) continue;
                        }
                        carryable_cells.push_back(board[npos.y][npos.x]);
                    }
                }
            }
        }
        // PV(carryable_cells);
        rep(i, ideal_perm.size()){
            if(ideal_perm[i]==-1) continue;
            rep(j, carryable_cells.size()){
                if(i==carryable_cells[j]){
                    Pos pos=container[i];
                    pos.print();
                    ideal_perm[i]=-1;
                    board[pos.y][pos.x]=100;
                    return;
                }
            }
        }
    }
    void random_carryout(){
        search_left_cell_from_dist();
        while(!left_cell.empty()){
            auto itr=left_cell.end();
            itr--;
            Pos pos=*itr;
            left_cell.erase(itr);
            pos.print();
        }
    }

    // void print_ans(){
    //     cout<< "-1 -1 -1" <<endl;
    //     rep(i, n) cout<< e[i] <<endl;
    // }
};

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> d >> n;

    rep(i, n){
        cin>> obstacles[i].y >> obstacles[i].x;
    }
}

int main(){
    // cout<< "main" <<endl;
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Warehouse warehouse;
    warehouse.init();
    rep(i, 80-n) warehouse.nearest_placement();
    // PVV(warehouse.board);
    warehouse.calc_enter_dist();
    rep(i, 80-n) warehouse.nearest_carryout();

    // warehouse.print_ans();

    return 0;
}
