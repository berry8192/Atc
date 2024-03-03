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
double TIME_LIMIT=1.9;
double start_temp=50.0;
double end_temp=10.0;

//入力など
int n;
int ansi;
vector<int> ans1, ans2;
ll sco1=0, sco2=0;

//スコアの計算
ll calc_score(int idx){
    ll rtn=0;
    if(idx==1){

    }else{

    }
    return rtn;
}

int main(){

    //開始時間の計測
    double start_time;

    //乱数の準備
    int seed=10000;
    mt19937 mt(seed);
    rep(i, 10) cout<< mt() <<endl;

    //入力
    cin>> n;

    //初期状態の計算（貪欲やらランダムやら）

    //焼きなまし
    while (true) { // 時間の許す限り回す
        double now_time; // 現在時刻
        if (now_time - start_time > TIME_LIMIT) break;

        if(ansi){

        }else{

        }
        int new_score = calc_score(2);
        int pre_score = calc_score(1);

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * (now_time-start_time) / TIME_LIMIT;
        // 遷移確率関数(最大化の場合)
        double prob = exp((new_score-pre_score)/temp);

        if (prob > (mt()%lmax)/(double)lmax) { // 確率probで遷移する
            ansi=2-ansi;
        }
    }

    //答え出力
    rep(i, 200){
        if(ansi==1) cout<< ans1[i] <<endl;
        else cout<< ans1[i] <<endl;
    }

	return 0;
}