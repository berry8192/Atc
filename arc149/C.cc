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
//using mint = modint1000000007;
//using mint = modint=998244353;

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

vector<int> Eratosthenes( const int N )
{
    std::vector<bool> is_prime( N + 1 );
    for( int i = 0; i <= N; i++ )
    {
        is_prime[ i ] = true;
    }
    std::vector<int> P;
    for( int i = 2; i <= N; i++ )
    {
        if( is_prime[ i ] )
        {
            for( int j = 2 * i; j <= N; j += i )
            {
                is_prime[ j ] = false;
            }
            P.emplace_back( i );
        }
    }
    return P;
}

int main(){

	int n, ans=0;
	vector<vector<int>> v, st;
	vector<int> dirx={0, 1, 0, -1}, diry={1, 0, -1, 0};
	vector<int> P=Eratosthenes(1000100);
	set<int> pri;
	rep(i, P.size()) pri.insert(P[i]);
	// PV(P);

	cin>> n;
	v.resize(n);
	rep(i, n) v[i].resize(n);
	st.resize(n);
	rep(i, n) st[i].resize(n);

	if(n==3){
		cout<< "4 2 6" <<endl;
		cout<< "8 7 9" <<endl;
		cout<< "1 3 5" <<endl;
		return 0;
	}

	rep(i, (n+1)/2){
		rep(j, n){
			v[i][j]=(i*n+j)*2+1;
		}
	}

	rep(i, (n+1)/2){
		rep(j, n){
			if((i*n+j+1)*2>n*n) break;
			v[n-1-i][n-1-j]=(i*n+j+1)*2;
		}
	}

	rep(i, n){
		rep(j, n){
			rep(k, 4){
				int x=i+dirx[k];
				int y=j+diry[k];
				if(x<0 || n<=x || y<0 || n<=y) continue;
				int su=v[i][j]+v[x][y];
				if(pri.find(su)!=pri.end()){
					st[i][j]=1;
					st[x][y]=1;
				}
			}
		}
	}
	// PVV(st);

	rep(i, n){
		rep(j, n){
			if(st[i][j]){
				int deru=0;
				rep(k, n){
					rep(l, n){
						swap(v[i][j], v[k][l]);
						int flag=1;
						rep(d, 4){
							int x=i+dirx[d];
							int y=j+diry[d];
							if(x<0 || n<=x || y<0 || n<=y) continue;
							int su=v[i][j]+v[x][y];
							if(pri.find(su)!=pri.end()){
								// cout<< su <<endl;
								flag=0;
								// cout<< "NG" <<endl;
								break;
							}
						}
						rep(d, 4){
							int x=k+dirx[d];
							int y=l+diry[d];
							if(x<0 || n<=x || y<0 || n<=y) continue;
							int su=v[k][l]+v[x][y];
							if(pri.find(su)!=pri.end()){
								// cout<< su <<endl;
								flag=0;
								break;
							}
						}
						if(flag){
							deru=1;
							st[i][j]=0;
							// cout<< i SP << j SP << k SP << l <<endl; 
							break;
						}else{
							swap(v[i][j], v[k][l]);
						}
					}
					if(deru) break;
				}
			}
		}
	}
	
	// PVV(st);

	rep(i, (n+1)/2){
		rep(j, n){
			if((i*n+j+1)*2>n*n) break;
			swap(v[i][j], v[n-1-i][n-1-j]);
			swap(st[i][j], st[n-1-i][n-1-j]);
		}
	}

	rep(i, n){
		rep(j, n){
			if(st[i][j]){
				int deru=0;
				rep(k, n){
					rep(l, n){
						swap(v[i][j], v[k][l]);
						int flag=1;
						rep(d, 4){
							int x=i+dirx[d];
							int y=j+diry[d];
							if(x<0 || n<=x || y<0 || n<=y) continue;
							int su=v[i][j]+v[x][y];
							if(pri.find(su)!=pri.end()){
								// cout<< su <<endl;
								flag=0;
								// cout<< "NG" <<endl;
								break;
							}
						}
						rep(d, 4){
							int x=k+dirx[d];
							int y=l+diry[d];
							if(x<0 || n<=x || y<0 || n<=y) continue;
							int su=v[k][l]+v[x][y];
							if(pri.find(su)!=pri.end()){
								// cout<< su <<endl;
								flag=0;
								break;
							}
						}
						if(flag){
							deru=1;
							st[i][j]=0;
							// cout<< i SP << j SP << k SP << l <<endl; 
							break;
						}else{
							swap(v[i][j], v[k][l]);
						}
					}
					if(deru) break;
				}
			}
		}
	}

	PVV(v);
 
	return 0;
}