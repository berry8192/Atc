#include <iostream>
#include <vector>

using namespace std;

//vector<int> bg;
//vector<int> pbg(1);
vector<long int> p(50);
vector<long int> b(50);
vector<long int> sum(50);

int sol(long int x, int i, long int eat, long int eatp){

	if(i==0) return eatp+1;

//cout<< "sol: " << i << " " << eat << " " << eatp << " " << "\n";//
//cout<< sum[i-1] << "\n";//

	if(x==eat+1){
		//cout<<"case a: " << "\n\n";//
		return eatp;

	}else if(eat+2*sum[i-1]+3==x){
		//cout<<"case e: " << "\n\n";//
		return eatp+2*p[i-1]+1;

	}else if(eat+2*sum[i-1]+2<=x){
		//cout<<"case d: " << eat+sum[i-1]+2 << "\n\n";//
		return sol(x, i-1, eat+sum[i-1]+2, eatp+p[i-1]+1);

	}else if(eat+sum[i-1]+2==x){
		//cout<<"case c: " << "\n\n";//
		return eatp+p[i-1]+1;

	}else if(eat+sum[i-1]+1<=x){
		//cout<<"case b: " << eat+1 << "\n\n";//
		return sol(x, i-1, eat+1, eatp);

	}else{
		//cout<< "case f" << " " << eat << " " << sum[i-1] << " " << x << "\n";//
	}

}

int main(){

	int n;
	long int x, eatp;

	p[0]=1;
	b[0]=0;
	sum[0]=p[0]+b[0];
	//eat=sum[0];
	//eatp=p[0];

	cin>> n;
	cin>> x;

	for(int i=1;i<=n;i++){
		p[i]=2*p[i-1]+1;
		b[i]=2*b[i-1]+2;
		//cout<< i << " " << p[i] << " " << b[i] << "\n";//
		if(x<p[i]+b[i]){
			eatp=sol(x, i-1, sum[i-1], p[i-1]);
			cout<< eatp << "\n";
			return 0;
		}
		sum[i]=p[i]+b[i];
	}

	cout<< /*"w " << */sum[n] << "\n";

	/*pbg[0]=1;

	for(int i=1;i<n;i++){
		bg.resize(1);
		bg[0]=0;
		bg.insert(bg.end(), pbg.begin(), pbg.end());
		bg.emplace_back(1);
		bg.insert(bg.end(), pbg.begin(), pbg.end());
		bg.emplace_back(0);
		pbg=bg;
	}

	for(int i=0;i<bg.size();i++) cout<< bg[i] << "\n";//

	if(bg.size()<x) x=bg.size();

	for(int i=0;i<x;i++){
		if(bg[i]==1) sum++;
	}

	cout<< sum << "\n";*/

}
