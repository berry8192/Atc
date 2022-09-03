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

	string s;
	cin>> s;
	vector<int> v(7);

	if(s[0]=='1'){
		cout<< "No" << endl;
		return 0;
	}

	if(s[1]=='1') v[2]=1;
	if(s[2]=='1') v[4]=1;
	if(s[3]=='1') v[1]=1;
	if(s[4]=='1') v[3]=1;
	if(s[5]=='1') v[5]=1;
	if(s[6]=='1') v[0]=1;
	if(s[7]=='1') v[2]=1;
	if(s[8]=='1') v[4]=1;
	if(s[9]=='1') v[6]=1;
	
	rep(i, 7){
		rep3(j, 7, i+2){
			if(v[i]==1 && v[j]==1){
				int flag=0;
				rep3(k, j, i+1){
					if(v[k]==1) flag=1;
				}
				if(flag==0){
					cout<< "Yes" << endl;
					return 0;
				}
			}
		}
	}
	
	cout<< "No" << endl;
 
	return 0;
}