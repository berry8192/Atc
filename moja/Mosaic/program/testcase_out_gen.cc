#include <bits/stdc++.h>
#include <experimental/filesystem>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
namespace fs = std::filesystem;

//定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
ll mod=1000000007;

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
 
ll modinv(ll a) {
    ll b = mod, u = 1, v = 0;
    while (b) {
        ll t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

int main(){
    
    string path = "../testcases/";

    vector<string> file_in_paths;
    vector<string> file_out_paths;
    for (const auto & file : fs::directory_iterator(path+"in/")){
        string tmp=file.path();
        file_in_paths.push_back(tmp);
        file_out_paths.push_back(path+"out/"+tmp.substr(16));
    }
    
    rep(lp, file_in_paths.size()){
        std::ifstream ifs(file_in_paths[lp]);
        if (!ifs)
        {
            std::cout << file_in_paths[lp] << " 読み込み失敗" << std::endl;
            continue;
        }
        cout<< "opened " << file_in_paths[lp] <<endl;
        
        int H, W;
        ifs>> H >> W;
        vector<vector<int>> A(H, vector<int>(W));
        rep(i, H) rep(j, W) ifs>> A[i][j];

        assert(1<=H && H<=1000);
        assert(1<=W && W<=1000);
        rep(i, H) rep(j, W) assert(0<=A[i][j] && A[i][j]<=255);

        // 愚直解
        ll gans=0;
        vector<vector<int>> B(H+1, vector<int>(W+1));
        rep(i, H){
            rep(j, W){
                B[i+1][j+1]=B[i][j+1]+B[i+1][j]-B[i][j]+A[i][j];
            }
        }
        rep3(i, H+1, 1){
            rep3(j, W+1, 1){
                rep3(k, min(i, j)+1, 2){
                    if((B[i][j]-B[i-k][j]-B[i][j-k]+B[i-k][j-k])%(k*k)==0) gans++;
                }
            }
        }
        cout<< gans <<endl;

        // ちゃんとした解
        ll ans=0;
        vector<vector<int>> C(H+1, vector<int>(W+1));
        rep(k, 16){
            // i=そろえる平均値
            rep(i, H){
                rep(j, W){
                    C[i+1][j+1]=C[i][j+1]+C[i+1][j]-C[i][j]+A[i][j]-k;
                }
            }
            PVV(C);
            rep3(i, H+1, 1){
                map<int, int> mp;
                rep3(j, min(H-i-j, W-j), 1){
                    int tmp=C[i+j][j]-C[i][j]-C[i+j][0]+C[i][0];
                    ans+=mp[-tmp];
                    mp[tmp]++;
                }
            }
            rep3(i, W+1, 2){
                map<int, int> mp;
                rep3(j, min(H-i-j, W-j), 1){
                    int tmp=C[j][i+j]-C[0][i+j]-C[j][i]+C[0][i];
                    ans+=mp[-tmp];
                    mp[tmp]++;
                }
            }
        }
        cout<< ans <<endl;
        assert(gans==ans);

        std::ofstream ofs(file_out_paths[lp]);
        if (!ofs){
            std::cout << file_out_paths[lp] << " 書き込み失敗" << std::endl;
            continue;
        }

        ofs<< ans <<endl;
        cout<< "ans=" << ans <<endl;
        cout<< "wrote " << file_out_paths[lp] <<endl;
    }

	return 0;
}