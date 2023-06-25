#include <bits/stdc++.h>
using namespace std;

//by num sort
struct xxxx{
	int value;
	int num;

	bool operator<(const xxxx &in) const{
		return num<in.num;
	};
};

//2 factor sort
struct xxxx{
	int x1;
	int x2;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

//3 factor sort
struct xxxx{
	int x1;
	int x2;
	int x3;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2!=in.x2 ? x2<in.x2 : x3<in.x3;
	};
};

// 区間型
struct itv{
	int le, ri;

	// 区間スケジュール的な、終わるのが早い順で始まるのが遅い順のソート用
	bool operator<(const itv &in) const{
		return ri!=in.ri ? ri<in.ri : le>in.le;
	};

	// 区間が重なっているかどうか（端点を含ませたい場合は<=を使う）
	bool cover(itv x, itv y){
		return max(x.le, y.le)<min(x.ri, y.ri);
	}
};

int main(){
	
}