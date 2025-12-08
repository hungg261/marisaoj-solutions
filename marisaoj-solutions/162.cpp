#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e6;
const int MOD = 1e9 + 7;
int arr[MAXN + 5], n;
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

int temp[MAXN + 5];
void compress(){
    for(int i = 1; i <= n; ++i) temp[i] = arr[i];
    sort(temp + 1, temp + n + 1);
    
    for(int i = 1; i <= n; ++i){
        arr[i] = lower_bound(temp + 1, temp + n + 1, arr[i]) - temp;
    }
}

int freq[MAXN + 5];
void solve(){
    compute();
    compress();
    for(int i = 1; i <= n; ++i){
        ++freq[arr[i]];
    }
    
    int ans = fact[n];
    for(int i = 1; i <= n; ++i){
        ans = ans * inv(fact[freq[i]], MOD) % MOD;
    }
    
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    
    solve();
    
    return 0;
}