#include <iostream>
#include <algorithm>
#include <vector>

struct dis{
	int dist;
	int pos;

	bool operator<( const dis& right ) const{
		return dist == right.dist ? pos < right.pos : dist < right.dist;
	}
};

int x[100000];
std::vector<dis> d(99999);

int main(){

	int n, m;

	std::cin>> n >> m;
	for(int i=0;i<m;i++){
		std::cin>> x[i];
	}

	if(m<=n){
		int a=0;
		std::cout<< a <<"\n";
		return 0;
	}

	std::sort(x, x+m);

	for(int i=0;i<m-1;i++){
		d[i].dist=x[i+1]-x[i];
		d[i].pos=x[i];
	}

	std::sort(d.begin(), d.begin()+m);


	for(int i=0;i<m;i++){
		std::cout<< d[i].dist << " " << d[i].pos << "\n";
	}


}
