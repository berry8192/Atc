#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, k, head=0, fig=1, cnt=0;
	vector<int> v;
	set<int> st;

	cin>> n >> k;
	v.resize(n);

	rep(i, n) cin >> v[i];

	while(1){
		if(v[head]==fig){
			st.insert(v[head]);
			head++;
			// cout<< "add head: " << head <<endl;
			fig=1;
			while(st.find(fig)!=st.end()) fig++;
			// cout<< "new fig: " << fig <<endl;
			if(head==n){
				// cout<< "end" <<endl;
				if(k<=cnt+n){
					// cout<< "match" <<endl;
					PV(v);
					return 0;
				}else{
					break;
					cnt+=n;
					fig++;
					cnt++;
					if(fig==n){
						fig=1;
						head--;
					}
				}
			}
			continue;
		}
		if(cnt==k){
			int idx;
			rep(i, n){
				if(v[i]==fig) idx=i;
			}

			vector<int> w=v;
			// cout<< head SP << fig <<endl;
			int l=head, r=idx;
			// reverse(w.begin()+head, w.begin()+idx);
			while(l<r){
				swap(w[l], w[r]);
				l++;
				r--;
			}
			// cout<< "cnt: " << cnt <<endl;
			PV(w);
			return 0;
		}
		cnt++;
		fig++;
		while(st.find(fig)!=st.end()) fig++;
		// if(fig==n){
		// 	fig=1;
		// 	head--;
		// }
		// if(cnt==k) return 0;
	}

	head=n-1;
	fig=v[n-1];	
	while(1){
		fig++;
		while(st.find(fig)!=st.end()) fig++;
		if(fig==n+1){
			st.erase(v[head]);
			head--;
			fig=v[head];
			continue;
		}
		cnt++;
		if(1||cnt==k){
			int idx;
			rep(i, n){
				if(v[i]==fig) idx=i;
			}

			vector<int> w=v;
			// cout<< head SP << fig <<endl;
			int l=head, r=idx;
			// reverse(w.begin()+head, w.begin()+idx);
			while(l<r){
				swap(w[l], w[r]);
				l++;
				r--;
			}
			cout<< "cnt: " << cnt <<endl;
			PV(w);
			// return 0;
		}
		// if(cnt==k) return 0;
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}