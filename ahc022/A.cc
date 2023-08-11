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

//焼きなましの定数
double TIME_LIMIT=3900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

struct Pos;
struct Space;

int l, n, s;
Pos exit_cells[110];

// 構造体
struct Pos{
    int y;
    int x;

    Pos(){};
    Pos(int yy, int xx){
        y=yy;
        x=xx;
    }

    void print(){
        cout<< "(" << y << ", " << x << ")" <<endl;
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
};

struct Compare{
	int idx;
	int val;

	bool operator<(const Compare &in) const{
		return val!=in.val ? val<in.val : idx<in.idx;
	};
};

struct Space{
    Pos e_cells[110];
    int p[110][110];
    vector<Compare> compare;
    int e[110];

    void init(){
        rep(i, n) e_cells[i]=exit_cells[i];
        compare.resize(l);
    }

    void sample_placement(){
        rep(i, l){
            rep(j, l){
                p[i][j]=0;
            }
        }
        rep(i, n){
            p[e_cells[i].y][e_cells[i].x]=(i+1)*10;
        }
        print_placement();
    }
    void sample_measurement(){
        rep(i, n){
            compare[i]={i, measurement(i, e_cells[i])};
        }
        guess();
    }

    void guess(){
        sort(all(compare));
        rep(i, n) e[i]=compare[i].idx;
    }
    int measurement(int i, Pos pos){
        cout<< i+1 SP << pos.y SP << pos.x <<endl;
        int tmp;
        cin>> tmp;
        return tmp;
    }

    void print_placement(){
        rep(i, l){
            rep(j, l){
                cout<< p[i][j] SP;
            }
            cout<< endl;
        }
    }
    void print_ans(){
        cout<< "-1 -1 -1" <<endl;
        rep(i, n) cout<< e[i]+1 <<endl;
    }
};

void inpt(){
    cin>> l >> n >> s;

    rep(i, n){
        cin>> exit_cells[i].y >> exit_cells[i].x;
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Space space;
    space.init();


    space.print_ans();

    return 0;
}
