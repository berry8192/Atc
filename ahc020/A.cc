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

int imax=2147483647;
long long int llimax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=6950.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

int n, m, k;

// 構造体
struct Pos{
    int x;
    int y;

    Pos(){};
    Pos(int xx, int yy){
        x=xx;
        y=yy;
    }

    double euclid(Pos ipos){
        int rnd=mt()%21+100;
        rnd=100;
        return (rnd/100.0)*sqrt((x-ipos.x)*(x-ipos.x)+(y-ipos.y)*(y-ipos.y));
    }
    bool is_out_of_bounce(){
        //cout<< "out_of_bounce" <<endl;
        if(abs(x)>=10000 || abs(y)>=10000){
            // print();
            return true;
        }
        return false;
    }
    int get_id(int id){
        // print();
        return 100000*x+y;
    }
    void print(){
        cout<< "(" << x << ", " << y << ")" <<endl;
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.x=x+pos.x;
        rtn.y=y+pos.y;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.x=x-pos.x;
        rtn.y=y-pos.y;
        return rtn;
    }
};

struct Tv;
struct Watch;
struct Edge;

vector<Tv> tv;
vector<Edge> cable, inc;
vector<Watch> watch;

struct Tv{
    Pos pos;

};

struct Watch{
    Pos pos;

    void near(int &idx, int &dist){
        int best_idx;
        double near_dist=100000.0;
        rep(i, n){
            double dis=pos.euclid(tv[i].pos);
            if(dis<near_dist){
                best_idx=i;
                near_dist=dis;
            }
        }
        idx=best_idx;
        dist=ceil(near_dist);
    }
};

struct Edge{
	int to;
	int fr;
	int co;
	int edit_co;
    double hev;
    int id;

	// bool operator<(const Edge &in) const{
	// 	return hev!=in.hev ? hev<in.hev : to<in.to ? to<in.to : fr<in.fr;
	// };
	bool operator<(const Edge &in) const{
		return edit_co!=in.edit_co ? edit_co<in.edit_co : to<in.to ? to<in.to : fr<in.fr;
	};
};

struct Town{
    int p[110];
    int b[310];
    vector<set<int>> g;
    ll s;

    void init(){
        rep(i, n) p[i]=0;
        rep(i, m) b[i]=0;
        g.resize(n);
        cable=inc;
        rep(i, m){
            int rnd=mt()%151+50;
            cable[i].edit_co=cable[i].co*(rnd/100.0);
        }
        sort(all(cable));
        s=0;
    }

    void kruskal(){
        ll cost=0;
        dsu d(n);
        rep(i, m){
            if(!d.same(cable[i].to, cable[i].fr)){
                d.merge(cable[i].to, cable[i].fr);
                cost+=cable[i].co;
                b[cable[i].id]=1;
                g[cable[i].to].insert(cable[i].fr);
                g[cable[i].fr].insert(cable[i].to);
            }
        }
        s+=cost;
    }
    void nearest_tv(){
        rep(i, k){
            int idx, dist;
            watch[i].near(idx, dist);
            p[idx]=max(p[idx], dist);
        }
    }
    void decrease_p(){

    }
    void erase_nonuse_cable(){
        int flag;
        while(flag){
            flag=0;
            rep(i, m){
                if(b[cable[i].id]){
                    if(g[cable[i].to].size()==1 && p[cable[i].to]==0){
                        g[cable[i].to].clear();
                        g[cable[i].fr].erase(cable[i].to);
                        b[cable[i].id]=0;
                        flag++;
                        s-=cable[i].co;
                        continue;
                    }
                    if(g[cable[i].fr].size()==1 && p[cable[i].fr]==0){
                        g[cable[i].fr].clear();
                        g[cable[i].to].erase(cable[i].fr);
                        b[cable[i].id]=0;
                        flag++;
                        s-=cable[i].co;
                    }
                }
            }
            // cout<< flag <<endl;
        }
    }

    ll calc_score(){
        rep(i, n) s+=p[i]*p[i];
        return 1000000.0*(1+100000000.0/(s+10000000));
    }
    void print_ans(){
        rep(i, n) cout<< p[i] SP;
        cout<< endl;
        rep(i, m) cout<< b[i] SP;
        cout<< endl;
    }
};

void inpt(){
    cin>> n >> m >> k;

    tv.resize(n);
    rep(i, n){
        cin>> tv[i].pos.x >> tv[i].pos.y;
    }

    inc.resize(m);
    rep(i, m){
        cin>> inc[i].to >> inc[i].fr >> inc[i].co;
        inc[i].edit_co=inc[i].co;
        inc[i].to--;
        inc[i].fr--;
        inc[i].hev=1.0;
        // inc[i].hev=1.0*inc[i].co/(tv[inc[i].to].pos.euclid(tv[inc[i].fr].pos));
        inc[i].id=i;
    }

    watch.resize(k);
    rep(i, k){
        cin>> watch[i].pos.x >> watch[i].pos.y;
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Town best;
    best.init();
    best.kruskal();
    best.nearest_tv();
    best.erase_nonuse_cable();
    ll best_score=best.calc_score();

    int lp=0;
    while (true){
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if(delta > TIME_LIMIT) break;

        Town town;
        town.init();
        town.kruskal();
        town.nearest_tv();
        town.erase_nonuse_cable();
        ll score=town.calc_score();
        if(best_score<score){
            cout<< "lp: " << lp <<endl;
            cout<< score <<endl;
            best=town;
            best_score=score;
        }
    }

    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    return 0;
}
