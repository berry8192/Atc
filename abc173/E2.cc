#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;

LLi modabs(LLi x){
	if(x>=0) return (x%mod);

	LLi tmp=abs(x);
	LLi di=(tmp+mod-1)/mod;
	return mod*di+x;
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

int main(){

	int n, k, zer=0, pp=0, mp=0, sig=1;
	vector<LLi> pv, mv;
	LLi tmp, ans=1;

	cin>> n >> k;

	rep(i, n){
		cin >> tmp;
		if(0<tmp) pv.push_back(tmp);
		if(0>tmp) mv.push_back(tmp);
		if(tmp==0) zer++;
	}
	
	sort(pv.begin(), pv.end(), greater<LLi>());
	sort(mv.begin(), mv.end());

	if(k%2==1 && n==(int)mv.size()){
		rep(i, k){
			ans*=modabs(mv[mv.size()-1-i]);
			ans=ans%mod;
		}
		cout<< ans <<endl;
		return 0;
	}

	rep(i, k){
		if((int)pv.size()==pp && (int)mv.size()==mp){
			cout<< 0 <<endl;
			return 0;
		}else if((int)pv.size()==pp){
			ans*=modabs(mv[mp]);
			ans=ans%mod;
			sig*=-1;
			mp++;
		}else if((int)mv.size()==mp){
			ans*=pv[pp];
			ans=ans%mod;
			pp++;
		}else{
			if(-mv[mp]<=pv[pp]){
				ans*=pv[pp];
				ans=ans%mod;
				pp++;
			}else{
				ans*=modabs(mv[mp]);
				ans=ans%mod;
				sig*=-1;
				mp++;
			}
		}
	}
	//cout<< "mp=" << mp <<endl;//
	//cout<< "pp=" << pp <<endl;//

	LLi p1=-1, p2=-1;
	if(sig!=1){
		if(pp!=(int)pv.size() && mp!=0) p1=pv[pp]*pv[pp-1];
		if(mp!=(int)mv.size() && pp!=0) p2=mv[mp]*mv[mp-1];
		//cout<< p1 <<endl;
		//cout<< p2 <<endl;

		if(p1>p2){
			ans*=pv[pp];
			ans=ans%mod;
			ans*=modinv(modabs(mv[mp-1]));
			ans=ans%mod;
		}
		if(p1<p2){
			ans*=modabs(mv[mp]);
			ans=ans%mod;
			ans*=modinv(pv[pp-1]);
			ans=ans%mod;
		}
		if(p1==-1 && p2==-1 && zer>0) ans=0;
	}

	cout<< ans <<endl;
 
	return 0;
}