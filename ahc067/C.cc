// C.cc — d=10 入れ子スパイン版 + ランダム化構築の時間探索
// 洞察: ハノイ系列は2手に1手 switch0。0を遠方隔離すれば非0スイッチを co-locate しても
//       バッチ押下不可(間に必ず hub 往復)→ 往復回数 2^{d-1-n} の掛け算が保たれる。
// 構造: 最深deadend=anchor に top スイッチ。幹を下りつつ各分岐の側枝スタブに switch (sw) を
//       bit_{sw-1} 押下ゲートで封入、幹辺に bit_{sw-1} 未押下。switch0 は gate-free領域の遠方へ。
//       ゴールは bit_top 押下の half ゲート。壁=type(2*top+1):top bit は最後まで未押下=常時閉。
//       非木辺を壁で潰す→木のみ→迂回リーク無し&経路長増。calc_T(judge同等)で実測し最良保持。
// 時間探索: anchor/枝選択/スタブ経路/hub をランダム化し TIME_LIMIT まで反復、calc_T最良を出力。
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(int)(n);i++)
#define all(v) v.begin(),v.end()
#define ll long long

double TIME_LIMIT=1950.0;
struct Timer{chrono::system_clock::time_point st;Timer(){st=chrono::system_clock::now();}
    double ms(){return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now()-st).count()/1000.0;}};
Timer timer;
mt19937 mt(12345);

int N,M,K; vector<string> c;
struct Pos{int h,w; Pos():h(-1),w(-1){} Pos(int a,int b):h(a),w(b){} int index()const{return h*N+w;} };
Pos d4[]={{0,1},{-1,0},{0,-1},{1,0}};
struct Door{int d,i,j,g;}; struct Switch{int p,q,s;};
inline bool isopen(int i,int j){return 0<=i&&i<N&&0<=j&&j<N&&c[i][j]=='.';}
inline int deg(int i,int j){int d=0;for(Pos dp:d4)if(isopen(i+dp.h,j+dp.w))d++;return d;}
inline int edgeKey(int ah,int aw,int bh,int bw){int d,i,j;if(aw==bw){d=0;i=min(ah,bh);j=aw;}else{d=1;i=ah;j=min(aw,bw);}return d*N*N+i*N+j;}
inline Door mkDoor(int ah,int aw,int bh,int bw,int g){int d,i,j;if(aw==bw){d=0;i=min(ah,bh);j=aw;}else{d=1;i=ah;j=min(aw,bw);}return{d,i,j,g};}

Pos startP,goal; vector<vector<int>> depthG,parentG; vector<Pos> deadends;
vector<array<int,2>> nonTree;

ll calc_T(const vector<Door>&doors,const vector<Switch>&sw){
    vector<vector<int>> dh(N,vector<int>(N,-1)),dv(N,vector<int>(N,-1)),sg(N,vector<int>(N,-1));
    for(auto&d:doors){if(d.d==0)dh[d.i][d.j]=d.g;else dv[d.i][d.j]=d.g;}
    for(auto&s:sw)sg[s.p][s.q]=s.s;
    auto is_open=[&](int g,int mask){if(g==-1)return true;int k=g/2;return ((mask>>k)&1)==(g&1);};
    int SZ=1<<K; vector<int> dist((size_t)SZ*N*N,-1);
    auto idx=[&](int m,int i,int j){return ((size_t)m*N+i)*N+j;};
    deque<array<int,3>> que; dist[idx(0,0,0)]=0; que.push_back({0,0,0});
    while(!que.empty()){auto[mask,i,j]=que.front();que.pop_front();int d=dist[idx(mask,i,j)];
        if(i==N-1&&j==N-1)return d;
        for(auto[di,dj]:{array<int,2>{-1,0},{1,0},{0,-1},{0,1}}){int ni=i+di,nj=j+dj;
            if(!(0<=ni&&ni<N&&0<=nj&&nj<N))continue; if(c[ni][nj]=='#')continue;
            int g; if(di==1)g=dh[i][j];else if(di==-1)g=dh[ni][nj];else if(dj==1)g=dv[i][j];else g=dv[ni][nj];
            if(!is_open(g,mask))continue;
            if(dist[idx(mask,ni,nj)]==-1){dist[idx(mask,ni,nj)]=d+1;que.push_back({mask,ni,nj});}}
        int s=sg[i][j]; if(s!=-1){int nm=mask^(1<<s); if(dist[idx(nm,i,j)]==-1){dist[idx(nm,i,j)]=d+1;que.push_back({nm,i,j});}}
    } return 0;
}
ll scoreOf(ll T){return T>0?(ll)llround(1e6*log2((double)T/N)):1;}
void bfsOpen(Pos s,vector<int>&dist){dist.assign(N*N,-1);queue<int>q;dist[s.index()]=0;q.push(s.index());
    while(!q.empty()){int id=q.front();q.pop();int i=id/N,j=id%N;for(Pos dp:d4){int ni=i+dp.h,nj=j+dp.w;if(!isopen(ni,nj))continue;int nid=ni*N+nj;if(dist[nid]!=-1)continue;dist[nid]=dist[id]+1;q.push(nid);}}}

