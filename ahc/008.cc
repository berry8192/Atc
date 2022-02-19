#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

int n, m, rdy=0, ul=60, uli;
string s, ans;
vector<int> px, py, pt, hx, hy, ox, oy;

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){

	cin>> n;
	px.resize(n);
	py.resize(n);
	pt.resize(n);
	rep(i, n) cin >> px[i] >> py[i] >> pt[i];

	cin>> m;
	hx.resize(m);
	hy.resize(m);
	ox.resize(m);
	oy.resize(m);
	rep(i, m){
        cin >> hx[i] >> hy[i];
        if(hx[i]+hy[i]<ul){
            ul=hx[i]+hy[i];
            uli=i;
        }

        if(i==0){
            ox[i]=1;
            oy[i]=1;
        }else{
            ox[i]=i+1;
            oy[i]=m-i;
        }
    }
    swap(ox[0], ox[uli]);
    swap(oy[0], oy[uli]);

    rep(trn, 300){
        if(rdy==1){
            int tag=1;
            rep(i, n){
                if(px[i]+py[i]<=m-2) tag*=2;
                if(m-1<=px[i]+py[i] && px[i]+py[i]<=m+1) tag=0;
            }
            ans=".";
            if((trn%2 && tag>1) || (trn+1)%2 && tag>2){
                rep(i, m-1) ans+="u";
                rdy=2;
            }else{
                rep(i, m-1) ans+=".";
            }
                
            cout<< ans <<endl;
        }else{
            int flag=1;
            ans="";
            rep(i, m){
                if(ox[i]<hx[i]){
                    ans+="U";
                    hx[i]--;
                    flag=0;
                }else if(ox[i]>hx[i]){
                    ans+="D";
                    hx[i]++;
                    flag=0;
                }else if(oy[i]<hy[i]){
                    ans+="L";
                    hy[i]--;
                    flag=0;
                }else if(oy[i]>hy[i]){
                    ans+="R";
                    hy[i]++;
                    flag=0;
                }else{
                    ans+=".";
                }
            }
            cout<< ans <<endl;
            if(flag && rdy==0) rdy=1;
        }
        cout<< flush;
        rep(i, n){
            cin>> s;
            rep(j, s.size()){
                if(s[j]=='U') px[i]--;
                if(s[j]=='D') px[i]++;
                if(s[j]=='L') py[i]--;
                if(s[j]=='R') py[i]++;
            }
        }
    }
 
	return 0;
}