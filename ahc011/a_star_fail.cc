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

struct rpos{
	int h;
	int w;

	bool operator<(const rpos &in) const{
		return h+w!=in.h+in.w ? h+w>in.h+in.w : h>in.h;
	};
};

// slide puzzle solver
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int moves[2000][10][10];
int initial[10][10];
int final[10][10];
int mv;

struct Node{
    Node* par;
    int board[10][10];
    int x_0;
    int y_0;
    int level;
    int cost;
};

Node* newNode(int board[10][10] , int x_0 , int y_0 , int nx , int ny, int level , Node* par){

    Node* temp = new Node;
    temp->par = par;

    memcpy(temp->board , board , sizeof temp->board );
    swap(temp->board[x_0][y_0] , temp->board[nx][ny]);

    temp->level = level;
    temp->x_0 = nx;
    temp->y_0 = ny;
    temp->cost = 1e9;

    return temp;

}

int heuristic_manhattan(int b[10][10]){

    int dist=0;
    map<int,pair<int,int>> val;

    int x=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            val[x] = make_pair(i,j);
            x++;
        }
    }
    val[0] = make_pair(n-1,n-1);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            dist += abs(i-val[b[i][j]].first) + abs(j-val[b[i][j]].second);
        }
    }

    return dist;

}

int heuristic_misplaced(int b[10][10]){
    int cost=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(b[i][j] && b[i][j]!=final[i][j]){
                cost++;
            }
        }
    }
    return cost;
}

void print(int a[10][10]){  

    for(int i=0;i<n;i++){
        cout << "[ " ;
        for(int j=0;j<n;j++){
            cout << a[i][j] << " ";
        }
        cout << "]\n";
    }
cout << "\n\n";
    
}

void print_moves(Node* cur){

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            moves[mv][i][j] = cur->board[i][j];
        }
    }
    mv++;

    int f=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(cur->board[i][j]!= initial[i][j])
                f=0;
            }
        }
        if(f)
            return;

    
    print_moves(cur->par);
}

bool check(int x , int y){
    if(x>=0 && x<n && y>=0 && y<n){
        return 1;
    }
    return 0;
}

struct prioritize
{
    bool operator()(const Node* p1, const Node* p2) const
    {
        return (p1->cost + p1->level) > (p2->cost + p2->level);
    }
};

void A_Star(Node* src){

    priority_queue<Node* , std::vector<Node*> , prioritize> pq;

    Node* root = newNode(src->board , src->x_0 , src->y_0 , src->x_0 , src->y_0 , src->level , src->par);

    root->cost = heuristic_manhattan(root->board);
    pq.push(root);

    map<vector<int>,int> vis;
	//int as_cnt=0;
    while(!pq.empty()){
		// as_cnt++;
		// cout<< as_cnt SP << pq.size() <<endl;

        Node* cur = pq.top();
        pq.pop();
        int x = cur->x_0;
        int y = cur->y_0;

        vector<int> ans;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                ans.push_back(cur->board[i][j]);
            }
        }

        vis[ans]=1;
       if(cur->cost == 0){

            cout << "SOLUTION STATE using A* star: " ;
            cout << " No. of moves ";
            cout << cur->level << "\n";
            mv=0;
            print_moves(cur);
            int x=0;

            for(int i=mv-1;i>=0;i--){
                cout << "Move : " << x++ << "\n";
                print(moves[i]);
            }

            return;
        }

        for(int k=0;k<4;k++){
            int nx = x+dx[k];
            int ny = y+dy[k];

            if(check(nx,ny)){

                Node* temp = newNode(cur->board , cur->x_0 , cur->y_0 , nx , ny , cur->level+1 , cur);
                temp->cost = heuristic_manhattan(temp->board);

                vector<int> tmp;
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        tmp.push_back(temp->board[i][j]);
                    }
                }

                if(!vis[tmp]){
                    
                    pq.push(temp);
                }
            }

        }

    }
}

int merge(int a[99] , int start,int mid,int end){
    int temp[n*n-1];
    int pos = start;
    int i = start , j = mid+1;

    int invCount=0;

    while(i<=mid && j <= end){
        if(a[i]>a[j]){
            temp[pos++] = a[j++];
            invCount += (mid-i+1);
        }
        else{
            temp[pos++] = a[i++];
        }
    }

    while(i<=mid){
        temp[pos++]= a[i++];
    }
    while(j<=end){
        temp[pos++]= a[j++];
    }

    for(int i=start;i<=end;i++){
        a[i] = temp[i];
    }

    return invCount;    

}

int mergesort(int start, int end , int a[99]){
    if(start>=end){
        return 0;
    }

    int mid = start + (end-start)/2;
    int invCount = 0;

    invCount += mergesort(start,mid,a);
    invCount += mergesort(mid+1,end,a);

    invCount += merge(a,start,mid,end);

    return invCount;

}

//Finds row position of blank cell from bottom
int find_blankRow_pos(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(initial[i][j]==0){
                return n-i;  
            }
        }
    }

    return -1;
}

// Checks if the current instance of sliding puzzle is solvable or not. 
bool isSolvable(){
    int a[n*n];
    int p=0;
    int zero;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(initial[i][j]==0)
                continue;
            a[p++] = initial[i][j];
        }
    }
    //int inv_cnt=0;
    int x = n*n-1;
    int inv_cnt = mergesort(0,x-1,a);     // Returns the inversion count of the array in O(n^2log(n)) time complexity
    int pos = find_blankRow_pos();

    // For a grid of odd width , number of inversions should be even for the current instance of puzzle to be solvable
    if(n&1){
        if(inv_cnt&1){
            return 0;
        }
        else{
               return 1;
        }
    }
// For a grid of even width, the following is invariant: (#inversions even) == (blank on odd row from bottom). 
    else{
        int flag =pos+inv_cnt;
        if(flag&1){
               return 1;
        }
        else{
               return 0;
        }
    }
}

int main(){
	std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

	int t, fh, fw, cnt=0, failgen, crt, flag, count, sz, cone;
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
				else bo[i*n+j]=0; // 超行儀悪いけど許して
			}
		}
		if(cd.size()!=1){
			cout<< "check digit error " << cd.size() SP;
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
				else cout<< bo[i*n+j];
			}
			cout<< endl;
		}

		// puzzle solver
		// initial=fbo
		// final=bo
		// 一番マンハッタン距離が近いやつを結びつける
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
				initial[i][j]=(rtmp.h*n+rtmp.w+1)%(n*n);
				final[i][j]=(i*n+j+1)%(n*n);
				//initial[i][j]=(i*n+j+1)%(n*n);
			}
		}
		//swap(initial[n-1][n-1], initial[n-1][n-2]);

		rep(i, n){
			rep(j, n){
				printf("%02d ", initial[i][j]);
			}
			cout<< endl;
		}
		rep(i, n){
			rep(j, n){
				printf("%02d ", final[i][j]);
			}
			cout<< endl;
		}

		Node* rt = newNode(initial,fh,fw,fh,fw,0,NULL);
		if(!isSolvable()){
			cout<< "SORRY NOT SOLVABLE" <<endl;
			break;
		}else{
			cout << ":) SOLVABLE" << endl;
		}
		A_Star(rt);
		return 0;
    }

	//cout<< cnt <<endl;
	cout<< mans << endl;
 
	return 0;
}