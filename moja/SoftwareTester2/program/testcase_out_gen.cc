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
    
    rep(i, file_in_paths.size()){
        std::ifstream ifs(file_in_paths[i]);
        if (!ifs)
        {
            std::cout << file_in_paths[i] << " 読み込み失敗" << std::endl;
            continue;
        }
        cout<< "opened " << file_in_paths[i] <<endl;
        
        int N;
        vector<int> P;
        ifs>> N;
        cout<< "N=" << N <<endl;
        P.resize(N);
        rep(i, N) ifs>> P[i];
        //cout<< "P=";
        //PV(P);
        assert(1<=N && N<=100000);
        rep(i, N) assert(1<=P[i] && P[i]<=1000000000);

        ll ans=0;
        ll prod=1;
        rep(i, N){
            prod*=P[i];
            prod%=mod;
        }
        rep(i, N){
            ll cases=(prod*modinv(P[i]))%mod;
            ll psum=(1LL*P[i]*(P[i]+1)/2LL)%mod;
            ans+=(cases*psum)%mod;
            ans%=mod;
        }

        std::ofstream ofs(file_out_paths[i]);
        if (!ofs){
            std::cout << file_out_paths[i] << " 書き込み失敗" << std::endl;
            continue;
        }

        ofs<< ans <<endl;
        cout<< "ans=" << ans <<endl;
        cout<< "wrote " << file_out_paths[i] <<endl;
    }

	return 0;
}