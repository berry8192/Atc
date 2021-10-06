#include <iostream>
#include <vector>

using namespace std;
int main(){

	int n, mi;
	int max=0;
	int sum=0;
	vector<int> p;

	cin>> n;

	p.resize(n);

	for(int i=0;i<n;i++){
		cin>> p[i];
		sum+=p[i];
		if(max<p[i]){
			max=p[i];
			mi=i;
		}
	}

	sum-=p[mi]/2;

	cout<< sum << "\n";

}
