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

	LLi x, y, r, flag, ans=0;
	string sx, sy, sr, ssx, ssy, ssr;

	cin>> sx >> sy >> sr;

	flag=4;
	for(int i=0;i<(int)sx.size();i++){
		if(sx[i]!='.'){
			ssx.push_back(sx[i]);
		}else{
			//for(int j=0;j<i+5-(int)sx.size();j++) ssx+="0";
			flag=i+5-(int)sx.size();
		}
	}
			//cout<< flag <<endl;
	if(flag){
		for(int i=0;i<flag;i++) ssx+="0";
	}

	flag=4;
	for(int i=0;i<(int)sy.size();i++){
		if(sy[i]!='.'){
			ssy.push_back(sy[i]);
		}else{
			//for(int j=0;j<i+5-(int)sy.size();j++) ssy+="0";
			flag=i+5-(int)sy.size();
		}
	}
			//cout<< flag <<endl;
	if(flag){
		for(int i=0;i<flag;i++) ssy+="0";
	}
	
	flag=4;
	for(int i=0;i<(int)sr.size();i++){
		if(sr[i]!='.'){
			ssr.push_back(sr[i]);
		}else{
			//for(int j=0;j<i+5-(int)sr.size();j++) ssr+="0";
			flag=i+5-(int)sr.size();
		}
	}
			//cout<< flag <<endl;
	if(flag){
		for(int i=0;i<flag;i++) ssr+="0";
	}

	//cout<< ssx << endl;
	//cout<< ssy << endl;
	//cout<< ssr << endl;

	x=stoi(ssx);
	y=stoi(ssy);
	r=stoi(ssr);

	//cout<< x << endl;
	//cout<< y << endl;
	//cout<< r << endl;

	LLi s=x-r;
	LLi e=x+r;

	s=(s/10000-2)*10000;
	e=(e/10000+2)*10000;
	//cout<< s << " " << e <<endl;

	double h;
	LLi u, d, zer=0;
	for(LLi i=s;i<=e;i+=10000){
		if(r-abs(x-i)<0) continue;
		h=sqrt(r*r-abs(x-i)*abs(x-i));
		u=(y+floor(h))/10000;
		d=(y-floor(h)+9999)/10000;
		ans+=max(zer, u-d+1);
		//cout<< i/10000 SP << h SP << u SP << d <<endl;
	}

	cout<< ans <<endl;
 
	return 0;
}