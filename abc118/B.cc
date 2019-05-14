#include <iostream>

int main(){

	int n, m, flag;
	int count=0;
	int k[30], a[30][30];

	std::cin>> n >> m;

	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			a[i][j]=0;
		}
	}

	for(int i=0;i<n;i++){
		std::cin>> k[i];
		for(int j=0;j<k[i];j++){
			std::cin>> a[i][j];
		}
	}

	for(int l=1;l<=m;l++){
		flag=0;
		for(int i=0;i<n;i++){
			flag=0;
			for(int j=0;j<k[i];j++){
				if(a[i][j]==l){
					flag=1;
					break;
				}
			}
			if(flag==0) break;
		}
		if(flag==1) count++;
	}
/*
	std::cout<< n << " " << m << "\n";
	for(int i=0;i<n;i++){
		std::cout<< k[i];
		for(int j=0;j<k[i];j++){
			std::cout<< " " << a[i][j];
		}
		std::cout<< "\n";
	}
*/
	std::cout<< count << "\n";

}
