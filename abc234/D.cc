#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;
class fenwick_tree_set {
    const int n;
    int cnt;
    vector<int> data;
    int find(int p) const {
        int res = 0;
        while (p > 0) {
            res += data[p];
            p -= p & -p;
        }
        return res;
    }
    void add(int p, int x) {
        ++p;
        while (p <= n) {
            data[p] += x;
            p += p & -p;
        }
    }
public:
    fenwick_tree_set(int maxi)
        : n(maxi + 1), cnt(0), data(n + 1) {}
    int size() const {
        return cnt;
    }
    int count(int val) const {
        assert(0 <= val && val < n);
        return find(val + 1) - find(val);
    }
    void insert(int val) {
        assert(0 <= val && val < n);
        add(val, 1);
        cnt += 1;
    }
    void erase(int val) {
        assert(0 <= val && val < n);
        assert(0 < count(val));
        add(val, -1);
        cnt -= 1;
    }
    int kth_element(int k) const {
        assert(0 <= k && k < cnt);
        int p = 1 << (32 - __builtin_clz(n)), res = 0;
        while (p >>= 1) {
            if (res + p <= n && data[res + p] <= k) {
                k -= data[res + p];
                res += p;
            }
        }
        return res;
    }
};

int main(){

	int n, k, tmp;
	vector<int> ans;

	cin>> n >> k;
	fenwick_tree_set fts(n);
	fts.insert(0);

	rep(i, n){
		cin >> tmp;
		fts.insert(tmp);
		// cout<< "size " << fts.size() <<endl;
		// rep(j, fts.size()) cout<< fts.kth_element(j) SP;
		// cout<<endl;
		if(i>=k-1){
			ans.push_back(fts.kth_element(fts.size()-k));
		}
	}

	rep(i, ans.size()) cout<< ans[i] <<endl;
 
	return 0;
}