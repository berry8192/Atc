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

struct st{
	int k;
	LLi v;

	bool operator<(const st &in) const{
		return k<in.k;
	};
};

int main(){

	int n;
	LLi w, u=0, hs=0, ht=0, is, it, ip;
	vector<st> s, t;

	cin>> n >> w;
	s.resize(n+1);
	t.resize(n+1);

	rep(i, n){
		cin >> is >> it >> ip;
		s[i].k=is;
		s[i].v=ip;
		t[i].k=it;
		t[i].v=ip;
	}
		s[n].k=imax;
		s[n].v=0;
		t[n].k=imax;
		t[n].v=0;
	
	sort(s.begin(), s.end());
	sort(t.begin(), t.end());

	while(hs<n || ht<n){
		if(ht>n-1 || s[hs].k<t[ht].k){
			u+=s[hs].v;
			if(w<u){
				cout<< "No" <<endl;
				return 0;
			}
			hs++;
		}else{
			u-=t[ht].v;
			ht++;
		}
		//cout<< u << " " << hs << " " << ht <<endl;
	}

	cout<< "Yes" << endl;
 
	return 0;
}