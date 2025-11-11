#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e6, MAXVAL = 1e6;
int last[MAXVAL + 5];

const int MOD = 123456789;
int n, arr[MAXN + 5];
int dp[MAXN + 5];

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        dp[i] = dp[i - 1] * 2 % MOD;

        int& j = last[arr[i]];
        if(j != 0){
            dp[i] -= dp[j - 1];
            dp[i] %= MOD;
        }

        j = i;
    }

    int ans = (dp[n] - 1 + MOD) % MOD;
    cout << ans << '\n';

    return 0;
}