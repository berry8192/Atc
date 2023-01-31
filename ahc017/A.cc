// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

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

vector<int> v_inv(vector<ll> pvv) {
    vector<pair<ll, int>> pa;
	// rep(i, pvv.size()) pa.push_back(make_pair(-pvv[i], i)); // 昇順の場合
	rep(i, pvv.size()) pa.push_back(make_pair(-pvv[i], i));
    sort(all(pa));
    vector<int> rtn;
    rep(i, pa.size()){
        rtn.push_back(pa[i].second);
    }
    return rtn;
}

vector<int> rankOfArray(vector<ll> arr) {
    vector<ll> sorted = arr;
    sort(sorted.begin(), sorted.end(), greater<ll>());
    unordered_map<ll, int> rankMap;
    for (int i = 0; i < sorted.size(); i++) {
        if (!rankMap.count(sorted[i])) {
            rankMap[sorted[i]] = i;
        }
    }
    vector<int> result(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        result[i] = rankMap[arr[i]];
    }
    return result;
}

void preview_edge(int mm, vector<int> vv){
    vector<int> pv(mm, 1);
    rep(i, vv.size()) pv[vv[i]]=i+2;
    PV(pv);
}

//入力
int n, m, d, k;
vector<int> u, v, w, x, y;
int leftmost_v_idx, left_max=1001;

// 構造体
typedef pair<int, int> P;
struct edge{
    int id;
    int to;
    int cost;
    double rad; // -PI<rad<PI

    bool operator<(const edge &in) const{
		return rad<in.rad;
	};
};

// struct polygon{
//     vector<int> edge_id;
// };

struct City{
    vector<vector<int>> base_dist, dist;
    vector<vector<int>> edge_inv;
    vector<vector<edge>> graph;
    vector<int> ans, edge_priority;
    vector<ll> edge_used_fig;
    bitset<3000> outside_edge;

    void init(){
        // cout<< "init" <<endl;
        base_dist.resize(n, vector<int>(n));
        dist.resize(n, vector<int>(n));
        edge_inv.resize(n, vector<int>(n, -1));
        graph.resize(n);
        ans.resize(m, -1);
        edge_used_fig.resize(m);
        rep(i, m){
            // ワーシャルフロイドの時は使う
            // dist[u[i]][v[i]]=w[i];
            // dist[v[i]][u[i]]=w[i];
            double rad=atan2(y[v[i]]-y[u[i]], x[v[i]]-x[u[i]]);
            double radr=atan2(y[u[i]]-y[v[i]], x[u[i]]-x[v[i]]);
            // cout<< rad SP << radr <<endl;
            graph[u[i]].push_back({i, v[i], w[i], rad});
            graph[v[i]].push_back({i, u[i], w[i], radr});
            edge_inv[u[i]][v[i]]=i;
            edge_inv[v[i]][u[i]]=i;
        }
        rep(i, n) sort(all(graph[i]));
    }

    void floyd_warshall() {
        for (int k=0;k<n;k++){
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    // dfs(どの頂点idから来たか、どの頂点idに行くか)
    void outside_dfs(int from, int to){
        // cout<< from SP << to <<endl;
        int esz=graph[to].size();
        int before_edge_id=edge_inv[from][to];
        // cout<< "from edge of: " << before_edge_id <<endl;
        rep(i, esz){
            if(graph[to][i].id==before_edge_id){
                int use_idx=(i+1)%esz;
                edge use_edge=graph[to][use_idx];
                if(outside_edge[use_edge.id]) return;
                outside_edge.set(use_edge.id);
                // testv.push_back(use_edge.id);
                outside_dfs(to, use_edge.to);
                return;
            }
        }
    }
    void search_outside_edge(){
        // vector<int> tmp;
        // rep(i, graph[leftmost_v_idx].size()){
        //     tmp.push_back(graph[leftmost_v_idx][i].id);
        //     cout<< graph[leftmost_v_idx][i].rad SP << x[graph[leftmost_v_idx][i].to] SP << y[graph[leftmost_v_idx][i].to] <<endl;
        // }
        // preview_edge(m, tmp);
        int next_vertex=graph[leftmost_v_idx][0].to;
        outside_edge.set(graph[leftmost_v_idx][0].id);
        // testv.push_back(graph[leftmost_v_idx][0].id);
        outside_dfs(leftmost_v_idx, next_vertex);
        // vector<int> tmp;
        // rep(i, m){
        //     if(outside_edge[i]) tmp.push_back(i);
        // }
        // preview_edge(m, testv);
        // preview_edge(m, tmp);
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
            if(calc_dist[uu] < dd) continue;
            for(int i=0;i<graph[uu].size();++i){
                // ここはedge型に一旦移すと速いはず
                if(ans[graph[uu][i].id]==day) continue;
                int vv = graph[uu][i].to;
                int cost = graph[uu][i].cost;
                if(calc_dist[vv] > dd + cost){
                    calc_dist[vv] = dd + cost;
                    prev[vv] = uu;
                    que.push(P(calc_dist[vv], vv));
                }
            }
        }
    }
    void get_path(const vector<int> &prev, int t) {
        for (int cur = t; prev[cur] != -1; cur = prev[cur]) {
            int tmp=edge_inv[cur][prev[cur]];
            // cout<< cur << "->" << prev[cur] SP << tmp SP;
            if(-1<tmp) edge_used_fig[tmp]++;
        }
        // cout<< endl;
    }
    void dijkstra_base(){
        // cout<< "dijkstra_base" <<endl;
        rep(i, n){
            vector<int> prev(n, -1);
            dijkstra(i, 0, base_dist[i], prev);
            rep(j, n) get_path(prev, j);
            // PV(edge_used);
        }
        // cout<< "dijkstra_base_end" <<endl;
        // rep(i, m) edge_used_fig[i]*=-w[i];
        edge_priority=v_inv(edge_used_fig);
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
    void pickup_NGlist(){
        // 出発してきた辺の隣の添え字の辺を伝うdfsを書く

    }
    void init_ans(){
        rep(i, m) ans[i]=i%d+1;
    }
    ll calc_score(){
        // vector<vector<int>> block(d);
        // rep(i, m) block[ans[i]-1].push_back(i-1);
        ll complain_sum=0, base_sum=calc_dist_sum(base_dist);
        rep3(i, d+1, 1){
            dijkstra_all(i, dist);
            // cout<< calc_dist_sum(dist) SP << base_sum <<endl;
            double day_complain=calc_dist_sum(dist)-base_sum;
            // day_complain/=n*(n-1);
            cout<< "day:" << i SP;
            printf("%.3lf\n", day_complain/n/(n-1));
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
        // 最も右にある点を取得
        if(x[i]<left_max){
            left_max=x[i];
            leftmost_v_idx=i;
        }
    }
}

int main(){
    // cout<< "main" <<endl;
    inpt();
    City city;
    city.init();
    city.search_outside_edge();
    return 0;
    // rep(i, n) PV(city.edge_inv[i]);
    // city.floyd_warshall();
    // cout<< city.dist_sum <<endl;
    city.init_ans();
    // city.print_ans();
    city.dijkstra_base();
    sort(all(city.edge_used_fig));
    // PV(city.edge_used_fig);
    // PV(city.edge_priority);
    rep(i, m){
        // if(city.edge_priority[i]>1130){
        //     cout<< "1 ";
        // }else if(city.edge_priority[i]<11){
        //     cout<< "2 ";
        // }else{
        //     cout<< "3 ";
        // }
        // cout<< city.edge_priority[i]/((m+d-1)/d)+1 SP;
    }
    cout<< city.calc_score() <<endl;

    return 0;
}
