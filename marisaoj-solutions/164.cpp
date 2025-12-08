/******************************************************************************
Link: https://marisaoj.com/problem/164
Code: 164
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-17-00.37.23
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
int binpow(int a, int b, int m){
    a %= m;
 
    int res = 1;
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
const int MOD = 1e9 + 7;
const int MAXN = 1e6;
int q;
 
int fact[MAXN + 5];
void compute(){
    fact[0] = 1;
    for(int i = 1; i <= MAXN; ++i){
        fact[i] = fact[i - 1] * i % MOD;
    }
}
 
int C(int n, int k){
    return fact[n] * binpow(fact[k] * fact[n - k], MOD - 2, MOD) % MOD;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("164.INP","r",stdin);
    //freopen("164.OUT","w",stdout);
    cin >> q;
    compute();
 
    while(q--){
        int n, k;
        cin >> n >> k;
 
        cout << C(n, k) << '\n';
    }
 
    return 0;
}