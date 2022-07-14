#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

int main(){

	int a, b=0;
	cin>> a;
	vector<string> w={"TAKAHASHIKUN", "Takahashikun", "takahashikun"};

	rep(i, a){
		string s;
		cin>> s;
		if(i==a-1) s.pop_back();
		//cout<< s <<endl;
		int flag=0;
		rep(j, 3){
			if(s==w[j]){
				flag=1;
				break;
			}
		}
		b+=flag;
	}

	cout<< b <<endl;
 
	return 0;
}