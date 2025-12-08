#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int MOD = 1e9 + 7;
int powmod(int a, int b, int m = MOD){
    int res = 1;
    a %= m;
 
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
 
signed main(){
    int n;
    cin >> n;
 
    int lapses = n / 3, extra = n % 3;
    int ans = powmod(36, lapses);
    while(extra--) ans = ans * 3 % MOD;
 
    cout << ans << '\n';
 
    return 0;
}