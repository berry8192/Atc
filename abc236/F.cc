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

string tob(LLi n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

struct sp{
	int c;
	int nu;

	bool operator<(const sp &in) const{
		return c<in.c;
	};
};

int main(){

	int n, m;
	LLi ans=0;
	string s;
	sp tmp;
	vector<sp> v;
	vector< vector<int> > bo;

	cin>> n;
	bo.resize(n);
	rep(i, n) bo[i].resize(n, 0);

	m=1<<n;
	m--;
	v.resize(m);
	//cout<< tob(n) <<endl;

	rep(i, m){
		cin >> tmp.c;
		tmp.nu=i+1;
		v[i]=tmp;
	}
	sort(all(v));

	rep(i, m){
		s=tob(v[i].nu, n);
		//cout<< s <<endl;
		int flag=0;
		rep(j, n){
			for(int k=j+1;k<n;k++){
				//if(j==k) continue;
				//cout<< "j=" << j SP << "k=" << k <<endl;
				if(bo[j][k]==0){
					if(s[j]!=s[k]){
						flag=2;
						bo[j][k]=1;
					}
					flag=max(flag, 1);
				}
			}
		}
		if(flag==2 || i==0) ans+=v[i].c;
		if(flag==0) break;
	}

	cout<< ans <<endl;
 
	return 0;
}