#include <bits/stdc++.h>

using namespace std;

int main(){

	int x, y, a, b, c;
	vector<int> p, q, r, v;
	long long int ps=0, qs=0, ans = 0;

	cin>> x >> y >> a >> b >> c;
	p.resize(a);
	q.resize(b);
	r.resize(c);
	for (int i = 0;i<a;i++) cin >> p[i];
	for (int i = 0;i<b;i++) cin >> q[i];
	for (int i = 0;i<c;i++) cin >> r[i];

	sort(p.begin(), p.end(), greater<int>());
	sort(q.begin(), q.end(), greater<int>());
	sort(r.begin(), r.end(), greater<int>());

	for (int i = 0;i < x;i++) v.emplace_back(p[i]);
	for (int i = 0;i < y;i++) v.emplace_back(q[i]);
	for (int i = 0;i < min(c, x + y);i++) v.emplace_back(r[i]);

	sort(v.begin(), v.end(), greater<int>());

	for (int i = 0;i < x+y;i++) ans+=v[i];

	cout << ans << endl;

	return 0;
}
