#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct kaz{
	int val;
	int num;

	bool operator<(const kaz &in) const{
		return val!=in.val ? val>in.val : num<in.num;
	};
};

int main(){

	int h, w, m, ih, iw, tmp, che, ma=0;
	vector<int> a, b;
	vector<kaz> aa, bb;
	map<kaz, int> mp, mapo;
	kaz tmpk;

	cin>> h >> w >> m;
	a.resize(h);
	b.resize(w);
	aa.resize(h);
	bb.resize(w);

	rep(i, m){
		cin >> ih >> iw;
		ih--;
		iw--;
		tmpk.val=ih;
		tmpk.num=iw;
		mp[tmpk]=i+1;
		a[ih]++;
		b[iw]++;
	}

	rep(i, h) {
		aa[i].val=a[i];
		//cout<< a[i] << " " << b[i] <<endl;
		aa[i].num=i;
	}
	rep(i, w) {
		bb[i].val=b[i];
		//cout<< a[i] << " " << b[i] <<endl;
		bb[i].num=i;
	}
	
	sort(aa.begin(), aa.end());
	sort(bb.begin(), bb.end());

	/*for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			tmpk.val=i;
			tmpk.num=j;
			cout<< mp[tmpk] <<endl;
		}
	}*/

	//cout<< mp.size() <<endl;

	int flag=0, cnt=0;

	for(int i=0;i<h;i++){
		if(i>0 && aa[i-1].val!=aa[i].val) break;
		for(int j=0;j<w;j++){
			if(j>0 && bb[j-1].val!=bb[j].val) flag=1;
			if(flag) break;
			tmp=aa[i].val+bb[j].val;
			tmpk.val=aa[i].num;
			tmpk.num=bb[j].num;
			//cout<< tmp <<endl;
			if(cnt<=m){
				mapo[tmpk]=1;
			}else{
				cout<< ma <<endl;
				return 0;
			}
			if(mp.count(tmpk)){
				tmp--;
				//cout<< i << j <<endl;
			}else{
				cout<< max(ma, tmp) <<endl;
				return 0;
			}
			ma=max(ma, tmp);
		}
	}

	cout<< ma <<endl;
 
	return 0;
}