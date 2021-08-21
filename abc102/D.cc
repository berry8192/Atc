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

	int n, l, r, mid, tmp;
	LLi mi=llimax, sul, sur, sb;
	vector<LLi> v, su(4);

	cin>> n;
	v.resize(n+1);

	rep(i, n){
		cin >> tmp;
		v[i+1]=v[i]+tmp;
	}
	//PVL(v);

	for(int i=2;i<=n-2;i++){
		fill( all(su), 0 );

		l=1;
		r=i;
		while(1){
			mid=(l+r)/2;
			sul=v[mid];
			sur=v[i]-v[mid];
			//cout<< l << "#" << r << " " << sul << " " << sur <<endl;
			if(r-l<2) break;

			if(sul<sur) l=mid;
			else r=mid;
		}
		sb=abs(sur-sul);
		su[0]=sul;
		su[1]=sur;
		if(abs(sur-sul-2*(v[mid+1]-v[mid]))<sb){
			su[0]+=v[mid+1]-v[mid];
			su[1]-=v[mid+1]-v[mid];
		}
		//cout<< su[0] << " " << su[1] << " ";

		l=i+1;
		r=n;
		while(1){
			mid=(l+r)/2;
			sul=v[mid]-v[i];
			sur=v[n]-v[mid];
			//cout<< l << "#" << r << " " << sul << " " << sur <<endl;
			if(r-l<2) break;

			if(sul<sur) l=mid;
			else r=mid;
		}
		sb=abs(sur-sul);
		su[2]=sul;
		su[3]=sur;
		if(abs(sur-sul-2*(v[mid+1]-v[mid]))<sb){
			su[2]+=v[mid+1]-v[mid];
			su[3]-=v[mid+1]-v[mid];
		}
		//cout<< su[2] << " " << su[3] <<endl;

		sort(su.begin(), su.end());
		//PVL(su);
		mi=min(mi, su[3]-su[0]);
	}

	cout<< mi <<endl;
 
	return 0;
}