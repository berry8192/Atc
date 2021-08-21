#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int k, sp, tp, tmp;
	double ans=0.0, as, bs, at, bt;
	vector<int> sv(10, 0), tv(10, 0), ten={1, 10, 100, 1000, 10000, 100000};
	string s, t;
	
	cout << fixed << setprecision(12);

	cin>> k;
	cin>> s >> t;

	for(int i=0;i<4;i++){
		sv[(int)(s[i]-'0')]++;
		tv[(int)(t[i]-'0')]++;
	}

	//PV(sv);
	//PV(tv);

	for(int i=1;i<10;i++){
		for(int j=1;j<10;j++){
			//cout<< i SP <<j <<endl;
			//sがiを引きtがjを引くとする
			//cout<< sv[i]+tv[i]+1 <<endl;
			//cout<< sv[j]+tv[j]+1 <<endl;
			if(sv[i]+tv[i]+1>k) continue;
			if(sv[j]+tv[j]+1>k) continue;
			if(i==j && sv[i]+tv[i]+2>k) continue;

			sp=0;
			tp=0;
			for(int l=1;l<10;l++){
				tmp=sv[l];
				if(l==i) tmp++;
				sp+=ten[tmp]*l;
			}
			for(int l=1;l<10;l++){
				tmp=tv[l];
				if(l==j) tmp++;
				tp+=ten[tmp]*l;
			}

			//cout<< i SP << j SP << sp SP << tp << endl;

			if(sp<=tp) continue;

			bs=9*k-8;
			as=k-sv[i]-tv[i];
			bt=9*k-9;
			at=k-sv[j]-tv[j];
			if(i==j) at--;

			ans+=as/bs*at/bt;
		}
	}

	cout<< ans << endl;
 
	return 0;
}