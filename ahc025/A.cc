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
    int index;

    Item(){};
    Item(Interval iorder, int iindex){
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

    void init(){
    }

    void print_ans(){
    }
};

void inpt(){
    cin>> n >> d >> q;
}

int main(){
    inpt();
    Goods goods;

    goods.print_ans();

    return 0;
}
