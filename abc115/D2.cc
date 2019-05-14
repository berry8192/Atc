#include <iostream>
#include <vector>

using namespace std;

vector<long long int> p(50);
vector<long long int> sum(50);

int sol(int n, long long int x, int i){
//cout<< i << " " << n << " " << x << "\n";

	if(x==1){
		//cout<< "case a" << "\n";//
		return 0;

	}else if(x<=1+sum[i-1]){
		//cout<< "case b" << "\n";//
		return sol(n-1, x-1, i-1);

	}else if(x==2+sum[i-1]){
		//cout<< "case c" << "\n";//
		return p[i-1]+1;

	}else if(x<=2+2*sum[i-1]){
		//cout<< "case d" << "\n";//
		return p[i-1]+1+sol(n-1, x-2-sum[i-1], i-1);

	}else if(x==3+2*sum[i-1]){
		//cout<< "case e" << "\n";//
		return 2*p[i-1]+1;

	}else{
		//cout<< "case f" << "\n";//
	}

}

int main(){

	int n;
	long long int x;

	p[0]=1;
	sum[0]=p[0];

	cin>> n;
	cin>> x;

	for(int i=1;i<=n;i++){
		p[i]=2*p[i-1]+1;
		sum[i]=2*sum[i-1]+3;
//cout<< i << " " << p[i] << " " << sum[i] << "\n";//
		if(x<sum[i]){
			cout<< sol(n, x, i) << "\n";
			return 0;
		}
	}

	cout<< sum[n] << "\n";
	

}
