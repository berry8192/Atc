#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
int n, cone, mi, pred=-1, predp=-1, srt;
int dh[]={0, -1, 0, 1}, dw[]={-1, 0, 1, 0};
int bo[100], fbo[100], fpan[16], pan[16], initial[100], final[100], rph[100], rpw[100];
// vector<vector<int>> prm={
// 	{5, 6, 4, 3, 2, 1, 25, 31, 19, 13, 7, 11, 12, 10, 9, 8, 26, 32, 20, 14, 17, 18, 16, 15, 27, 33, 21, 23, 24, 22}
// };
// vector<vector<int>> prmh={
// 	{0, 1, 0, 0, 0, 0, 5, }
// };
// vector<vector<int>> prmw={
// 	{5, 5, 4, 3, 2, 1, 0}
// };
string ans, mans, ds="LURD";
const double TIME_LIMIT = 2800.0, FIRST_LIMIT=2700.0;
	
//乱数の準備
//int seed=100005;
//int seed=(unsigned)time(NULL);//todo
int seed=101;
mt19937 mt(seed%100000);

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv, int xx) {
	rep(i, xx){
		rep(j, xx){
			printf("%02d ", pvv[i*n+j]);
		}
		cout << endl;
	}
}

struct UnionFind {
    vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2
	vector<int> siz; // siz[i]:iの属する木から伸びている辺の数

    UnionFind(int N) : par(N) { //最初は全てが根であるとして初期化
        for(int i = 0; i < N; i++) par[i] = i;
		siz.resize(par.size()); //最初は全てサイズ0
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

	int tsize(int x){ // siz[x]の木の根を見に行き、サイズを返す
		if (par[x] == x) return siz[x];
		return tsize(par[x]);
	}

    void unite(int x, int y, int ade) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        //if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
		if(siz[rx]>siz[ry]) swap(rx, ry);
        par[rx] = ry; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[ry]=ade; //根で管理
    }
};

struct rpos{
	int h;
	int w;

	bool operator<(const rpos &in) const{
		return h+w!=in.h+in.w ? h+w>in.h+in.w : h>in.h;
	};
};

bool initial_invalid(){
	bool flag=false;
	if(rph[0]<0 || n<=rph[0] || rpw[0]<0 || n<=rpw[0]){
		cout<< "invalid blank" <<endl;
		cout<< "  (rph) " << rph[0] <<endl;
		cout<< "  (rpw) " << rpw[0] <<endl;
		flag=true;
	}
	rep(i, n*n){
		if(initial[rph[i]*n+rpw[i]]!=i && initial[rph[i]*n+rpw[i]]>=0){
			cout<< "invalid position " << i <<endl;
			cout<< "  rph[i]=" << rph[i] <<endl;
			cout<< "  rpw[i]=" << rpw[i] <<endl;
			cout<< "  initial[rph[i]*n+rpw[i]]=" << initial[rph[i]*n+rpw[i]] <<endl;
			flag=true;
		}
	}
	return flag;
}

