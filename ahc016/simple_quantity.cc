// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

#define QUESTIONS 100

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
bool debug_mode=false;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp=50.0;
double end_temp=10.0;
int lp=0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

//入力
int m, eps;
string in_eps;

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

struct Query{
    string h;
    int ans;
};

// 構造体
struct Graphs{
    int n, vertex, diff;
	vector<bitset<4950>> g;
    vector<double> simple_variance;

	void init(){
        n=calc_v_size();
        vertex=n*(n-1)/2;
        g.resize(m);
        simple_variance.resize(m);
    }
    int calc_v_size(){
        // mのサイズそのまま
        return m;
    }

    void simple_create_graph(){
        diff=vertex/m;
        int bit_quantity=0;
        rep(i, m){
            rep(j, bit_quantity){
                g[i].set(j);
            }
            simple_variance[i]=(bit_quantity*(100-eps)+(vertex-bit_quantity)*eps)/100.0;
            bit_quantity+=diff;
        }
    }
    // void print_graph(){
    //     rep(i, m){
    //         rep(j, vertex){
    //             cout<< g[i][j];
    //         }
    //         cout<<endl;
    //     }
    // }
    Query gen_query(){
        Query rtn;
        rtn.ans=mt()%n;
        bitset<4950> tmp=g[rtn.ans];
        rep(i, vertex){
            if(eps>mt()%100) tmp.flip(i);
            if(tmp[i]) rtn.h+='1';
            else rtn.h+='0';
        }
        return rtn;
    }

    int guess(string s){
        bitset<4950> h(s);
        int bit_quantity=h.count();
        // int ans=round(1.0*bit_quantity/diff);
        int ans=0;
        double diff=9999.0;
        rep(i, m){
            if(diff>abs(bit_quantity-simple_variance[i])){
                ans=i;
                diff=bit_quantity-simple_variance[i];
            }
        }
        return ans;
    }
};

void inpt(){
    //cout<< "inpt" <<endl;
    cin>> m;
    if(m>100){
        m-=100;
        debug_mode=true;
    }
    cin>> in_eps;
    eps=stoi(in_eps.substr(2));
    // cout<< eps <<endl;
}

void solve(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();

    Graphs graphs;
    graphs.init();
    graphs.simple_create_graph();

    cout<< graphs.n <<endl;
    rep(i, m){
        rep(j, graphs.vertex){
            cout<< graphs.g[i][j];
        }
        cout<<endl;
    }

    rep(i, QUESTIONS){
        string h;
        int ans;
        if(debug_mode){
            Query query=graphs.gen_query();
            h=query.h;
            ans=query.ans;
        }else{
            cin>> h;
        }
        cout << graphs.guess(h) <<endl;
    }
}

int main(){
    solve();
}
