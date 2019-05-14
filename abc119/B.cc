#include <iostream>
#include <string>

using namespace std;

int main(){

	int n;
	double get=0.0;
	double x;
	string u;

	cin>> n;

	for(int i=0;i<n;i++){
		cin>> x >> u;
		if(u=="BTC") x*=380000.0;
		get+=x;
	}

	cout<< get << "\n";
}
