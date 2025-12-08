#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int MOD = 1e9 + 7;
const int MAXN = 20, MAXMASK = 1 << MAXN;
int n;
int w[MAXN + 5][MAXN + 5];
 
int dp[MAXMASK + 1][MAXN + 1];
void solve(){
    memset(dp, 0x3f, sizeof dp);
    for(int i = 0; i < 1; ++i){
        dp[1 << i][i] = 0;
    }
 
    for(int mask = 0; mask < (1 << n); ++mask){
        if(__builtin_popcount(mask) == 1) continue;
 
        for(int i = 0; i < n; ++i){
            if(mask >> i & 1){
                for(int j = 0; j < n; ++j){
                    dp[mask][i] = min(dp[mask][i], dp[mask ^ (1 << i)][j] + w[j][i]);
                }
            }
        }
    }
 
    int full = (1 << n) - 1;
    int ans = LLONG_MAX;
    for(int i = 0; i < n; ++i){
        ans = min(ans, dp[full][i] + w[i][0]);
    }
 
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> w[i][j];
        }
    }
 
    solve();
 
    return 0;
}