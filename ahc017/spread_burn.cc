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
double TIME_LIMIT=5900;
double start_temp;
double end_temp=0.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i]+1 SP;
	cout<< pvv[pvv.size()-1]+1 <<endl;
}

template <class T> void PS(T ps) {
    cout<< "{";
	for(auto itr = ps.begin(); itr != ps.end(); ++itr) cout<< *itr SP;
	cout<< "}" <<endl;
}

template <class T> T v_inv(T pvv) {
    vector<pair<int, int>> pa;
	// rep(i, pvv.size()) pa.push_back(make_pair(-pvv[i], i)); // 昇順の場合
	rep(i, pvv.size()) pa.push_back(make_pair(-pvv[i], i));
    sort(all(pa));
    vector<int> rtn;
    rep(i, pa.size()) rtn.push_back(pa[i].second);
    return rtn;
}

//入力
int n, m, d, k;
vector<int> u, v, w;
vector<double> xx, yy;

// 構造体
struct edge{
    int id;
    int from;
    int to;
    double x;
    double y;
    double rad;

    double distance(edge &in){
        double dis=sqrt((x-in.x)*(x-in.x)+(y-in.y)*(y-in.y));
        double ang=min(abs(rad-in.rad), M_PI-abs(rad-in.rad));
        ang=2.0-ang;
        return dis*ang;
    }
};

vector<edge> vv;
vector<int> ans, cnt;
vector<set<int>> st;
vector<double> sco;
void inpt(){
    // cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    xx.resize(n);
    yy.resize(n);
    ans.resize(m);
    st.resize(d);
    sco.resize(d);
    cnt.resize(d);
    rep(i, m){
        cin>> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
    }
    rep(i, n){
        cin>> xx[i] >> yy[i];
    }
    rep(i, m){
        double rad=atan2(yy[u[i]]-yy[v[i]], xx[u[i]]-xx[v[i]]);
        if(rad<0.0) rad+=M_PI;
        vv.push_back({i, u[i], v[i], (xx[u[i]]+xx[v[i]])/2.0, (yy[u[i]]+yy[v[i]])/2.0, rad});
    }
}

void init_score(){
    rep(i, d){
        double dis=0.0;
        map<int, int> mp;
        for(auto itr = st[i].begin(); itr != st[i].end(); ++itr){
            dis-=1000.0*mp[vv[*itr].from];
            dis-=1000.0*mp[vv[*itr].to];
            mp[vv[*itr].from]++;
            mp[vv[*itr].to]++;
            double mi=99999999999.9;
            for(auto itr2 = st[i].rbegin(); *itr2 != *itr; ++itr2){
                mi=min(mi, vv[*itr].distance(vv[*itr2]));
            }
            dis+=mi;
        }
        sco[i]=dis;
    }
}

bool does_score_up(int day1, int day2){
    // cout<< "in does_score_up" <<endl;
    double before=sco[day1]+sco[day2];
    double after=0.0;
    // cout<< day1 SP << day2 <<endl;
    map<int, int> mp1;
    for(auto itr = st[day1].begin(); itr != st[day1].end(); ++itr){
        after-=1000.0*mp1[vv[*itr].from];
        after-=1000.0*mp1[vv[*itr].to];
        mp1[vv[*itr].from]++;
        mp1[vv[*itr].to]++;
        // cout<< *itr <<endl;
        double mi=99999999999.9;
        for(auto itr2 = st[day1].rbegin(); *itr2 != *itr; ++itr2){
            mi=min(mi, vv[*itr].distance(vv[*itr2]));
        }
        after+=mi;
    }
    // cout<< "middle" <<endl;
    map<int, int> mp2;
    for(auto itr = st[day2].begin(); itr != st[day2].end(); ++itr){
        after-=1000.0*mp2[vv[*itr].from];
        after-=1000.0*mp2[vv[*itr].to];
        mp2[vv[*itr].from]++;
        mp2[vv[*itr].to]++;
        double mi=99999999999.9;
        for(auto itr2 = st[day2].rbegin(); *itr2 != *itr; ++itr2){
            mi=min(mi, vv[*itr].distance(vv[*itr2]));
        }
        after+=mi;
    }
    // cout<< "end does_score_up" <<endl;
    return before<after;
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    rep(i, m){
        int day=i%d;
        ans[i]=day;
        st[day].insert(i);
        cnt[day]++;
    }
    init_score();

    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        // if(lp%100==0) PV(ans);
        // cout<< "lp:" << lp <<endl;
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;

        int type=mt()%100;
        int from=mt()%m;
        int to=(from+mt()%(m-1))%m;
        int tmp=ans[from];
        // cout<< "from:" << from SP << "to:" << to <<endl;
        // cout<< "ans[from]:" << ans[from] SP << "ans[to]:" << ans[to] <<endl;
        if(type<100){
            st[ans[from]].erase(from);
            st[ans[to]].erase(to);
            st[ans[from]].insert(to);
            st[ans[to]].insert(from);
            swap(ans[from], ans[to]);
        }else{
            // if(cnt[to]==k) continue;
            // cnt[from]--;
            // cnt[to]++;
            // st[ans[from]].erase(from);
            // st[ans[to]].insert(from);
            // ans[from]=ans[to];
        }

        if(does_score_up(ans[from], ans[to])){
            if(type<100){
                st[ans[from]].erase(to);
                st[ans[to]].erase(from);
                st[ans[from]].insert(from);
                st[ans[to]].insert(to);
                swap(ans[from], ans[to]);
            }else{
                // cnt[from]++;
                // cnt[to]--;
                // st[ans[to]].erase(from);
                // st[ans[from]].insert(from);
                // ans[from]=tmp;
            }
        }
    }
    PV(ans);

    return 0;
}