void mov(int num, int th, int tw){
	//cout<< "mov " << num <<endl;
	//return;
	initial[rph[num]*n+rpw[num]]=-1;
	int h, w, idx, idxb, brh, brw, dist, allow_side_step;
	int dd[4];
	while(rph[num]!=th || rpw[num]!=tw){
		// 進む方向を決めるフェイズ

		rep(i, 4){
			dd[i]=0;
			if((i+2)%4==predp) continue;
			dist=dh[i]*(th-rph[num])+dw[i]*(tw-rpw[num]);
			if(dist<=0) continue; // このif文あんまり自信ない
			//if(rph[num]+dh[i]<0 || rph[num]+dh[i]>=n || rpw[num]+dw[i]<0 || rpw[num]+dw[i]>=n) continue;
			if(initial[(rph[num]+dh[i])*n+rpw[num]+dw[i]]<0) continue;
			dd[i]=dist;
		}
		idx=0;
		rep3(i, 4, 1){
			if(dd[idx]<dd[i]) idx=i;
		}
		//if(dd[idx]==0) cout<< "dd empty 1" <<endl;

		// 空白を移動する
		brh=rph[num]+dh[idx];
		brw=rpw[num]+dw[idx];
		while(rph[0]!=brh || rpw[0]!=brw){
			allow_side_step=0;
			if(rph[0]==brh && initial[rph[0]*n+rpw[0]+(brw-rpw[0])/abs(brw-rpw[0])]<0) allow_side_step=1;
			if(rpw[0]==brw && initial[(rph[0]+((brh-rph[0])/abs(brh-rph[0])))*n+rpw[0]]<0) allow_side_step=1;
			rep(i, 4){
				dd[i]=-10;
				if((i+2)%4==pred) continue;
				dist=dh[i]*(brh-rph[0])+dw[i]*(brw-rpw[0]);
				if(dist>0) dist=1;
				//if(rph[num]+dh[i]<0 || rph[num]+dh[i]>=n || rpw[num]+dw[i]<0 || rpw[num]+dw[i]>=n) continue;
				if(rph[0]+dh[i]<0 || rph[0]+dh[i]>=n || rpw[0]+dw[i]<0 || rpw[0]+dw[i]>=n){
					dd[i]=-10;
					continue;
				}
				if(initial[(rph[0]+dh[i])*n+rpw[0]+dw[i]]<0){
					dd[i]=-10;
					continue; // 道を完全にふさがれることがあるので
				}
				if(dist<=0){
					if(dist<0 || !allow_side_step){
						dd[i]=dist;
						continue;
					}else{
						//cout<< "allow_side_step" <<endl;
						dist=10;
					}
				}
				dd[i]=dist;
			}
			idxb=0;
			rep3(i, 4, 1){
				if(dd[idxb]<dd[i]) idxb=i;
			}
			vector<int> ddd;
			rep(i, 4){
				if(dd[idx]==dd[i]) ddd.push_back(i);
			}
			int idx=ddd[mt()%ddd.size()];
			//if(dd[idxb]==0) cout<< "dd empty 2" <<endl;

			// 入れ替える
			int ch=rph[0];
			int cw=rpw[0];
			swap(rph[0], rph[initial[(ch+dh[idxb])*n+cw+dw[idxb]]]);
			swap(rpw[0], rpw[initial[(ch+dh[idxb])*n+cw+dw[idxb]]]);
			swap(initial[ch*n+cw], initial[(ch+dh[idxb])*n+cw+dw[idxb]]);
			//cout<< "blank move " << ds[idxb] <<endl;
			//PVV(initial, n);
			// cout<< " 0 " << rph[0] SP << rpw[0] <<endl;
			// cout<< " " << initial[(rph[0]+dh[idxb])*n+rpw[0]+dw[idxb]] SP << rph[initial[(rph[0]+dh[idxb])*n+rpw[0]+dw[idxb]]] SP << rpw[initial[(rph[0]+dh[idxb])*n+rpw[0]+dw[idxb]]] <<endl;
			// if(initial_invalid()){
			// 	cout<< ans <<endl;
			// 	exit(0);
			// }
			ans+=ds[idxb];
			pred=idxb;
			if(ans.size()>=mi){
				//cout<< "move limit " << ans.size() <<endl;
				return;
			}
		}
		// 本命の移動
		swap(initial[rph[0]*n+rpw[0]], initial[rph[num]*n+rpw[num]]);
		swap(rph[0], rph[num]);
		swap(rpw[0], rpw[num]);
		//cout<< "panel move " << ds[(idx+2)%4] <<endl;
		//PVV(initial, n);
		// cout<< " 0 " << rph[0] SP << rpw[0] <<endl;
		// cout<< " " << num SP << rph[num] SP << rpw[num] <<endl;
		// if(initial_invalid()){
		// 	cout<< ans <<endl;
		// 	exit(0);
		// }
		ans+=ds[(idx+2)%4];
		pred=(idx+2)%4;
		predp=idx;
		if(ans.size()>=mi){
			//cout<< "move limit " << ans.size() <<endl;
			return;
		}
	}
	initial[rph[num]*n+rpw[num]]=-2;
	predp=-1;
}

