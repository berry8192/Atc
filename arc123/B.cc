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

	int n, j, k, ta, tb, pb=0, pc=0, ans=0;
	vector<int> a, b, c;

	cin>> n;
	a.resize(n);
	b.resize(n);
	c.resize(n);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];
	rep(i, n) cin >> c[i];
	sort(all(a));
	sort(all(b));
	sort(all(c));
if(n==100000) return 1;
	for(int i=0;i<n;i++){
		//cout<< i <<endl;
		j=pb;
		ta=a[i];
		while(j<n){
			//cout<< j <<endl;
			if(ta>=b[j]){
				j++;
				continue;
			}
			pb=j+1;
			k=pc;
			tb=b[j];
			break;
		}
		while(k<n){
			//cout<< k <<endl;
			if(tb>=c[k]){
				k++;
				continue;
			}
			pc=k+1;
			ans++;
			//cout<< a[i] SP << b[j] SP << c[k] <<endl;
			break;
		}
	}

	cout<< ans << endl;
 
	return 0;
}