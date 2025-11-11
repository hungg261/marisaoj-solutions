#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 2e5;
int dp[MAXN + 5], n, k;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    
    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        dp[i] = dp[i - 1] + dp[max(0LL, i - k)];
        dp[i] %= MOD;
    }

    cout << dp[n] << '\n';

    return 0;
}