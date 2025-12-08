#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 2000, MAXK = 2000, MAXVAL = 2000;
int last[MAXVAL + 5];
 
const int MOD = 123456789;
int n, k, arr[MAXN + 5];
int dp[MAXN + 5][MAXK + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
        dp[i][0] = 1;
 
        int& prv = last[arr[i]];
        for(int j = 1; j <= k; ++j){
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
            
            if(prv != 0){
                dp[i][j] = (dp[i][j] - dp[prv - 1][j - 1]) % MOD;
            }
        }
 
        prv = i;
    }
 
    int ans = (dp[n][k] + MOD) % MOD;
    cout << ans << '\n';
 
    return 0;
}