void mov0(int th, int tw){
	//cout<< "mov0 " <<endl;
	//return;
	int h, w, idx, dist;
	int dd[4];
	while(rph[0]!=th || rpw[0]!=tw){
		// 進む方向を決めるフェイズ

		rep(i, 4){
			dd[i]=0;
			if((i+2)%4==predp) continue;
			dist=dh[i]*(th-rph[0])+dw[i]*(tw-rpw[0]);
			if(dist<=0) continue; // このif文あんまり自信ない
			//if(rph[num]+dh[i]<0 || rph[num]+dh[i]>=n || rpw[num]+dw[i]<0 || rpw[num]+dw[i]>=n) continue;
			if(initial[(rph[0]+dh[i])*n+rpw[0]+dw[i]]<0 && (!srt && initial[(rph[0]+dh[i])*n+rpw[0]+dw[i]]>-3)) continue;
			dd[i]=dist;
		}
		idx=0;
		rep3(i, 4, 1){
			if(dd[idx]<dd[i]) idx=i;
		}
		//if(dd[idx]==0) cout<< "dd empty 1" <<endl;

		// 本命の移動
		if(srt){
			initial[(rph[0]+dh[idx])*n+rpw[0]+dw[idx]]--;
			swap(initial[rph[0]*n+rpw[0]], initial[(rph[0]+dh[idx])*n+rpw[0]+dw[idx]]);
			rph[0]+=dh[idx];
			rpw[0]+=dw[idx];
		}else{
			int ch=rph[0];
			int cw=rpw[0];
			int cn=initial[(ch+dh[idx])*n+cw+dw[idx]];
			swap(initial[ch*n+cw], initial[rph[cn]*n+rpw[cn]]);
			swap(rph[0], rph[cn]);
			swap(rpw[0], rpw[cn]);
		}

		//cout<< "0 move " << ds[idx] <<endl;
		//PVV(initial, n);
		// cout<< " 0 " << rph[0] SP << rpw[0] <<endl;
		// cout<< " " << num SP << rph[num] SP << rpw[num] <<endl;
		// if(initial_invalid()){
		// 	cout<< ans <<endl;
		// 	exit(0);
		// }
		ans+=ds[idx];
		if(ans.size()>=mi){
			//cout<< "move limit " << ans.size() <<endl;
			return;
		}
	}
}

