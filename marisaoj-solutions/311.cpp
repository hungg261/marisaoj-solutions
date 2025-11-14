#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 2e5, MAXQ = 1e9, MAXK = __lg(MAXQ) + 1;
int n, q;
int parent[MAXN + 5];
 
int table[MAXK + 5][MAXN + 5];
void compute(){
    for(int i = 1; i <= n; ++i){
        table[0][i] = parent[i];
    }
 
    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i <= n; ++i){
            table[k][i] = table[k - 1][table[k - 1][i]];
        }
    }
}
 
int query(int pos, int steps){
    for(int k = 0; k <= MAXK; ++k){
        if(steps >> k & 1) pos = table[k][pos];
    }
    return pos;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> parent[i];
    }
 
    compute();
    while(q--){
        int x, s;
        cin >> x >> s;
 
        cout << query(x, s) << '\n';
    }
 
    return 0;
}