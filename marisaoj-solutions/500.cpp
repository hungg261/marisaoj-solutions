#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MOD = 1e9 + 7;
const int MAXN = 1e5;
int fact[MAXN + 5] = {1};
int n, m;
 
void compute(){
    for(int i = 1; i <= n; ++i){
        fact[i] = fact[i - 1] * i % MOD;
    }
}
 
int powmod(int a, int b, int m){
    int res = 1;
    a %= m;
 
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
int C(int n, int k){
    return fact[n] * powmod(fact[k] * fact[n - k], MOD - 2, MOD) % MOD;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    compute();
 
    cout << C(n - m + 1, m) << '\n';
 
    return 0;
}