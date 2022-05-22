#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int gcdi(int a, int b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

int lcmi(int a, int b) {
    return a/gcdi(a, b)*b;
}

int gcdv(vector<int> gv){
	int tmp=gv[0];
	for(int i=1;i<(int)gv.size();i++) tmp=gcdi(tmp, gv[i]);
	return tmp;
}

int lcmv(vector<int> gv){
	int tmp=gv[0];
	for(int i=1;i<(int)gv.size();i++) tmp=lcmi(tmp, gv[i]);
	return tmp;
}

LLi gcdi(LLi a, LLi b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

LLi lcmi(LLi a, LLi b) {
    return a/gcdi(a, b)*b;
}

LLi gcdv(vector<LLi> gv){
	LLi tmp=gv[0];
	for(int i=1;i<(int)gv.size();i++) tmp=gcdi(tmp, gv[i]);
	return tmp;
}

LLi lcmv(vector<LLi> gv){
	LLi tmp=gv[0];
	for(LLi i=1;i<(int)gv.size();i++) tmp=lcmi(tmp, gv[i]);
	return tmp;
}

//aとbが互いに素のときaとa+b, bとa+bも互いに素
//https://qiita.com/drken/items/0c88a37eec520f82b788

//整数 N が整数 x,y を用いて ax+by の形に表せる必要十分条件
//N が GCD(a,b) の倍数であることである

//a, bが互いに素の場合にすると解きやすいため、GCD(a, b)=gのとき
//ga'=a, gb'=bとおくとa'とb'が互いに素になる

int main(){

	int n;
	cin>> n;

	return 0;
}