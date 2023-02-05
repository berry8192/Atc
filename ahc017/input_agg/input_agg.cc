// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define CS << ", " 
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

template <typename T>
class SafeVector : public std::vector<T>
{
public:
  // int 型の引数を1つ取るコンストラクタ
  SafeVector(int idx = 0)
  {
    this->resize(idx);
  }

  // 添え字演算子をオーバーロード
  T& operator[](int idx)
  {
    // 配列外参照の場合は、異常終了する
    if (idx < 0 || idx >= this->size())
    {
        cout<< "index limit: " << this->size() <<endl;
        cout<< "given index: " << idx <<endl;
      throw std::out_of_range("配列外参照してます");
    }

    return std::vector<T>::operator[](idx);
  }
};

//入力
int n, m, d, k;
vector<int> u, v, w;

// 構造体
struct City{
    vector<vector<int>> dist;
    vector<int> ans;
    ll dist_sum=0;

    void init(){
        dist.resize(n, vector<int>(n, INF));
        ans.resize(m);
        rep(i, m){
            dist[u[i]][v[i]]=w[i];
            dist[v[i]][u[i]]=w[i];
        }
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
    void calc_dist_sum(){
        rep(i, n){
            rep3(j, n, i+1){
                dist_sum+=dist[i][j];
            }
        }
    }
    void init_ans(){
        int lp=0;
        while(lp<m){
            ans[lp]=lp%d+1;
            lp++;
        }
    }

    void print_ans(){
        rep(i, m) cout<< ans[i] SP;
        cout<< endl;
    }
};

void inpt(){
    //cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    rep(i, m){
        cin>> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
    }
}

int main(){
    inpt();
    City city;
    city.init();
    city.floyd_warshall();
    city.calc_dist_sum();
    // cout<< "N, M, M/N, D, K, M/D, dist_sum" <<endl;
    cout<< n CS << m CS << 1.0*m/n CS << d CS << k CS << 1.0*m/d CS << city.dist_sum <<endl;
    return 0;
}
