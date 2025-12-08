#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int MAXN = 1e6;
const int MOD = 1e9 + 7;
int fact[MAXN + 5];
 
void compute(){
    fact[0] = 1;
    for(int i = 1; i <= MAXN; ++i){
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
 
int inv(int b, int mod){
    return powmod(b, mod - 2, mod);
}
 
int C(int n, int k){
    if(n < k) return 0;
    return fact[n] * inv(fact[k] * fact[n - k] % MOD, MOD) % MOD;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    compute();
    
    int n, k, p;
    cin >> n >> k >> p;
    
    cout << C(n - p * k + k - 1, k - 1) << '\n';
    
    return 0;
}