#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
typedef __int128_t ll;

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
/*
二元一次不定方程式 ax+by=c(a≠0かつb≠0) を解く
初期化すると、x=x0+m*b,y=y0-m*aで一般解が求められる(m=0で初期化)
llは32bit整数まで→超えたらPythonに切り替え
*/
struct LDE{
    ll a,b,c,x,y;
    ll m=0;
    bool check=true;//解が存在するか

    //初期化
    LDE(ll a_,ll b_,ll c_): a(a_),b(b_),c(c_){
        ll g=gcd(a,b);
        if(c%g!=0){
            check=false;
        }else{
            //ax+by=gの特殊解を求める
            extgcd(abs(a),abs(b),x,y);
            if(a<0)x=-x;
            if(b<0)y=-y;
            //ax+by=cの特殊解を求める(オーバフローに注意！)
            x*=c/g;y*=c/g;
            //一般解を求めるために割る
            a/=g;b/=g; 
        }
    }

    //拡張ユークリッドの互除法
    //返り値:aとbの最大公約数
    ll extgcd(ll a,ll b,ll &x0,ll &y0){
        if(b==0){
            x0=1;
            y0=0;
            return a;
        }
        ll d=extgcd(b,a%b,y0,x0);
        y0-=a/b*x0;
        return d;
    }

    //パラメータmの更新(書き換え)
    void m_update(ll m_){
        x+=(m_-m)*b;
        y-=(m_-m)*a;
        m=m_;
    }
};

int main(){

	ll n, x, y, p, q, mi;

	cin>> n;

	rep(i, n) {
		cin>> x, y, p, q;
		mi=9223372036854775807;
		for(int i=)
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}