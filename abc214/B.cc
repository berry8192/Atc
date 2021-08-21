#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

void ac(string s){
	cout<< s <<endl;
	exit(0);
}

int main(){

	int a, b, ans=0;
	cin>> a >> b;

	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			for(int k=0;k<=100;k++){
				if(i*j*k<=b && i+j+k<=a) ans++;
			}
		}
	}

	cout<< ans <<endl;
 
	return 0;
}