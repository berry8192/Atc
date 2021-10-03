#include <atcoder/lazysegtree>
#include <cstdio>
#include <vector>

using namespace std;
using namespace atcoder;

using F = bool;

long long op(long long a, long long b) { return (a+b)%998244353; }

long long e() { return 0; }

long long mapping(F l, long long  r) { return long long({r.a * l.a + r.size * l.b, r.size};) }
long long target;

bool f(long long v) { return v < target; }

long long main() {
    long long n, tmp;
    scanf("%d", &n);
    vector<long long> a(n);
    for (long long i = 0; i < n; i++) {
        scanf("%d", &(a[i]));
    }

    lazy_segtree<long long, op, e, F, mapping, composition, id> seg(n+1);
	long long mod=998244353;
	
	vector<long long> ten(1);
    ten[0]=1;
  	for(long long i=0;i<n;i++) ten.push_back((ten[i]*2)%mod);

    for (long long i = 0; i < n; i++) {
		tmp=seg.prod(1, a[i]+1);

		seg.set(a[i], seg.get(a[i])+1);
		
        prlong longf("%d\n", tmp);
    }
}
