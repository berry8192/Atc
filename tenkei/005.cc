#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}
 
LLi modinv(LLi a) {
    LLi b = mod, u = 1, v = 0;
    while (b) {
        LLi t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}
 
LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	LLi n, b, k, key, syu, fra=-1, di;
	vector<LLi> c, ten(1), tmp;
	vector< vector<LLi> > v;
	set<LLi> s;

	cin>> n >> b >> k;
	c.resize(k);
	tmp.resize(b);
	v.resize(b);

	rep(i, k) cin >> c[i];
	rep(i, b) v[i].resize(1);

	ten[0]=1;
  	rep(i, n-1){
		if(s.count(ten[i])){
			key=i;
			cout<< i <<endl;
			for(int j=0;j<key;j++){
				if(ten[j]==ten[i]){
					syu=i-j;
					break;
				}
			}
			break;
		}
		else s.insert(ten[i]);
		ten.push_back((ten[i]*10)%b);
	}
	PVL(ten);

	v[0][0]=1;
	rep(i, b) cout<< v[i][0] << " ";
	cout<< endl;
	for(LLi i=1;i<=n;i++){
		if(key==i){
			if(ten[key]==0){
				cout<< (modpow(k, n-1)*v[0][i]) <<endl;
				return 0;
			}else{
				if(fra==-1){
					fra=modinv(v[0][i]);
				}else{
					di=fra*v[0][i-1];
					di=di%mod;
					modpow(di, (n-i)/syu);
					n=n%syu;
				}
			}
		}
		//cout<< "i=" << i <<endl;
		tmp.clear();
		tmp.resize(b, 0);
		for(LLi j=0;j<b;j++){
			//cout<< "j=" << j <<endl;
			for(LLi l=0;l<k;l++){
				//cout<< "tmp" << j << "to" << (j+1000000*b-c[l]*ten[i-1])%b << "add" << v[(j+1000000*b-c[l]*ten[i-1])%b][i-1] <<endl;
				//if(1 || i==8) cout<< (j+1000000*b-c[l]*ten[i-1])%b <<endl;// i==8 のときtenのindexが溢れるのが原因なので畳み込みを実装すると治る
				tmp[j]+=v[(j+1000000*b-c[l]*ten[i-1])%b][i-1];
				tmp[j]=tmp[j]%mod;
			}
		}
		for(LLi j=0;j<b;j++){
			v[j].push_back(tmp[j]);
		}
		 rep(j, b) cout<< v[j][i] << " ";
		 cout<< endl;
	}

	//PVL(ten);
 
	return 0;
}