// anchor から入れ子スパイン構築。rnd=true で枝選択/スタブ経路をランダム化。
int buildSpine(Pos anchor, vector<Door>&doors, vector<Switch>&sws, vector<char>&claimed, int&topOut, bool rnd){
    doors.clear(); sws.clear(); claimed.assign(N*N,0);
    vector<int> trunk; int cur=anchor.index(); trunk.push_back(cur);
    while(parentG[cur/N][cur%N]>=0){cur=parentG[cur/N][cur%N];trunk.push_back(cur);}
    reverse(all(trunk));
    int L=trunk.size()-1; if(L<2) return 0;
    vector<char> onTrunk(N*N,0); for(int t:trunk) onTrunk[t]=1;
    int sw=1;
    auto sideChildren=[&](int v,int prev,int nxt,vector<int>&out){ out.clear(); int vi=v/N,vj=v%N;
        for(Pos dp:d4){int ni=vi+dp.h,nj=vj+dp.w; if(!isopen(ni,nj))continue; int nid=ni*N+nj;
            if(nid==prev||nid==nxt)continue; if(onTrunk[nid])continue; if(claimed[nid])continue;
            if(parentG[ni][nj]!=v)continue; if(nid==goal.index())continue; out.push_back(nid);} };
    auto deepStub=[&](int child, vector<int>&path)->int{ path.clear(); int cur=child; path.push_back(cur);
        while(true){ int ci=cur/N,cj=cur%N; vector<int> ch;
            for(Pos dp:d4){int ni=ci+dp.h,nj=cj+dp.w; if(!isopen(ni,nj))continue; int nid=ni*N+nj;
                if(parentG[ni][nj]!=cur)continue; if(claimed[nid]||onTrunk[nid]||nid==goal.index())continue; ch.push_back(nid);}
            if(ch.empty())break; int nx=ch[0]; int bd=depthG[ch[0]/N][ch[0]%N];
            for(int x:ch) if(depthG[x/N][x%N]>bd){bd=depthG[x/N][x%N];nx=x;}
            if(rnd && ch.size()>1 && (mt()%100)<30) nx=ch[mt()%ch.size()]; // たまに別枝
            path.push_back(nx); cur=nx; }
        return cur; };
    // 使える幹頂点を列挙
    vector<int> cand;
    for(int idx=1; idx<L; idx++){ vector<int> sc; sideChildren(trunk[idx],trunk[idx-1],trunk[idx+1],sc); if(!sc.empty()) cand.push_back(idx); }
    // 最深8本(rnd時は深め候補からランダム抽出)
    if((int)cand.size()>8){ sort(all(cand));
        if(rnd){ int take=min((int)cand.size(),12); vector<int> deep(cand.end()-take,cand.end());
                 shuffle(all(deep),mt); deep.resize(8); cand=deep; }
        else cand=vector<int>(cand.end()-8,cand.end()); }
    sort(all(cand));
    for(int idx:cand){ if(sw>8) break;
        int v=trunk[idx], prev=trunk[idx-1], nxt=trunk[idx+1]; if(claimed[v]) continue;
        vector<int> sc; sideChildren(v,prev,nxt,sc); if(sc.empty()) continue;
        int child = rnd ? sc[mt()%sc.size()] : sc[0];
        vector<int> path; int tip=deepStub(child,path);
        doors.push_back(mkDoor(v/N,v%N,child/N,child%N, 2*(sw-1)+1));
        doors.push_back(mkDoor(v/N,v%N,nxt/N,nxt%N, 2*(sw-1)));
        sws.push_back({tip/N,tip%N,sw});
        for(int cc:path) claimed[cc]=1; claimed[v]=1; sw++;
    }
    int top=sw; int ap=trunk[L-1];
    doors.push_back(mkDoor(anchor.h,anchor.w,ap/N,ap%N, 2*(top-1)+1));
    sws.push_back({anchor.h,anchor.w,top}); claimed[anchor.index()]=1; topOut=top; return top;
}

