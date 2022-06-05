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
int n, cone;
int dh[]={0, -1, 0, 1}, dw[]={-1, 0, 1, 0};
// int dh8[]={-2, -1, 0, 1, 2, 1, 0, -1}, dw8[]={0, 1, 2, 1, 0, -1, -2, -1}, dr8[]={8, 9, 1, 3, 2, 6, 4, 12};
char ds[]={'L', 'U', 'R', 'D'};
int bo[100], fbo[100], fpan[16], pan[16];
const double TIME_LIMIT = 2900.0, FIRST_LIMIT=1500.0;

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

int main(){
	std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

	int t, fh, fw, h, w, cnt=0, failgen, crt, flag, count, sz, cone;
	int dir[4], tre[4];
	char tmp;
	string ans, mans;

	cin>> n >> t;

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
		}
		//cout<< endl;
	}
	//cout<< "h=" << h << " w=" << w <<endl;
	
    //乱数の準備
    //int seed=100005;
	int seed=(unsigned)time(NULL);//todo
    mt19937 mt(seed%100000);
	cout<< "seed " << seed <<endl;//todo

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
					if(j!=i && j!=n-i-1 && k==i+1) k+=n-2*i-2; // type 2
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
					int idx;
					idx=mt()%nd.size();
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
			}
		}
		if(cd.size()!=1){
			//cout<< "check digit error " << cd.size() SP;
			continue;
		}
		cout<< "cnt: " << cnt <<endl;

		//if(failgen!=n*n) continue;
		//if(failgen!=n*n || cd.size()==1) continue;
		cout<< failgen <<endl;
		//rep(i, 16) cout<< pan[i] SP;
		//cout<< endl;

		rep(i, n){
			rep(j, n){
				//printf("%02d ", bo[i*n+j]);
				if(bo[i*n+j]>9) cout<< char('a'+bo[i*n+j]-10);
				else if(bo[i*n+j]==-1) cout<< 0;
				else cout<< bo[i*n+j];
				if(bo[i*n+j]!=-1) cd.insert(uf.root(i*n+j));
			}
			cout<< endl;
		}
		return 0;

		// rep(i, t){
		// 	//cout<< "turn: " << i <<endl;
		// 	int d[4];
		// 	rep(j, 4) d[j]=j;
		// 	d[(pdir+2)%4]=-1;
		// 	rep(j, 4){
		// 		if(h+dh[j]<0 || n<=h+dh[j] || w+dw[j]<0 || n<=w+dw[j]) d[j]=-1;
		// 	}
		// 	vector<int> nd;
		// 	rep(j, 4){
		// 		if(d[j]!=-1){
		// 			nd.push_back(d[j]);
		// 		}
		// 	}
		// 	//cout<< "nd=";
		// 	//PV(nd);
		// 	while(1){
		// 		// TODO、連続部分がすくないものを選ぶようにする
		// 		int idx=mt()%nd.size();
		// 		pdir=nd[idx];
		// 		swap(bo[h*n+w], bo[(h+dh[pdir])*n+w+dw[pdir]]);
		// 		int tmp;

		// 		tmp=score();

		// 		if(sco<=tmp || nd.size()==1){
		// 			h+=dh[pdir];
		// 			w+=dw[pdir];
		// 			sco=tmp;
		// 			//cout<< "score=" << sco <<endl;
		// 			ans+=ds[pdir];
		// 			if(msco<sco){
		// 				mans=ans;
		// 				msco=sco;
		// 			}
		// 			break;
		// 		}else{
		// 			swap(bo[h*n+w], bo[(h+dh[pdir])*n+w+dw[pdir]]);
		// 			nd.erase(nd.begin()+idx);
		// 		}
		// 	}
		// }
    }

	//cout<< cnt <<endl;
	cout<< mans << endl;
 
	return 0;
}