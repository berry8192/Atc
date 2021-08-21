#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int main(){

	int t, n, tmp, ans, flag;
	vector<int> v;

	cin>> t;

	rep(i, t){
		flag=1;
		cin>> n;
		v.clear();
		v.resize(n);

		rep(j, n){
			cin >> tmp;
			v[j]=tmp;
		}

		if(n%2==1){
			cout<< "Second" <<endl;
			continue;
		}

		sort(v.begin(), v.end());
		rep(j, n-1){
			if(j%2==0 && v[j]!=v[j+1]){
				flag=0;
				break;
			}
		}

		if(flag) cout<< "Second" <<endl;
		else cout<< "First" <<endl;
	}

	return 0;
}