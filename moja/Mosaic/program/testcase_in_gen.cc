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

int main(){
    int lp;
    cin>> lp;
    
    // int seed=10000;
    auto seed=(unsigned)time(NULL);
    mt19937 mt(seed);

    rep(i, lp){
        string fname="../testcases/in/hand-0"+to_string(i+1)+".txt";
        std::ofstream ofs(fname);
        if (!ofs){
            std::cout << fname << " 書き込み失敗" << std::endl;
            continue;
        }

        int H, W;
        // H=mt()%10+1;
        // W=mt()%10+1;
        H=1000;
        W=1000;
        vector<vector<int>> A(H, vector<int>(W));
        // rep(i, H) rep(j, W) A[i][j]=mt()%9+1;
        rep(i, H) rep(j, W) A[i][j]=1;

        ofs<< H SP << W <<endl;
        rep(i, A.size()){
            rep(j, A[i].size()){
                ofs << A[i][j] SP;
            }
            ofs << endl;
        }
    }
    
	return 0;
}