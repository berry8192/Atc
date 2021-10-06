#include <iostream>

int main(){

	int n, l[110];
	int sum=0;
	int flag=0;

	std::cin>> n;
	for(int i=0;i<n;i++){
		std::cin>> l[i];
		sum+=l[i];
	}

	for(int i=0;i<n;i++){
		if(sum<=2*l[i]){
			std::cout<< "No" << "\n";
			flag=1;
			break;
		}
	}
	if(flag==0) std::cout<< "Yes" << "\n";

	/*
	std::cout<< n << "\n";
	for(int i=0;i<n;i++){
		std::cout<< " " << l[i];
	}
	std::cout<< "\n";
	*/

}
