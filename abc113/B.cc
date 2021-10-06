#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){

	int n;
	int t;
	int a;
	double min=100000000.0;
	double cal;
	int mini;
	vector<int> h;

	cin>> n >> t >> a;

	h.resize(n);

	for(int i=0;i<n;i++){
		cin>> h[i];
		cal=abs(t-h[i]*0.006-a);
		if(cal<min){
			min=cal;
			mini=i+1;
		}
	}

	cout<< mini << "\n";
}
