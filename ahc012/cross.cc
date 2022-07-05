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
double TIME_LIMIT=2980;
double start_temp=2000.0;
double end_temp=10.0;

//入力など
int n, k, sua=0, sec, nsco=0, psco=0, nev=0, pev=0, idx, lp=0;
vector<int> a(11), x, y, d(5010);
vector<int> px(100), py(100), qx(100), qy(100);
vector<int> apx(100), apy(100), aqx(100), aqy(100);
int bo[90][90], xx[5010], yy[5010];

void inpt(){
    cin>> n >> k;
    x.resize(n);
    y.resize(n);
    rep3(i, 11, 1){
        cin>> a[i];
        sua+=a[i];
    }
    rep(i, n) cin>> x[i] >> y[i];
    //cout<< "sua=" << sua <<endl;
}

void init(){
    // 番兵として両端点にいてもらう
    sec=sqrt(sua)*1.2;
    sec=min(sec, 48);
    sec=max(sec, 10);
    //横の線つくる
    rep(i, sec+1){
        px[i]=-9999999;
        py[i]=(20000.0/sec)*i-10000;
        qx[i]=9999999;
        qy[i]=(20000.0/sec)*i-10000+1;
    }
    //縦の線つくる
    rep(i, sec+1){
        px[i+sec+1]=(20000.0/sec)*i-10000;
        py[i+sec+1]=-9999999;
        qx[i+sec+1]=(20000.0/sec)*i-10000+1;
        qy[i+sec+1]=9999999;
    }
}

//初回用スコアの計算
void init_score(){
    rep(i, n){
        // cout<< "(x, y)= " << x[i] SP << y[i] <<endl;
        // cout<< x[i]/(20000/sec)+sec/2 SP << y[i]/(20000/sec)+sec/2 <<endl;
        //bo[int((x[i]+10000)/20000.0*(sec))][int((y[i]+10000)/20000.0*(sec))]++;
        if(lp==1){
            rep(j, sec){
                if((py[j]-y[i])*(py[j+1]-y[i])<=0){
                    yy[i]=j+1;
                    break;
                }
            }
            rep(j, sec){
                if((px[j+sec+1]-x[i])*(px[j+sec+2]-x[i])<=0){
                    xx[i]=j+1;
                    break;
                }
            }
        }else if(idx<sec){
            //if(abs(yy[i]-idx)<3 || lp==1){
                rep(j, sec){
                    if((py[j]-y[i])*(py[j+1]-y[i])<=0){
                        yy[i]=j+1;
                        break;
                    }
                }
            //}
        }else{
            //if(abs(xx[i]-(idx-sec-1))<3 || lp==1){
                rep(j, sec){
                    if((px[j+sec+1]-x[i])*(px[j+sec+2]-x[i])<=0){
                        xx[i]=j+1;
                        break;
                    }
                }
            //}
        }

        // auto xub=upper_bound(py.begin(), py.begin()+sec, y[i]-1);
        // xx=xub-py.begin();
        // auto yub=upper_bound(px.begin()+sec+1, px.end(), x[i]-1);
        // yy=yub-px.begin()+sec+1;

        // if(xx<0 || sec<xx || yy<0 || sec<<yy){
        //     d[1]=100000000;
        // }else{
        //     bo[xx][yy]++;
        // }
        bo[xx[i]][yy[i]]++;
    }
    rep(i, sec+1) rep(j, sec+1) d[bo[i][j]]++;

    // rep(i, sec+1){
    //     rep(j, sec+1){
    //         cout<< bo[i][j] SP;
    //     }
    //     cout<< endl;
    // }
    // rep(i, 5001){
    //     if(d[i]) cout<< "(i, cnt)= " << i SP << d[i] <<endl;
    // }
}

void score(){
    int cor=0;
    int ev=0;
    rep3(i, 11, 1){
        cor+=min(a[i], d[i]);
        //cor-=abs(a[i]-d[i]);
    }
    // rep3(i, 50, 11){
    //     ev+=d[i]*i*i;
    //     cor-=d[i];
    // }
    psco=round(1000000.0*cor/sua);
    pev=ev;
}

void print_ans(){
    cout<< sec*2+2 <<endl;
    //rep(i, sec*2+2) cout<< apx[i] SP << apy[i] SP << aqx[i] SP << aqy[i] <<endl;
    rep(i, sec*2+2) cout<< px[i] SP << py[i] SP << qx[i] SP << qy[i] <<endl;
}

int main(){

    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    //乱数の準備
    int seed=10000;
    //auto seed=(unsigned)time(NULL);
    mt19937 mt(seed);

    rep(i, 60) rep(j, 60) bo[i][j]=0;
    // rep(i, 5010){
    //     xx[i]=-1;
    //     yy[i]=-1;
    // }

    //入力
    inpt();
    //初期状態の計算
    init();
    // 各セクションに入っている点の個数を求める
    init_score();
    // 評価関数とスコアの計算
    score();
    nsco=psco;
    nev=pev;
    //cout<< nsco SP << nev <<endl;

    //焼きなまし
    while (true) { // 時間の許す限り回す
        lp++;
        //cout<< lp <<endl;
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
        //if(lp==20000) break;

        int type=mt()%2+1;
        int mvp;
        int mvm;
        int del;
        if(type==1){
            //横の線（1~sec-1）をずらす
            idx=mt()%(sec-1)+1;
            mvp=(py[idx+1]-py[idx])/3;
            mvm=(py[idx]-py[idx-1])/3;
            del=mt()%(mvp+mvm)-mvm;
            py[idx]+=del;
            qy[idx]+=del;
        }else{
            //縦の線（横の線+sec）をずらす
            idx=mt()%(sec-1)+2+sec;
            mvp=(px[idx+1]-px[idx])/3;
            mvm=(px[idx]-px[idx-1])/3;
            del=mt()%(mvp+mvm)-mvm;
            px[idx]+=del;
            qx[idx]+=del;
        }
        // cout<< "idx=" << idx <<endl; 
        // cout<< "mvp=" << mvp <<endl; 
        // cout<< "mvm=" << mvm <<endl; 
        // cout<< "del=" << del <<endl; 
        rep(i, 60) rep(j, 60) bo[i][j]=0;
        rep(i, 50) d[i]=0;
        init_score();
        score();

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * chrono::duration_cast<chrono::milliseconds>(current - start).count() / TIME_LIMIT;
        // 遷移確率関数(最大化の場合)
        double prob = exp((psco-nsco)/temp);

        if (prob > (mt()%imax)/(double)imax) { // 確率probで遷移する
        //if (nsco<psco) {
            nsco=psco;
            nev=pev;
        }else{
            if(type==1){
                py[idx]-=del;
                qy[idx]-=del;
            }else{
                px[idx]-=del;
                qx[idx]-=del;
            }
        }
    }

    //cout<< lp <<endl;
    print_ans();

	return 0;
}