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

	int n, tmp, t2, t5;
	LLi ind, ans=0;
	vector<int> d2, d5;
	vector< vector<int> > bo;
	string s;

	cin>> n;
	d2.resize(n);
	d5.resize(n);
	bo.resize(60);
	rep(i, 60) bo[i].resize(35, 0);

	rep(i, n){
		cin >> s;
		tmp=0;
		rep(j, s.size()){
			if(s[j]=='.'){
				tmp=s.size()-j-1;
				s.erase(s.begin() + j);
				break;
			}
		}
		ind=stoll(s);
		//cout<< ind <<" ";

		t2=-tmp;
		t5=-tmp;
		while(ind%2==0){
			t2++;
			ind/=2;
		}
		while(ind%5==0){
			t5++;
			ind/=5;
		}
		//cout<< t2 << " " << t5 <<endl;
		bo[10+t2][10+t5]++;
		d2[i]=t2;
		d5[i]=t5;
	}

	/*rep(i, 60){
		rep(j, 35){
			cout<< bo[i][j] << " ";
		}
		cout <<endl;
	}*/

	for(int i=0;i<94;i++){
		for(int j=0;j<=i;j++){
			if(0<=j && j<60 && 0<=i-j && i-j<35){
				if(bo[j][i-j]>0){
					rep(l, j+1){
						rep(m, i-j+1){
							bo[l][m]+=bo[j][i-j];
						}
					}
					bo[j][i-j]/=2;
				}
			}
		}
	}

	/*rep(i, 20){
		rep(j, 35){
			cout<< bo[i][j] << " ";
		}
		cout <<endl;
	}*/

	rep(i, n){
		ans+=bo[max(0, 10-d2[i])][max(0, 10-d5[i])];
		if(d2[i]>=0 && d5[i]>=0) ans--;
	}
	cout<< ans/2 <<endl;

	return 0;
}