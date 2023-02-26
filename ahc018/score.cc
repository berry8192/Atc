#pragma GCC target("avx")
#pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

// 定数周り
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp;
double end_temp=0.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

//入力
int n, m, d, k;
vector<int> u, v, w, x, y;

// 構造体
typedef pair<int, int> P;
struct edge{
    int id;
    int to;
    int cost;
};

struct Land{
    vector<vector<int>> base_dist, dist;
    vector<vector<edge>> graph;
    vector<int> ans;

    void init(){
        // cout<< "init" <<endl;
        base_dist.resize(n, vector<int>(n));
        dist.resize(n, vector<int>(n));
        graph.resize(n);
        ans.resize(m, -1);
        rep(i, m){
            graph[u[i]].push_back({i, v[i], w[i]});
            graph[v[i]].push_back({i, u[i], w[i]});
        }
    }

    void dijkstra(int start, int day, vector<int>& calc_dist, vector<int>& prev){
        // cout<< "dijkstra " << start <<endl;
        priority_queue< P, vector<P>, greater<P> > que;
        fill(all(calc_dist), INF);
        // fill(all(prev), -1);
        calc_dist[start] = 0;
        que.push(P(0, start));
        while(que.size()){
            int dd = que.top().first;
            int uu = que.top().second;
            que.pop();
            if(calc_dist[uu] != dd) continue;
            for(int i=0;i<graph[uu].size();++i){
                // ここはedge型に一旦移すと速いはず
                edge nedge=graph[uu][i];
                if(ans[nedge.id]==day) continue;
                int vv = nedge.to;
                int cost = nedge.cost;
                if(calc_dist[vv] > dd + cost){
                    calc_dist[vv] = dd + cost;
                    prev[vv] = uu;
                    que.push(P(calc_dist[vv], vv));
                }
            }
        }
    }
    void dijkstra_base(){
        // cout<< "dijkstra_base" <<endl;
        rep(i, n){
            vector<int> prev(n, -1);
            dijkstra(i, 0, base_dist[i], prev);
        }
    }
    void dijkstra_all(int day, vector<vector<int>>& calc_dist){
        rep(i, n){
            vector<int> prev(n, -1);
            dijkstra(i, day, calc_dist[i], prev);
        }
    }
    ll calc_dist_sum(vector<vector<int>>& calc_dist){
        ll dist_sum=0;
        rep(i, n){
            rep3(j, n, i+1){
                dist_sum+=calc_dist[i][j];
            }
        }
        dist_sum*=2;
        return dist_sum;
    }
    void init_ans(){
        rep(i, m){
            cin>> ans[i];
            // ans[i]--;
        }
    }
    ll calc_score(){
        ll complain_sum=0, base_sum=calc_dist_sum(base_dist);
        rep3(i, d+1, 1){
            dijkstra_all(i, dist);
            double day_complain=calc_dist_sum(dist)-base_sum;
            complain_sum+=day_complain;
        }
        return round(1000.0*complain_sum/(d*n*(n-1)));
    }
    void print_ans(){
        rep(i, m) cout<< ans[i] SP;
        cout<< endl;
    }
};


void inpt(){
    // cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    x.resize(n);
    y.resize(n);
    rep(i, m){
        cin>> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
    }
    rep(i, n){
        cin>> x[i] >> y[i];
    }
}

int main(){
    // cout<< "main" <<endl;
    inpt();
    Land city;
    city.init();
    // cout<< "#" <<endl;
    city.init_ans();
    // cout<< "#" <<endl;
    city.dijkstra_base();
    // PV(city.edge_used);
    // PV(city.edge_priority);
    cout<< city.calc_score() <<endl;

    return 0;
}