int main(){
	std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

	int t, fh, fw, cnt=0, failgen, crt, flag, count, sz, cone;
	int dir[4], tre[4];
	char tmp;

	cin>> n >> t;
	mi=t;
	//mi=50;

	rep(i, 16) fpan[i]=0;

	rep(i, n){
		rep(j, n){
			cin>> tmp;
			if('a'<=tmp) tmp=tmp-39;
			tmp=tmp-48;
			//cout<< int(tmp) SP;
			fbo[i*n+j]=int(tmp);
			fpan[int(tmp)]++;
			if(int(tmp)==0){
				fh=i;
				fw=j;
			}
			final[i*n+j]=(i*n+j+1)%(n*n);
		}
		//cout<< endl;
	}
	//cout<< "h=" << h << " w=" << w <<endl;

	while (1) {
		cnt++;
		// if(cnt%100000==0){
		// 	cout<< "rep:" << cnt << " in ";//todo
		// 	cout<< chrono::duration_cast<chrono::milliseconds>(current - start).count() <<endl;
		// }
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > FIRST_LIMIT) {
            //break;//todo
        }

		rep(i, n*n) bo[i]=-1;
		rep(i, 16){
			pan[i]=fpan[i];
			//cout<< pan[i] <<endl;
		}
		failgen=0;
		UnionFind uf(n*n);
		flag=1;
		count=0;

		// int count=0;
		rep(i, n){ // type3
		//rep(i, (n+1)/2){ // type2
		//rep(i, 1){ // type1
			rep3(j, n, i){ // type3
			//rep3(j, n-i, i){ // type2
			//rep(j, n){ // type1
				rep3(k, n, i){ // type3
				//rep3(k, n-i, i){ // type2
				//rep(k, n){ // type1
					if(j!=i && k!=i) break; // type 3
					//if(j!=i && j!=n-i-1 && k==i+1) k+=n-2*i-2; // type 2
					rep(l, 4){
						dir[l]=0;
						tre[l]=-1;
					}
					sz=0;
					cone=0;

					count++;
					// bo[j*n+k]=count;
					if(k!=0 && bo[j*n+k-1]!=-1){
						if((bo[j*n+k-1]>>2)%2){
							dir[0]=2;
							tre[0]=uf.root(j*n+k-1);
							sz+=uf.tsize(tre[0])-1;
							cone++;
						}
						else dir[0]=1;
					}
					if(j!=0 && bo[(j-1)*n+k]!=-1){
						if((bo[(j-1)*n+k]>>3)%2){
							dir[1]=2;
							tre[1]=uf.root((j-1)*n+k);
							sz+=uf.tsize(tre[1])-1;
							cone++;
						}
						else dir[1]=1;
					}
					if(k!=n-1 && bo[j*n+k+1]!=-1){
						if(bo[j*n+k+1]%2){
							dir[2]=2;
							tre[2]=uf.root(j*n+k+1);
							sz+=uf.tsize(tre[2])-1;
							cone++;
						}
						else dir[2]=1;
					}
					if(j!=n-1 && bo[(j+1)*n+k]!=-1){
						if((bo[(j+1)*n+k]>>1)%2){
							dir[3]=2;
							tre[3]=uf.root((j+1)*n+k);
							sz+=uf.tsize(tre[3])-1;
							cone++;
						}
						else dir[3]=1;
					}
					if(k==0) dir[0]=1;
					if(j==0) dir[1]=1;
					if(k==n-1) dir[2]=1;
					if(j==n-1) dir[3]=1;
					// rep(l, 4) cout<< dir[l] SP;
					// cout<< endl;

					rep(l, 4){
						// 閉路ができないようにする
						//if(j+dh[l]<0 || j+dh[l]>=n || k+dw[l]<0 || k+dw[l]>=n) continue;
						if(dir[l]==2) continue;
						if(j+dh[l]<0 || j+dh[l]>=n || k+dw[l]<0 || k+dw[l]>=n) continue;
						if(bo[(j+dh[l])*n+k+dw[l]]!=-1) continue;
						rep(m, 4){
							if(j+dh[l]+dh[m]<0 || j+dh[l]+dh[m]>=n || k+dw[l]+dw[m]<0 || k+dw[l]+dw[m]>=n) continue;
							if(bo[(j+dh[l]+dh[m])*n+k+dw[l]+dw[m]]==-1 || (bo[(j+dh[l]+dh[m])*n+k+dw[l]+dw[m]]>>((m+2)%4))%2==0) continue;
							crt=uf.root((j+dh[l]+dh[m])*n+k+dw[l]+dw[m]);
							rep(o, 4){
								if(crt==tre[o]){
									//cout<< "cycle " << l <<endl;
									dir[l]=1;
									m=4;
									break;
								}
							}
						}
					}

					if(/*(count==n*n-1 && pan[0]) ||*/ count==n*n) flag=0;

					vector<int> nd;
					rep3(l, 16, 1){
						// パネルの在庫確認
						if(pan[l]==0) continue;
						// 森になってしまうパターンを弾く
						if(sz==0 && __builtin_popcount(l)<=cone /*&& l*/ && flag) continue;
						// 接続がうまくいかないパターンを排除
						if(l%2+dir[0]==2) continue;
						if((l>>1)%2+dir[1]==2) continue;
						if((l>>2)%2+dir[2]==2) continue;
						if((l>>3)%2+dir[3]==2) continue;
						// 抽選にいれてあげる
						rep(m, pan[l]) nd.push_back(l);
					}
					//PV(nd);
					if(nd.empty()){
						// cout<< "nd empty " << j SP << k <<endl;
						failgen=count;
						j=n;
						i=n;
						break;
					}
					int idx=mt()%nd.size();
					//if(count==1) idx=0;
					// cout<< j SP << k SP << nd[idx] <<endl;
					pan[nd[idx]]--;
					bo[j*n+k]=nd[idx];
					// uniteする
					int nsz=sz+__builtin_popcount(nd[idx])-cone;
					rep(l, 4){
						if((nd[idx]>>l)%2==0) continue;
						uf.unite(j*n+k, (j+dh[l])*n+k+dw[l], nsz);
					}
					uf.siz[uf.root(j*n+k)]=nsz;
				}
			}
		}

		if(failgen!=n*n) continue;
		set<int> cd;
		rep(i, n){
			rep(j, n){
				if(bo[i*n+j]!=-1) cd.insert(uf.root(i*n+j));
				else bo[i*n+j]=0; // 超行儀悪いけど許して
			}
		}
		if(cd.size()!=1){
			//cout<< "check digit error " << cd.size() SP;
			continue;
		}
		//cout<< "cnt: " << cnt <<endl;

		//if(failgen!=n*n) continue;
		//if(failgen!=n*n || cd.size()==1) continue;
		//cout<< failgen <<endl;
		//rep(i, 16) cout<< pan[i] SP;
		//cout<< endl;

		// rep(i, n){
		// 	rep(j, n){
		// 		//printf("%02d ", bo[i*n+j]);
		// 		if(bo[i*n+j]>9) cout<< char('a'+bo[i*n+j]-10);
		// 		else cout<< bo[i*n+j];
		// 	}
		// 	cout<< endl;
		// }

		// puzzle solver
		// initial=fbo
		// final=bo
		// なんとなく近いやつを結びつける
		vector<vector<rpos>> bopos(16);
		rpos rtmp;
		rep(i, n){
			rtmp.h=i;
			rep(j, n){
				rtmp.w=j;
				bopos[bo[i*n+j]].push_back(rtmp);
			}
		}
		rep3(i, 16, 1) sort(all(bopos[i]));
		rep(i, n){
			rep(j, n){
				rtmp=*bopos[fbo[i*n+j]].rbegin();
				bopos[fbo[i*n+j]].pop_back();
				initial[i*n+j]=(rtmp.h*n+rtmp.w+1)%(n*n);
				rph[initial[i*n+j]]=i;
				rpw[initial[i*n+j]]=j;
				//initial[i][j]=(i*n+j+1)%(n*n);
			}
		}
		//swap(initial[n-1][n-1], initial[n-1][n-2]);

		//PVV(initial, n);

		//int eee=1;
		rep(i, n){
			mov(i*n+n-1, i, n-1);
			for(int j=n-1;j>=i;j--){
				if(ans.size()>=mi){
					j=n;
					i=n+1;
					break;
				}
				if(j==n-1) mov(i*n+j+1, i+1, j);
				else mov(i*n+j+1, i, j+1);
			}
			//cout<< "sort 1" <<endl;
			mov0(i, i);
			srt=1;
			//cout<< "sort 2" <<endl;
			mov0(i, n-1);
			//cout<< "sort 3" <<endl;
			mov0(i+1, n-1);
			srt=0;
			//cout<< "size " << ans.size() <<endl;
			//PVV(initial, n);
			if(i==n-3){
				i=n+1;
				break;
			}
			
			mov(n*(n-2)+i+1, n-1, i);
			for(int j=n-1;j>=i+1;j--){
				if(ans.size()>=mi){
					j=n;
					i=n+1;
					break;
				}
				if(j==n-1) mov(j*n+i+1, j, i+1);
				else mov(j*n+i+1, j+1, i);
			}
			//cout<< "sort 1" <<endl;
			mov0(i+1, i);
			srt=1;
			//cout<< "??????????????" <<endl;
			//PVV(initial, n);
			//cout<< "sort 2" <<endl;
			mov0(n-1, i);
			//cout<< "sort 3" <<endl;
			mov0(n-1, i+1);
			srt=0;
			//cout<< "size " << ans.size() <<endl;
			//PVV(initial, n);
		}
		mov(n*n-(n+2), n-2, n-3);
		mov0(n-1, n-3);
		int fin=0;
		if(rph[n*n-2]==n-2){
			if(rpw[n*n-2]==n-2){
				ans+="RU";
			}else{
				ans+="RR";
				fin=1;
			}
		}else if(rph[n*n-2]==n-1){
			if(rpw[n*n-2]==n-2){
				ans+="RURDLU";
			}else{
				ans+="RRUL";
			}
		}
		if(!fin){
			ans+="LDRRULDLURDLURRDLLURDR";;
		}

		cout<< ans <<endl;
		return 0;

		rep(i, n){
			rep(j, n){
				printf("%02d ", initial[i*n+j]);
			}
			cout<< endl;
		}
		cout<< "------------------------------------" <<endl;
		rep(i, n){
			rep(j, n){
				printf("%02d ", final[i*n+j]);
			}
			cout<< endl;
		}

		return 0;
    }

	//cout<< cnt <<endl;
 
	return 0;
}