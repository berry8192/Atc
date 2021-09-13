#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

vector< vector<char> > s, t1, t2, t3, t4;

int main(){

	int n, ans=0;

	cin>> n;
	s.resize(n);
	rep(i, n) s[i].resize(n);
	t1.resize(n);
	rep(i, n) t1[i].resize(n);
	t2.resize(n);
	rep(i, n) t2[i].resize(n);
	t3.resize(n);
	rep(i, n) t3[i].resize(n);
	t4.resize(n);
	rep(i, n) t4[i].resize(n);

	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<n;j++){
			s[i][j]=tmp[j];
		}
	}
	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		for(int j=0;j<n;j++){
			t1[i][j]=tmp[j];
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			t2[i][j]=t1[n-1-j][i];
			t3[i][j]=t1[n-1-i][n-1-j];
			t4[i][j]=t1[j][n-1-i];
		}
	}

	// rep(i, n){
	// 	rep(j, n){
	// 		cout<< t1[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }
	// cout<< endl;
	// rep(i, n){
	// 	rep(j, n){
	// 		cout<< t2[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }
	// cout<< endl;
	// rep(i, n){
	// 	rep(j, n){
	// 		cout<< t3[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }
	// cout<< endl;
	// rep(i, n){
	// 	rep(j, n){
	// 		cout<< t4[i][j] << " ";
	// 	}
	// 	cout<< endl;
	// }
	// cout<< endl;

	string sj="", t1j="", t2j="", t3j="", t4j="";
	
	int flag=1, fx=0, fy=0;
	rep(i, n){
		rep(j, n){
			if(s[i][j]=='#'){
				if(flag){
					fx=i;
					fy=j;
					flag=0;
				}else{
					sj+=to_string(i-fx);
					sj+=to_string(j-fy);
				}
			}
		}
	}
	flag=1;
	rep(i, n){
		rep(j, n){
			if(t1[i][j]=='#'){
				if(flag){
					fx=i;
					fy=j;
					flag=0;
				}else{
					t1j+=to_string(i-fx);
					t1j+=to_string(j-fy);
				}
			}
		}
	}
	if(sj==t1j){
		cout<< "Yes" << endl;
		return 0;
	}
 	flag=1;
	rep(i, n){
		rep(j, n){
			if(t2[i][j]=='#'){
				if(flag){
					fx=i;
					fy=j;
					flag=0;
				}else{
					t2j+=to_string(i-fx);
					t2j+=to_string(j-fy);
				}
			}
		}
	}
	if(sj==t2j){
		cout<< "Yes" << endl;
		return 0;
	}
	flag=1;
	rep(i, n){
		rep(j, n){
			if(t3[i][j]=='#'){
				if(flag){
					fx=i;
					fy=j;
					flag=0;
				}else{
					t3j+=to_string(i-fx);
					t3j+=to_string(j-fy);
				}
			}
		}
	}
	if(sj==t3j){
		cout<< "Yes" << endl;
		return 0;
	}
	flag=1;
	rep(i, n){
		rep(j, n){
			if(t4[i][j]=='#'){
				if(flag){
					fx=i;
					fy=j;
					flag=0;
				}else{
					t4j+=to_string(i-fx);
					t4j+=to_string(j-fy);
				}
			}
		}
	}
	if(sj==t4j){
		cout<< "Yes" << endl;
		return 0;
	}

	// cout<< sj <<endl;
	// cout<< t1j <<endl;
	// cout<< t2j <<endl;
	// cout<< t3j <<endl;
	// cout<< t4j <<endl;

	cout<< "No" << endl;
 
	return 0;
}