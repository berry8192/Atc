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

int main(){

	int n, ans=0;
	vector<int> v, rv;
	vector<string> s;

	cin>> n;
	v.resize(n);
	rv.resize(n+1);

	rep(i, n){
		cin >> v[i];
		rv[v[i]]=i;
	}

	rep(i, n) {
		if (rv[i+1]%2==(i)%2) continue;
		//cout<< "i:" << i+1 <<endl;
		rep(j, n){
			if(j==i) continue;
			if(i%2!=j%2 && rv[j+1]%2!=j%2){
				int ip=rv[i+1], jp=rv[j+1];
				//cout<< "ip,jp:" << ip SP << jp <<endl;
				while(abs(ip-jp)!=1){
					if(ip<jp){
						s.push_back("B "+to_string(jp+1-2));
						rv[v[jp-2]]+=2;
						rv[v[jp]]-=2;
						swap(v[jp-2], v[jp]);
						jp-=2;
					}else{
						s.push_back("B "+to_string(ip+1-2));
						rv[v[ip-2]]+=2;
						rv[v[ip]]-=2;
						swap(v[ip-2], v[ip]);
						ip-=2;
					}
				}
				s.push_back("A "+to_string(min(ip, jp)+1));
				rv[v[min(ip, jp)]]++;
				rv[v[max(ip, jp)]]--;
				swap(v[min(ip, jp)], v[max(ip, jp)]);
				break;
			}
		}
		//PV(v);
	}

	//PV(v);

	rep(i, n){
		rep(j, n-2){
			if(v[j]>v[j+2]){
				s.push_back("B "+to_string(j+1));
				swap(v[j], v[j+2]);
			}
		}
	}

	cout<< s.size() <<endl;
	rep(i, s.size()) cout<< s[i] <<endl;

	return 0;
}