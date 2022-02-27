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

int main(){

	int n, flag, tmp;
	vector<int> a, b, c, d, ra, rb;

	cin>> n;
	a.resize(n);
	b.resize(n);
	ra.resize(n);
	rb.resize(n);
	c.resize(n);
	d.resize(n);

	rep(i, n){
		cin >> a[i];
		c[i]=a[i];
		ra[n-1-i]=a[i];
	}
	rep(i, n){
		cin >> b[i];
		d[i]=b[i];
		rb[n-1-i]=b[i];
	}

	sort(all(c));
	sort(all(d));
	flag=0;
	rep(i, n){
		if(c[i]!=d[i]){
			flag=1;
			break;
		}
	}
	if(flag){
		cout<< "No" <<endl;
		return 0;
	}

	flag=0;
	rep(i, n-3) {
		// i番目の要素をそろえる、b[i]
		rep3(j, n, i){
			if(b[i]==a[j]){
				//cout<< "in" << j << " " << a[j] <<endl;
				while(j!=i){
					if(j-i==1){
						tmp=a[j];
						a[j]=a[j+1];
						a[j+1]=a[j-1];
						a[j-1]=tmp;
						j=1;
						break;
					}else{
						tmp=a[j];
						a[j]=a[j-1];
						a[j-1]=a[j-2];
						a[j-2]=tmp;
						j-=2;
					}
				}
				break;
			}
		}
		//PV(a);
	}
	if(a[n-1]==b[n-1] && a[n-2]==b[n-2] && a[n-3]==b[n-3]) flag=1;
	if(a[n-1]==b[n-3] && a[n-2]==b[n-1] && a[n-3]==b[n-2]) flag=1;
	if(a[n-1]==b[n-2] && a[n-2]==b[n-3] && a[n-3]==b[n-1]) flag=1;

	rep(i, n-3) {
		// i番目の要素をそろえる、b[i]
		rep3(j, n, i){
			if(rb[i]==ra[j]){
				//cout<< "in" << j << " " << a[j] <<endl;
				while(j!=i){
					if(j-i==1){
						tmp=ra[j];
						ra[j]=ra[j+1];
						ra[j+1]=ra[j-1];
						ra[j-1]=tmp;
						j=i;
						break;
					}else{
						tmp=ra[j];
						ra[j]=ra[j-1];
						ra[j-1]=ra[j-2];
						ra[j-2]=tmp;
						j-=2;
					}
				}
				break;
			}
		}
		//PV(a);
	}
	if(ra[n-1]==rb[n-1] && ra[n-2]==rb[n-2] && ra[n-3]==rb[n-3]) flag=1;
	if(ra[n-1]==rb[n-3] && ra[n-2]==rb[n-1] && ra[n-3]==rb[n-2]) flag=1;
	if(ra[n-1]==rb[n-2] && ra[n-2]==rb[n-3] && ra[n-3]==rb[n-1]) flag=1;

	if(flag) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}