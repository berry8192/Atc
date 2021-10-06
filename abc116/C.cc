#include <iostream>
#include <vector>

using namespace std;

int main(){

	int n, flag;
	int hmax=0;
	int hsum=0;
	int rdc=0;
	vector<int> h;

	cin>> n;

	h.resize(n);

	for(int i=0;i<n;i++){
		cin>> h[i];
		hsum+=h[i];
		if(hmax<h[i]) hmax=h[i];
	}

	//
	//cout<< hsum << " " << hmax << "\n";
	//

	for(int i=0;i<hmax;i++){
		flag=0;
		for(int j=0;j<n;j++){
			if(i+1<=h[j]){
				if(flag==1){
					rdc++;
					//cout<< "rdc";//
				}else{
					flag=1;
				}
			}else{
				flag=0;
			}
		//cout<< "\n";//
		}	
	//cout<< "\n";//
	}

	cout<< hsum-rdc << "\n";

}
