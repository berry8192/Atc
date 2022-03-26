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

int si, sj, ti, tj;
int dis[20][20], dis2[20][20], oma[20][20];
vector<string> h(20), v(19);
queue<int> qh, qw;
vector<char> ad;
vector<int> al;

void dfso(int y, int x){
	//移動してきた時の処理
    //cout<< y SP << x SP << dpt <<endl;

	//移動する処理
	// U
    int mv=0;
    while(0<y-mv && v[y-mv-1][x]=='0'){
        mv++;
        oma[y-mv][x]=1;
    }

	// D
    mv=0;
    while(y+mv<19 && v[y+mv][x]=='0'){
        mv++;
        oma[y+mv][x]=1;
    }

	// L
    mv=0;
    while(0<x-mv && h[y][x-mv-1]=='0'){
        mv++;
        oma[y][x-mv]=1;
    }

	// R
    mv=0;
    while(x+mv<19 && h[y][x+mv]=='0'){
        mv++;
        oma[y][x+mv]=1;
    }
}

void dfsr(int y, int x, int dpt){
	//移動してきた時の処理
    //cout<< y SP << x SP << dpt <<endl;
    if(dpt==0) return;

	//移動する処理
	// U
    int mv=0;
    while(0<y-mv && v[y-mv-1][x]=='0'){
        mv++;
        if(dis[y-mv][x]==dpt-1){
            ad.push_back('D');
            al.push_back(mv);
            if(dpt) dfsr(y-mv, x, dpt-1);
            return;
        }
    }

	// D
    mv=0;
    while(y+mv<19 && v[y+mv][x]=='0'){
        mv++;
        if(dis[y+mv][x]==dpt-1){
            ad.push_back('U');
            al.push_back(mv);
            if(dpt) dfsr(y+mv, x, dpt-1);
            return;
        }
    }

	// L
    mv=0;
    while(0<x-mv && h[y][x-mv-1]=='0'){
        mv++;
        if(dis[y][x-mv]==dpt-1){
            ad.push_back('R');
            al.push_back(mv);
            if(dpt) dfsr(y, x-mv, dpt-1);
            return;
        }
    }

	// R
    mv=0;
    while(x+mv<19 && h[y][x+mv]=='0'){
        mv++;
        if(dis[y][x+mv]==dpt-1){
            ad.push_back('L');
            al.push_back(mv);
            if(dpt) dfsr(y, x+mv, dpt-1);
            return;
        }
    }
}

void bfs(int y, int x){
	//移動してきた時の処理
    //cout<< y SP << x <<endl;

	//移動する処理
	// U
    int mv=0;
    while(0<y-mv && v[y-mv-1][x]=='0'){
        mv++;
        if(y-mv==ti && x==tj){
            if(dis[y][x]+1<dis[y-mv][x]){
                dis[y-mv][x]=dis[y][x]+1;
                mv=0;
                break;
            }
        }
    }
    //cout<< "  U " << y-mv SP << x <<endl;
    if(mv && dis[y][x]+1<dis[y-mv][x]){
        qh.push(y-mv);
        qw.push(x);
        dis[y-mv][x]=dis[y][x]+1;
    }

	// D
    mv=0;
    while(y+mv<19 && v[y+mv][x]=='0'){
        mv++;
        if(y+mv==ti && x==tj){
            if(dis[y][x]+1<dis[y+mv][x]){
                dis[y+mv][x]=dis[y][x]+1;
                mv=0;
                break;
            }
        }
    }
    //cout<< "  D " << y+mv SP << x <<endl;
    if(mv && dis[y][x]+1<dis[y+mv][x]){
        qh.push(y+mv);
        qw.push(x);
        dis[y+mv][x]=dis[y][x]+1;
    }

	// L
    mv=0;
    while(0<x-mv && h[y][x-mv-1]=='0'){
        mv++;
        if(y==ti && x-mv==tj){
            if(dis[y][x]+1<dis[y][x-mv]){
                dis[y][x-mv]=dis[y][x]+1;
                mv=0;
                break;
            }
        }
    }
    //cout<< "  L " << y SP << x-mv <<endl;
    if(mv && dis[y][x]+1<dis[y][x-mv]){
        qh.push(y);
        qw.push(x-mv);
        dis[y][x-mv]=dis[y][x]+1;
    }

	// R
    mv=0;
    while(x+mv<19 && h[y][x+mv]=='0'){
        mv++;
        if(y==ti && x+mv==tj){
            if(dis[y][x]+1<dis[y][x+mv]){
                dis[y][x+mv]=dis[y][x]+1;
                mv=0;
                break;
            }
        }
    }
    //cout<< "  R " << y SP << x+mv <<endl;
    if(mv && dis[y][x]+1<dis[y][x+mv]){
        qh.push(y);
        qw.push(x+mv);
        dis[y][x+mv]=dis[y][x]+1;
    }
}

int main(){

    string ans="";
    double p;

    cin>> si >> sj >> ti >> tj >> p;

    rep(i, 20){
        cin>> h[i];
    }
    rep(i, 19){
        cin>> v[i];
    }
    rep(i, 20){
        rep(j, 20){
            dis[i][j]=999;
            dis2[i][j]=999;
        }
    }
    rep(i, 20){
        rep(j, 20) oma[i][j]=0;
    }
    
	qh.push(si);
	qw.push(sj);
	dis[si][sj]=0;
  	while (!qh.empty()) {
    	bfs(qh.front(), qw.front());
    	qh.pop();
    	qw.pop();
  	}

    // rep(i, 20){
	// 	rep(j, 20){
	// 		if(dis[i][j]!=999) cout << dis[i][j] SP;
    //         else cout<< -1 SP;
	// 	}
	// 	cout << endl;
	// }

    if(dis[ti][tj]!=999){
        dfsr(ti, tj, dis[ti][tj]);
        reverse(all(ad));
        reverse(all(al));

        vector<int> len;
        int su=0;
        rep(i, al.size()){
            len.push_back(al[i]*(2+int(p*9.0))/2+6);
            su+=len[i];
        }
        if(200<su){
            //cout<< "edit" <<endl;
            rep(i, len.size()){
                len[i]=len[i]*200/su;
            }
        }

        rep(i, ad.size()){
            //cout<< ad[i] SP << al[i] <<endl;
            rep(j, len[i]){
                if(ans.size()==200) break;
                ans+=ad[i];
            }
        }
        char tmp=ans[ans.size()-1];
        while(ans.size()<200) ans+=tmp;
    }else{
        ans="DRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDR";
    }

    int flag=1;
    rep(i, 200){
        if(ans[i]!='U' && ans[i]!='D' && ans[i]!='L'&& ans[i]!='R'){
            flag=0;
        }
    }

    if(flag) cout<< ans <<endl;
    else cout<<"DRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDRDR"<<endl;

	return 0;
}