#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5;
const int MOD = 1e9 + 7;
int arr[MAXN + 5], n, k;
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
 
int inv(int b, int mod){ return powmod(b, mod - 2, mod); }
 
int C(int n, int k){
    return fact[n] * inv(fact[k] * fact[n - k] % MOD, MOD) % MOD;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    sort(arr + 1, arr + n + 1);
    
    compute();
    int ans = 0;
    for(int i = k; i <= n; ++i){
        ans = (ans + arr[i] * C(i - 1, k - 1)) % MOD;
    }
    
    cout << ans << '\n';
    
    return 0;
}