#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> A(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i];
    }
    // sort(A.begin(), A.end(), greater<int>());

    vector<string> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }

    vector<int> sco(N);

    for (int i = 0; i < N; i++) {
    	for (int j = 0; j < M; j++) {
    		if(S[i][j]=='o') sco[i]+=A[j];
        }
    }

    
    for (int i = 0; i < N; i++) {
    	int tsco=sco[i];
    	int ans=0;
    	for (int j = 0; j < M; j++) {
    		int flg=1;
    		for(int k=0;k<N;k++){
    			if(i==k) continue;
    			if(sco[k]+k>=tsco+i) flg=0;
    		}
        	if(!flg){
        		int ma=0;
        		int mai;
        		for(int l=0;l<M;l++){
        			if (S[i][l]=='x' && ma<A[l]){
        				ma=A[l];
        				mai=l;
        			}
        		}
        		tsco+=A[mai];
        		ans++;
        		S[i][mai]='o';
        	}
        }
        cout<< ans <<endl;
    }

    return 0;
}
