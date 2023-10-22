#include <bits/stdc++.h>

using namespace std;

int main(){

    std::random_device seed_gen;
    std::default_random_engine engine(seed_gen());

    int n;
    cin>> n;
    vector<int> v(n);
    exponential_distribution<> dist(0.00001);
    for(int i=0;i<n;i++) v[i]=max(1, int(round(dist(engine))));
    sort(v.begin(), v.end());
    for(int i=0;i<n;i++) cout<< v[i] <<endl;

    return 0;
}

