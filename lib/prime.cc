#include <bits/stdc++.h>
#include <vector>
#include <cmath>

using namespace std;

vector<int> pri;

//n以下の素数を配列に
void list_prime(int n){
	int flag, sqrtn;
	pri.emplace_back(2);

	for(int i=3;i<=n;i+=2){
		flag=0;
		sqrtn=(int)sqrt(n)+1;
		for(int j=0;j<pri.size();j++){
			if(i%pri[j]==0){
				flag=1;
				break;
			}
			if(sqrtn<pri[j]) break;
		}
		if(flag==0) pri.emplace_back(i);
	}
}

//nを素因数分解
vector<int> prime_fac(int n){
	int lmt=0;
	while(1){
		if(n<=pri[lmt]) break;
		lmt++;
		//if(pri.size()<=lmt) list_prime(n);
		//cout<< lmt << " " << pri[lmt] << endl;
	}

	vector<int> fac(lmt+1, 0);

	for(int i=0;i<pri.size();i++){
		while(n%pri[i]==0){
			n/=pri[i];
			fac[i]++;
		}
		if(n==1) break;
	}

	return fac;

}

int main(){

	int n, m;
	vector<int> v;

	cin>> n >> m;

	list_prime(n);
	//for(int i=0;i<pri.size();i++) cout<< pri[i] << endl;
	v=prime_fac(m);
	//for(int i=0;i<v.size();i++) cout<< v[i] << endl;

}
