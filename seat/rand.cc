#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

#define HEIGHT 
#define WIDTH 
#define TEAMS 
#define LOW_SCORE_STREAK_LIMIT 30000
#define MAX_ROTATE 4
#define ANSWER_FIGURE 2000

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=10;
mt19937 mt(seed);

vector<int> PEOPLE={};
int people_sum=0;
vector<string> SEAT={
};

int best_ans[HEIGHT][WIDTH], current_ans[HEIGHT][WIDTH];
vector<int> h_usable_seat, w_usable_seat; // 座れる席の逆引き用配列
int best_score=imax, new_score, best_ans_score=imax;
int dir_h[]={0, -1, 0, 1}, dir_w[]={-1, 0, 1, 0};

void init(){
    vector<int> team_num;
    rep(i, TEAMS){
        rep(j, PEOPLE[i]){
            team_num.push_back(i);
        }
    }
    people_sum=team_num.size();
    rep(i, HEIGHT){
        rep(j, WIDTH){
            if(SEAT[i][j]=='#'){
                current_ans[i][j]=-1;
            }else{
                int idx=mt()%team_num.size();
                current_ans[i][j]=team_num[idx];
                team_num.erase(team_num.begin()+idx);

                h_usable_seat.push_back(i);
                w_usable_seat.push_back(j);
            }
        }
    }
}

int calc_two_seat_score(int h1, int w1, int h2, int w2){
    int two_seat_score=0;
    // two_seat_score+=abs(h1-h2)*2;
    // two_seat_score+=abs((w1+1)/2-(w2+1)/2)*20;
    // two_seat_score+=abs(w1-w2)*5;
    two_seat_score+=(h1-h2)*(h1-h2);
    two_seat_score+=((w1+1)/2-(w2+1)/2)*((w1+1)/2-(w2+1)/2)*20;
    two_seat_score+=(w1-w2)*(w1-w2)*3;
    return two_seat_score;
}

int calc_score(){
    int score=0;
    rep(i, HEIGHT*WIDTH){
        int h1=i/WIDTH, w1=i%WIDTH;
        int neighbor=0;
        rep(j, 4){
            if(h1+dir_h[j]<0 || h1+dir_h[j]>=HEIGHT || w1+dir_w[j]<0 || w1+dir_w[j]>=WIDTH) continue;
            if(current_ans[h1][w1]==current_ans[h1+dir_h[j]][w1+dir_w[j]]) neighbor++;
        }
        if(neighbor<=1) score+=10;
        if(neighbor<=2) score+=10;
        rep3(j, HEIGHT*WIDTH, i+1){
            int h2=j/WIDTH, w2=j%WIDTH;
            assert(0<=h1 && h1<HEIGHT);
            assert(0<=w1 && w1<WIDTH);
            assert(0<=h2 && h2<HEIGHT);
            assert(0<=w2 && w2<WIDTH);
            if(current_ans[h1][w1]==current_ans[h2][w2]) score+=calc_two_seat_score(h1, w1, h2, w2);
        }
    }
    return score;
}

void print_ans(){
    rep(i, HEIGHT){
        rep(j, WIDTH){
            assert(-1<=current_ans[i][j] && current_ans[i][j]<TEAMS);
            cout<< current_ans[i][j]+1;
        }
        cout<< endl;
    }
}

int main(){

    rep(nth_try, ANSWER_FIGURE){
        // 初期状態を作成
        init();
        // 初期状態のスコアを計算
        best_score=calc_score();

        int loop=0;
        int low_score_streak=0;
        // vector<int> accept_rotate(MAX_ROTATE+1);
        while (true) {
            loop++;

            int type=mt()%1+1;
            int rotate=mt()%(MAX_ROTATE-1)+2; // (2<=rotate<=MAX_ROTATE)
            vector<int> h_idx, w_idx;
            if(type==1){
                // ランダムにrotate個の座席を入れ替える（indexを1ずつずらす）
                // 同じ席が選ばれることもあるけど許す
                rep(i, rotate){
                    int idx=mt()%people_sum;
                    h_idx.push_back(h_usable_seat[idx]);
                    w_idx.push_back(w_usable_seat[idx]);
                }
                rep(i, rotate) assert(0<=current_ans[h_idx[i]][w_idx[i]] && current_ans[h_idx[i]][w_idx[i]]<TEAMS);
                rep(i, rotate-1) swap(current_ans[h_idx[0]][w_idx[0]], current_ans[h_idx[i+1]][w_idx[i+1]]);
            }else{
                assert(false);
            }
            
            new_score=calc_score();

            if(best_score>new_score){
                low_score_streak=0;
                best_score=new_score;
                // accept_rotate[rotate]++;
            }else{
                if(type==1){
                    repr(i, rotate-1) swap(current_ans[h_idx[0]][w_idx[0]], current_ans[h_idx[i+1]][w_idx[i+1]]);
                }
                low_score_streak++;
                if(low_score_streak==LOW_SCORE_STREAK_LIMIT) break;
            }
        }
        // rep3(i, MAX_ROTATE+1, 2) cout<< i << " rotate:" << accept_rotate[i] << " times" <<endl;

        if(best_ans_score>best_score){
            cout<< "answer:" << nth_try+1 <<endl;
            cout<< "loop:" << loop <<endl;
            cout<< "best_score:" << best_score <<endl;
            best_ans_score=best_score;
            rep(i, HEIGHT){
                rep(j, WIDTH){
                    best_ans[i][j]=current_ans[i][j];
                }
            }
            print_ans();
        }
    }

	return 0;
}