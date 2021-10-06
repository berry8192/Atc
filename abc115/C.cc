#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){

	int n, k;
	int min=-1;
	int sum=0;
	vector<int> h;

	cin>> n;
	cin>> k;

	h.resize(n);

	for(int i=0;i<n;i++){
		cin>> h[i];
	}

	sort(h.begin(), h.end());

	//for(int i=0;i<n;i++) cout<< h[i] << "\n";//

	for(int i=0;i<n-k+1;i++){
//cout<< " " << h[i+k-1]-h[i] << "\n";//
		if(h[i+k-1]-h[i]<min || min==-1){
			min=h[i+k-1]-h[i];
//cout<< "  " << min << "\n";//
		}
	}

	cout<< min << "\n";

}
