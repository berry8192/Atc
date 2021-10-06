#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){
	//https://atcoder.jp/contests/abc170/tasks/abc170_e

	int n, q, c, d, mi=imax;
	vector< multiset<int> > mst;
	//各幼稚園での園児のレートをマルチセットで保持
	vector<int> r, k, ma;
	//園児のレートと所属幼稚園をr, kに保持
	//各幼稚園の最高レートをmaに保持
	multiset<int> mm;
	//mmでmaのminを計算

	cin>> n >> q;
	r.resize(n+1);
	k.resize(n+1);
	ma.resize(200010);
	mst.resize(200010);

	//n人の園児のレートと所属を受け取る
	//マルチセットにもブチ込む
	for(int i=1;i<n+1;i++){
		cin>> r[i] >> k[i];
		mst[k[i]].insert(r[i]);
	}

	//各幼稚園の最高戦力を得てmaにメモ
	//end()とbegin()が違う <=> size()>0がなのでend()のいっこ前のイテレータが取れる
	for(int i=1;i<=200000;i++){
		auto itr=mst[i].end();
		if(itr!=mst[i].begin()) itr--;
		ma[i]=*itr;
		//cout<< ma[i] <<endl;
		mm.insert(*itr);
	}

	//全要素表示
	/*rep(i, 200001){
		if(!mst[i].empty()) cout<< "y" << i << "  ";
		else continue;
		for(auto itr = mst[i].begin(); itr != mst[i].end(); ++itr) {
        	cout << *itr << " ";      // イテレータの指す先のデータを表示
    	}
		cout<< endl;
	}
	cout<< ma[1] << " " << ma[2] << " " << ma[3] <<endl;*/

	rep(i, q) {
		//cの幼児（所属はk[c]）がdに転園
		cin>> c >> d;

		//cのいた幼稚園からcのレートを削除
		auto itr=mst[k[c]].find(r[c]);
		mst[k[c]].erase(itr);

		//mmからも削除
		auto itr4=mm.find(ma[k[c]]);
		mm.erase(itr4);

		//cのいた幼稚園のmaを更新
		auto itr2=mst[k[c]].end();
		if(itr2!=mst[k[c]].begin()){
			itr2--;
			ma[k[c]]=*itr2;
			//mi=min(mi, ma[k[c]]);
		}else{
			ma[k[c]]=0;
		}

		//mmに追加
		mm.insert(ma[k[c]]);

		//cの所属幼稚園を変更
		k[c]=d;

		//転園先にcのレートを追加
		mst[d].insert(r[c]);

		//mmから一旦消去
		auto itr5=mm.find(ma[d]);
		mm.erase(itr5);

		//転園先のmaを更新
		auto itr3=mst[d].end();
		itr3--;
		ma[d]=*itr3;
		//mi=min(mi, ma[d]);

		//mmに追加
		mm.insert(ma[d]);

		auto itr6=mm.upper_bound(0);
		cout<< *itr6 <<endl;
		
	}
 
	return 0;
}