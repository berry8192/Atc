#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n;
int count=0;

void judge(vector<int> x){

	int m=0;

	for(int i=0;i<9;i++){
		m+=x[i]*pow(10, i);
	}
	if(n<m) return;
	cout<< m << "\n";

	int c3=0;
	int c5=0;
	int c7=0;

	for(int i=0;i<x.size();i++){	
		if(x[i]==3) c3=1;	
		if(x[i]==5) c5=1;	
		if(x[i]==7) c7=1;
	}
	if(c3==1 && c5==1 && c7==1) count++;

}

int main(){

	vector<int> x(9);
	int l;

	cin>> n;
	l=log10(n);

	for(int i0=3;i0<8;i0+=2){
	x[0]=i0;

	for(int i1=3;i1<8;i1+=2){
	if(0<l) x[1]=i1;

	for(int i2=3;i2<8;i2+=2){
	if(1<l) x[2]=i2;
		judge(x);

	for(int i3=3;i3<8;i3+=2){
	if(2<l) x[3]=i3;
		judge(x);

	for(int i4=3;i4<8;i4+=2){
	if(3<l) x[4]=i4;
		judge(x);

	for(int i5=3;i5<8;i5+=2){
	if(4<l) x[5]=i5;
		judge(x);
	
	for(int i6=3;i6<8;i6+=2){
	if(5<l) x[6]=i6;
		judge(x);

	for(int i7=3;i7<8;i7+=2){
	if(6<l) x[7]=i7;
		judge(x);

	for(int i8=3;i8<8;i8+=2){
	if(7<l) x[8]=i8;
		judge(x);

	}}}}}}}}}


	/*for(int i0=3;i0<8;i0+=2){
	x[0]=i0;

	for(int i1=3;i1<8;i1+=2){
	if(0<l) x[1]=i1;

	for(int i2=3;i2<8;i2+=2){
	if(1<l) x[2]=i2;
	if(2<=l){
		judge(x);
		//i2=8;
	}

	for(int i3=3;i3<8;i3+=2){
	if(2<l) x[3]=i3;
	if(3<=l){
		judge(x);
		//i3=8;
	}
	for(int i4=3;i4<8;i4+=2){
	if(3<l) x[4]=i4;
	if(4<=l){
		judge(x);
		//i4=8;
	}
	for(int i5=3;i5<8;i5+=2){
	if(4<l) x[5]=i5;
	if(5<=l){
		judge(x);
		//i5=8;
	}
	for(int i6=3;i6<8;i6+=2){
	if(5<l) x[6]=i6;
	if(6<=l){
		judge(x);
		//i6=8;
	}
	for(int i7=3;i7<8;i7+=2){
	if(6<l) x[7]=i7;
	if(7<=l){
		judge(x);
		//i7=8;
	}
	for(int i8=3;i8<8;i8+=2){
	if(7<l) x[8]=i8;
	if(8<=l){
		judge(x);
		//i8=8;
	}
	}}}}}}}}}*/

	cout<< count << " " << l << "\n";

}
