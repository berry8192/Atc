#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
// using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int n, d, q;

struct Interval{
    int l;
    int r;

    Interval(){};
    Interval(int il, int ir){
        l=il;
        r=ir;
    };

    void is_valid(){
        assert(l<=r);
    }
    int get_middle(){
        assert(l==r);
        return l;
    }
};

struct Item{
    Interval order;
    vector<int> index;

    Item(){};
    Item(Interval iorder, vector<int> iindex){
        order=iorder;
        index=iindex;
    };

    int get_order(){
        return order.get_middle();
    }
};

bool query(vector<int> l, vector<int> r){
    cout<< l.size() SP << r.size() SP;
    rep(i, l.size()) cout<< l[i] SP;
    rep(i, r.size()) cout<< r[i] SP;
    cout<< endl;

    char tmp;
    cin>> tmp;
    return (tmp=='<');
}

struct Goods{
    int remain_query; // 残りクエリ可能回数
    vector<Item> items; // 挿入ソート済みアイテム
    vector<vector<int>> item_list; // 未ソートアイテム

    void init(){
        remain_query=q;
        make_item(calc_allow_sort_count());
    }
    // Qの数からソート可能なNの上限を求める、制約から解Xは(N/2<=X<=N)、N=30で21, N=100で51
    int calc_allow_sort_count(){
        int rtn=n;
        int tmp=0;
        rep3(i, n+1, 2){
            int divi=i;
            while(divi>=2){
                divi/=2;
                tmp++;
            }
            if(q<tmp){
                rtn=i-1;
                break;
            }
        }
        return rtn;
    }
    void make_item(int item_count){
        item_list.resize(item_count);
        rep(i, n) item_list[i%item_count].push_back(i);
    }
    void insert_sort(){
        rep(i, n){

        }
    }

    void print_ans(){
    }
};

void inpt(){
    cin>> n >> d >> q;
    // rep(i, q) query({0}, {1});
    // rep(i, n) cout<< 0 SP;
    // cout<< endl;
}

int main(){
    inpt();
    Goods goods;

    goods.init();
    PVV(goods.item_list);
    goods.print_ans();

    return 0;
}