// 構成を完成(ゴールゲート/壁/hub)し calc_T を返す。doors/sws を最終形に。
ll assemble(Pos anchor, bool rnd, vector<Door>&alld, vector<Switch>&alls){
    vector<Door> doors; vector<Switch> sws; vector<char> claimed; int top=0;
    if(!buildSpine(anchor,doors,sws,claimed,top,rnd)||top<2) return -1;
    alld=doors; alls=sws;
    vector<char> usedEdge(2*N*N,0);
    for(auto&d:alld) usedEdge[edgeKey(d.i,d.j,d.d==0?d.i+1:d.i,d.d==0?d.j:d.j+1)]=1;
    int gt=2*top+1; // ゴール=top押下で開く(half)。top bit は最後まで未押下→壁にも流用
    for(Pos dp:d4){int ni=goal.h+dp.h,nj=goal.w+dp.w; if(!isopen(ni,nj))continue;
        int k=edgeKey(goal.h,goal.w,ni,nj); if(usedEdge[k])continue; usedEdge[k]=1;
        alld.push_back(mkDoor(goal.h,goal.w,ni,nj,gt));}
    // 壁: 非木辺を gt で封鎖(claim隣接優先、予算まで=経路長↑&迂回潰し)
    vector<array<int,2>> ord;
    rep(idx,nonTree.size()){auto&e=nonTree[idx];int u=e[0],v=e[1]; if(usedEdge[edgeKey(u/N,u%N,v/N,v%N)])continue;
        int pr=(claimed[u]||claimed[v])?0:1; ord.push_back({pr,(int)idx});}
    sort(all(ord));
    for(auto&o:ord){ if((int)alld.size()>=M) break; auto&e=nonTree[o[1]]; int u=e[0],v=e[1];
        int k=edgeKey(u/N,u%N,v/N,v%N); if(usedEdge[k])continue; usedEdge[k]=1;
        alld.push_back(mkDoor(u/N,u%N,v/N,v%N,gt)); }
    // hub(switch0): 扉ゼロで root 到達可能なセル & pocket群から重み付き最遠
    {
        vector<char> hasDoor(2*N*N,0);
        for(auto&d:alld){int ai=d.i,aj=d.j,bi=d.d==0?d.i+1:d.i,bj=d.d==0?d.j:d.j+1; hasDoor[edgeKey(ai,aj,bi,bj)]=1;}
        vector<char> r0(N*N,0); queue<int>q; r0[0]=1; q.push(0);
        while(!q.empty()){int id=q.front();q.pop();int i=id/N,j=id%N;
            for(Pos dp:d4){int ni=i+dp.h,nj=j+dp.w; if(!isopen(ni,nj))continue; int nid=ni*N+nj;
                if(r0[nid])continue; if(hasDoor[edgeKey(i,j,ni,nj)])continue; r0[nid]=1; q.push(nid);}}
        vector<int> tmp; vector<double> acc(N*N,0);
        for(auto&s:alls){ bfsOpen(Pos(s.p,s.q),tmp); double w=pow(2.0,top-s.s);
            rep(idx,N*N) if(tmp[idx]>=0) acc[idx]+=w*tmp[idx]; }
        // 候補収集
        vector<pair<double,int>> cands;
        rep(i,N)rep(j,N){int id=i*N+j; if(!isopen(i,j)||!r0[id]||claimed[id])continue; if(id==goal.index())continue;
            bool site=false; for(auto&s:alls)if(s.p==i&&s.q==j){site=true;break;} if(site)continue;
            cands.push_back({acc[id],id});}
        if(cands.empty()) return -1;
        sort(cands.rbegin(),cands.rend());
        int hub;
        if(rnd){ int top3=min((int)cands.size(),4); hub=cands[mt()%top3].second; }
        else hub=cands[0].second;
        alls.push_back({hub/N,hub%N,0});
    }
    if((int)alld.size()>M) return -1;
    return calc_T(alld,alls);
}

