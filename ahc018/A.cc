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
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;
int dr[4]={0, -1, 0, 1}, dc[4]={-1, 0, 1, 0};

//焼きなましの定数
double TIME_LIMIT=4900.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int lp=0;
int excavation_count=0; //testtest
int score=0; //testtest

//グローバル
int N, W, K, C;
int S[210][210]; //testtest
vector<int> a, b, c, d;
dsu uf(40010);
set<int> water_set;

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

void set_hyper_v_set(){
    rep(i, W){
        int id=a[i]*N+b[i];
        water_set.insert(id);
    }
}

// ジャッジ
bool does_get_water(int id){
    return (water_set.end()!=water_set.find(uf.leader(id)));
}
bool does_water_complete(){
    int cnt=0;
    rep(i, K){
        if(does_get_water(c[i]*N+d[i])) cnt++;
    }
    return (cnt==K);
}
void merge_uf(int y, int x){
    // 繋がっていればつなげる
    int id=y*N+x;
    rep(i, 4){
        if(y+dr[i]<0 || N<=y+dr[i] || x+dc[i]<0 || N<=x+dc[i]){
            continue;
        }
        int nid=(y+dr[i])*N+x+dc[i];
        uf.merge(id, nid);
    }
}
//testtest
int excavation_local(int y, int x, int power){
    excavation_count++;
    score+=C+power;
    if(S[y][x]<=0){
        cout<< "S[y][x]<=0" <<endl;
        return -1;
    }
    S[y][x]-=power;
    if(S[y][x]>0) return 0;

    merge_uf(y, x);

    if(does_water_complete()) return 2;
    else return 1;
}
int excavation(int y, int x, int power){
    excavation_count++;
    score+=C+power;
    cout<< y SP << x SP << power <<endl;
    int tmp;
    cin>> tmp;

    if(tmp==0){
        return 0;
    }else if(tmp==1){
        merge_uf(y, x);
        return 1;
    }else{
        exit(0);
    }
}

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> N >> W >> K >> C;
    rep(i, 200){
        rep(j, 200){
            cin>> S[i][j];
        }
    }
    a.resize(W);
    b.resize(W);
    c.resize(K);
    d.resize(K);
    rep(i, W){
        cin>> a[i] >> b[i];
    }
    rep(i, K){
        cin>> c[i] >> d[i];
    }
}

void init(){
    inpt();
    set_hyper_v_set();
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    init();

    rep(i, 200){
        rep(j, 200){
            if(i==c[0] && j==d[0]) continue;
            while(1){
                cout<< i SP << j SP << 100 <<endl;
                int tmp;
                cin>> tmp;
                if(tmp==1) break;
            }
        }
    }
    while(1){
        cout<< c[0] SP << d[0] SP << 100 <<endl;
        int tmp;
        cin>> tmp;
        if(tmp==2) break;
    }

    cout<< "exca: " << excavation_count <<endl;
    cout<< "score: " << score <<endl;

    return 0;
}
