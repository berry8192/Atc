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
vector<vector<int>> to = {
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};
vector<int> di = {0, -1, 0, 1}, dj = {-1, 0, 1, 0};
vector<int> rot = {1, 2, 3, 0, 5, 4, 7, 6};

//焼きなましの定数
double TIME_LIMIT=1.9;
double start_temp=50.0;
double end_temp=10.0;

//入力など
char c;
int ans[30][30];
int sco[30][30];
int t[30][30];
int cha[30][30];
int ox, oy;
vector<int> ri, rj;

//スコアの計算
int calc_score(){
    int rtn, p1=0, p2=0;
    rep(i, 30){
        rep(j, 30){
            sco[i][j]=-1;
        }
    }
    rep(i, 30){
        rep(j, 30){
            if(sco[i][j]==-1){
                int ci=i;
                int cj=j;
                int cd=0;
                int dep=0;
                while(true){
                    if(sco[i][j]!=-1 && !(4<=t[i][j] && t[i][j]<=5)) break;
                    sco[i][j]=dep;
                    int ct=t[ci][cj];
                    rep(i, ans[ci][cj]){
                        ct=rot[ct];
                    }
                    int d2 = to[ct][cd];
                    if (d2 == -1){
                        ri.push_back(ci);
                        rj.push_back(cj);
                        break;
                    }
                    //cout<< ci SP << cj SP << d2 <<endl;
                    ci += di[d2];
                    cj += dj[d2];
                    if (ci < 0 || ci >= 30 || cj < 0 || cj >= 30) break;
                    cd = (d2 + 2) % 4;
                    dep++;
                    if (i == ci && j == cj && cd == 0){
                        //cout<< dep <<endl;
                        if(p1<dep){
                            p2=p1;
                            p1=dep;
                        }else if(p2<dep){
                            p2=dep;
                        }
                        break;
                    }
                }
            }
        }
    }
    rtn=p1*p2;

    return rtn;
}

int main(){

    //開始時間の計測
    double start_time=clock();

    //乱数の準備
    int seed=100000;
    mt19937 mt(seed);
    //rep(i, 10) cout<< mt() <<endl;

    //入力
    rep(i, 30) rep(j, 30){
        cin>> c;
        t[i][j]=c-'0';
        ans[i][j]=0;
    }

    //初期状態の計算（貪欲やらランダムやら）
    int pre_score=calc_score();

    //焼きなまし
    rep(i, 40000) { // 時間の許す限り回す
        //double now_time=clock(); // 現在時刻
        //if ((now_time - start_time)/ > TIME_LIMIT) break;

        // rep(i, ri.size()){
        //     if(1 || mt()%2){
        //         ans[ri[i]][rj[i]]++;
        //         ans[ri[i]][rj[i]]%=4;
        //     }
        // }
        // ri.clear();
        // rj.clear();
        rep(i, 30){
            rep(j, 30){
                if(int(mt())%6==1){
                    cha[i][j]=mt()%3;
                    ans[i][j]+=cha[i][j];
                    ans[i][j]%=4;
                }else{
                    cha[i][j]=0;
                }
                //cout<< ans[i][j];
            }
            //cout<< endl;
        }
        int new_score=calc_score();
        // cout<< new_score <<endl;
        // rep(i, 900){
        //     cout<< ans[i/30][i%30];
        // }
        // cout<< endl;

        // // 温度関数
        // double temp = start_temp + (end_temp - start_temp) * (now_time-start_time) / TIME_LIMIT;
        // // 遷移確率関数(最大化の場合)
        // double prob = exp((new_score-pre_score)/temp);

        // if (prob > (mt()%lmax)/(double)lmax) { // 確率probで遷移する
            
        if(pre_score<new_score){
            //cout<< "up " << pre_score SP << new_score <<endl;
            pre_score=new_score;
        }else{
            //cout<< "down " << pre_score SP << new_score <<endl;
            rep(i, 30) rep(j, 30){
                if(cha[i][j]){
                    ans[i][j]-=cha[i][j]-4;
                    ans[i][j]%=4;
                }
            }
        }
    }

    //答え出力
    rep(i, 900){
        cout<< ans[i/30][i%30];
    }
    cout<< endl;

	return 0;
}