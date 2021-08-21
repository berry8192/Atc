#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
template<class Operator> class LazySegmentTree {
    Operator Op;                                       
	using typeNode = decltype(Op.unitNode);          
	using typeLazy = decltype(Op.unitLazy);
	size_t num;      
	size_t length;                                   
	size_t height;                                   
	vector<typeNode> node;                           
	vector<typeLazy> lazy;                           
	vector<pair<size_t,size_t>> range;
public:
 
	//unitで初期化
	LazySegmentTree(const size_t num) : num(num) {
		for (length = 1,height = 0; length < num; length *= 2, height++);
		node.resize(2 * length, Op.unitNode);
		lazy.resize(2 * length, Op.unitLazy);
		for (int i = 0; i < num; ++i) node[i + length] = Op.unitNode;
		for (int i = length - 1; i >= 0; --i) node[i] = Op.funcNode(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
 
	// //同じinitで初期化
	LazySegmentTree(const size_t num, const typeNode init) : num(num) {
		for (length = 1,height = 0; length < num; length *= 2, height++);
		node.resize(2 * length, Op.unitNode);
		lazy.resize(2 * length, Op.unitLazy);
		for (int i = 0; i < num; ++i) node[i + length] = init;
		for (int i = length - 1; i >= 0; --i) node[i] = Op.funcNode(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
 
	//vectorで初期化
	LazySegmentTree(const vector<typeNode>& vec) : num(vec.size()) {
		for (length = 1,height = 0; length < vec.size(); length *= 2, height++);
		node.resize(2 * length, Op.unitNode);
		lazy.resize(2 * length, Op.unitLazy);
		for (int i = 0; i < vec.size(); ++i) node[i + length] = vec[i];
		for (int i = length - 1; i >= 0; --i) node[i] = Op.funcNode(node[(i<<1)+0],node[(i<<1)+1]);
		range.resize(2 * length);
		for (int i = 0; i < length; ++i) range[i+length] = make_pair(i,i+1);
		for (int i = length - 1; i >= 0; --i) range[i] = make_pair(range[(i<<1)+0].first,range[(i<<1)+1].second);
	}
 
	void propagate(int k) {
		if(lazy[k] == Op.unitLazy) return;
		node[k] = Op.funcMerge(node[k],lazy[k],range[k].second-range[k].first);
		if(k < length) lazy[2*k+0] = Op.funcLazy(lazy[2*k+0],lazy[k]);
		if(k < length) lazy[2*k+1] = Op.funcLazy(lazy[2*k+1],lazy[k]);
		lazy[k] = Op.unitLazy;
    }
 
 
	//update [a,b)
    void update(int a, int b, typeLazy x) {
		int l = a + length, r = b + length - 1;
		for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
		for(r++; l < r; l >>=1, r >>=1) {
			if(l&1) lazy[l] = Op.funcLazy(lazy[l],x), propagate(l),l++;
			if(r&1) --r,lazy[r] = Op.funcLazy(lazy[r],x), propagate(r);
		}
		l = a + length, r = b + length - 1;
		while ((l>>=1),(r>>=1),l) {
			if(lazy[l] == Op.unitLazy) node[l] = Op.funcNode(Op.funcMerge(node[(l<<1)+0],lazy[(l<<1)+0],range[(l<<1)+0].second-range[(l<<1)+0].first),Op.funcMerge(node[(l<<1)+1],lazy[(l<<1)+1],range[(l<<1)+1].second-range[(l<<1)+1].first));
			if(lazy[r] == Op.unitLazy) node[r] = Op.funcNode(Op.funcMerge(node[(r<<1)+0],lazy[(r<<1)+0],range[(r<<1)+0].second-range[(r<<1)+0].first),Op.funcMerge(node[(r<<1)+1],lazy[(r<<1)+1],range[(r<<1)+1].second-range[(r<<1)+1].first));
		}
    }
 
	//get [a,b)
	typeNode get(int a, int b) {
		int l = a + length, r = b + length - 1;
		for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
		typeNode vl = Op.unitNode, vr = Op.unitNode;
		for(r++; l < r; l >>=1, r >>=1) {
			if(l&1) vl = Op.funcNode(vl,Op.funcMerge(node[l],lazy[l],range[l].second-range[l].first)),l++;
			if(r&1) r--,vr = Op.funcNode(Op.funcMerge(node[r],lazy[r],range[r].second-range[r].first),vr);
		}
		return Op.funcNode(vl,vr);
	}
 
	//return [0,length]
	int PrefixBinarySearch(typeNode var) {
		int l = length, r = 2*length - 1;
		for (int i = height; 0 < i; --i) propagate(l >> i), propagate(r >> i);
		if(!Op.funcCheck(node[1],var)) return num;
		typeNode ret = Op.unitNode;
		size_t idx = 2;
		for(; idx < 2*length; idx<<=1){
			if(!Op.funcCheck(Op.funcNode(ret,Op.funcMerge(node[idx],lazy[idx],range[idx].second-range[idx].first)),var)) {
				ret = Op.funcNode(ret,Op.funcMerge(node[idx],lazy[idx],range[idx].second-range[idx].first));
				idx++;
			}
		}
		return min((idx>>1) - length,num);
	}
 
	//range[l,r) return [l,r]
	int BinarySearch(size_t l, size_t r, typeNode var) {
		if (l < 0 || length <= l || r < 0 || length < r) return -1;
		for (int i = height; 0 < i; --i) propagate((l+length) >> i), propagate((r+length-1) >> i);
		typeNode ret = Op.unitNode;
		size_t off = l;
		for(size_t idx = l+length; idx < 2*length && off < r; ){
			if(range[idx].second<=r && !Op.funcCheck(Op.funcNode(ret,Op.funcMerge(node[idx],lazy[idx],range[idx].second-range[idx].first)),var)) {
				ret = Op.funcNode(ret,Op.funcMerge(node[idx],lazy[idx],range[idx].second-range[idx].first));
				off = range[idx++].second;
				if(!(idx&1)) idx >>= 1;			
			}
			else{
				idx <<=1;
			}
		}
		return off;
	}
 
	void print(){
		// cout << "node" << endl;
		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << node[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
		// cout << "lazy" << endl;
		// for(int i = 1,j = 1; i < 2*length; ++i) {
		// 	cout << lazy[i] << " ";
		// 	if(i==((1<<j)-1) && ++j) cout << endl;
		// }
		cout << "vector" << endl;
		cout << "{ " << get(0,1);
		for(int i = 1; i < length; ++i) cout << ", " << get(i,i+1);
		cout << " }" << endl;
	}
};
 
//node:最大　lazy:更新
template<class typeNode, class typeLazy> struct nodeMaxLazyUpdate {
	typeNode unitNode = 0;
	typeLazy unitLazy = 0;
	typeNode funcNode(typeNode l,typeNode r){return r;}
	typeLazy funcLazy(typeLazy l,typeLazy r){return l^r;}
	typeNode funcMerge(typeNode l,typeLazy r,int len){return r!=0?r*len:l;}
    // LazySegmentTree<nodeMaxLazyUpdate<ll,ll>> Seg(N+2,0);
    //verify https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_d
};

int main() {
	ll N, Q; cin >> N >> Q;
	vector<ll> T(Q + 1), X(Q + 1), Y(Q + 1), A(N+1);
	for(int i = 1; i <= Q; ++i) cin >> T[i] >> X[i] >> Y[i];
 
	LazySegmentTree<nodeMaxLazyUpdate<ll,ll>> Seg(N+2,0);
  
	for(int i = 1; i <= N; ++i) cin>> A[i];

	for(int i = 1; i <= Q; ++i) {
		if(T[i]==1){
			Seg.update(X[i], X[i]+1, Y[i]);
		}else{
			cout<< Seg.get(X[i], Y[i]) <<endl;
		}
		Seg.print();
	}
}