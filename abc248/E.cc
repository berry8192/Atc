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

	LLi n, k, ans=0;
	vector<LLi> x, y;
	set<string> li;

	cin>> n >> k;
	if(k==1){
		cout<< "Infinity" <<endl;
		return 0;
	}
	x.resize(n);
	y.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	rep(i, n) {
		for(int j=i+1;j<n;j++){
			int fig=2;
			LLi aa=y[j]-y[i];
			LLi ab=x[j]-x[i];
			LLi tmp=__gcd(aa, ab);
			aa/=tmp;
			ab/=tmp;

			if(ab==0){
				LLi d=x[j];
				
				string s;
				s+=to_string(d)+"/";
				//cout<< s <<endl;
				if(li.find(s)==li.end()){
					li.insert(s);
					for(int l=j+1;l<n;l++){
						if(l==i || l==j) continue;
						if(x[l]==d){
							fig++;
						}
					}
					if(fig>=k) ans++;
				}
			}else{
				LLi bb=ab;
				LLi ba=-aa*x[i];
				ba+=ab*y[i];
				tmp=__gcd(ba, bb);
				ba/=tmp;
				bb/=tmp;
				string s;
				s+=to_string(aa)+"/";
				s+=to_string(ab)+"/";
				s+=to_string(ba)+"/";
				s+=to_string(bb)+"/";
				//cout<< s <<endl;
				if(li.find(s)==li.end()){
					li.insert(s);
					for(int l=j+1;l<n;l++){
						if(l==i || l==j) continue;
						LLi ca=aa*x[l];
						LLi cb=ab;
						ca=cb*y[l]-ca;
						tmp=__gcd(ca, cb);
						ca/=tmp;
						cb/=tmp;
						if(cb*ba==ca*bb) fig++;
					}
					if(fig>=k) ans++;
				}
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}