int main(){
    cin>>N>>M>>K; c.resize(N); rep(i,N)cin>>c[i];
    startP=Pos(0,0); goal=Pos(N-1,N-1);
    depthG.assign(N,vector<int>(N,-1)); parentG.assign(N,vector<int>(N,-1));
    {queue<int>q;depthG[0][0]=0;q.push(0);
     while(!q.empty()){int id=q.front();q.pop();int i=id/N,j=id%N;for(Pos dp:d4){int ni=i+dp.h,nj=j+dp.w;if(!isopen(ni,nj)||depthG[ni][nj]!=-1)continue;depthG[ni][nj]=depthG[i][j]+1;parentG[ni][nj]=id;q.push(ni*N+nj);}}}
    rep(i,N)rep(j,N){if(!isopen(i,j))continue;int u=i*N+j;
        if(isopen(i+1,j)){int v=(i+1)*N+j;if(parentG[i][j]!=v&&parentG[i+1][j]!=u)nonTree.push_back({u,v});}
        if(isopen(i,j+1)){int v=i*N+(j+1);if(parentG[i][j]!=v&&parentG[i][j+1]!=u)nonTree.push_back({u,v});}}
    rep(i,N)rep(j,N){if(c[i][j]!='.')continue;if((i==0&&j==0)||(i==N-1&&j==N-1))continue;if(deg(i,j)==1)deadends.push_back({i,j});}
    sort(all(deadends),[&](const Pos&a,const Pos&b){return depthG[a.h][a.w]>depthG[b.h][b.w];});

    ll bestT=-1; vector<Door> bestDoors; vector<Switch> bestSws; int iters=0,detAnchor=0;
    auto consider=[&](Pos anc,bool rnd){ vector<Door> dd; vector<Switch> ss; ll T=assemble(anc,rnd,dd,ss);
        iters++; if(T>bestT){bestT=T;bestDoors=dd;bestSws=ss;} };
    // 貪欲(床): 最深 anchor を決定論で
    int detN=min((int)deadends.size(),14);
    rep(t,detN) consider(deadends[t],false);
    detAnchor=detN;
    // 時間探索: 深め anchor をランダム化構築
    int pool=min((int)deadends.size(),24);
    while(timer.ms()<TIME_LIMIT && pool>0){
        Pos anc=deadends[mt()%pool];
        consider(anc,true);
    }

    if(bestT<0){ cout<<0<<"\n"<<0<<"\n"; cerr<<"FAILED\n"; return 0; }
    cerr<<"iters="<<iters<<" doors="<<bestDoors.size()<<" T="<<bestT<<" score="<<scoreOf(bestT)<<"\n";
    cout<<bestDoors.size()<<"\n"; for(auto&d:bestDoors)cout<<d.d<<" "<<d.i<<" "<<d.j<<" "<<d.g<<"\n";
    cout<<bestSws.size()<<"\n"; for(auto&s:bestSws)cout<<s.p<<" "<<s.q<<" "<<s.s<<"\n";
    return 0;
}
