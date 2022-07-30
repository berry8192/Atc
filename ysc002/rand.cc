#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

//定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=2.9;
double start_temp=50.0;
double end_temp=10.0;

//入力など
int n, m;
vector<int> a, b;

//スコアの計算
ll calc_score(int idx){
    ll rtn=0;
    if(idx==1){

    }else{

    }
    return rtn;
}

void print_ans(int sz){
    cout<< sz <<endl;
    rep(i, sz) cout<< px[i] SP << py[i] SP << qx[i] SP << qy[i] <<endl;
}

int main(){

    //開始時間の計測
    double start_time;

    //乱数の準備
    int seed=10000;
    mt19937 mt(seed);
    //rep(i, 10) cout<< mt() <<endl;

    //入力
    cin>> n >> k;
    x.resize(n);
    y.resize(n);
    rep3(i, 11, 1) cin>> a[i];
    rep(i, n) cin>> x[i] >> y[i];

    //初期状態の計算（貪欲やらランダムやら）
    double r, t;
    rep(i, 100){
        r=mt()%10000;
        // string s;
        // rep(j, r) s+=to_string(mt()%9+1);
        // r=stoi(s);
        t=(mt()%6283184)/1000000.0;
        px[i]=r*cos(t);
        py[i]=r*sin(t);
        t=(mt()%6283184)/1000000.0;
        qx[i]=1000000000*cos(t);
        qy[i]=1000000000*sin(t);
    }
    print_ans(100);
    return 0;

    //焼きなまし
    while (true) { // 時間の許す限り回す
        double now_time; // 現在時刻
        if (now_time - start_time > TIME_LIMIT) break;

        int new_score = calc_score(2);
        int pre_score = calc_score(1);

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * (now_time-start_time) / TIME_LIMIT;
        // 遷移確率関数(最大化の場合)
        double prob = exp((new_score-pre_score)/temp);

        if (prob > (mt()%lmax)/(double)lmax) { // 確率probで遷移する
           // ansi=2-ansi;
        }
    }

	return 0;
}