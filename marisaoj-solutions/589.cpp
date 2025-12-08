#include<bits/stdc++.h>
// #define int long long
using namespace std;
 
const int MAXN = 500, MAXVAL = 1000,
        MAXSUM = MAXN * MAXVAL, OFFSET = MAXSUM;
pair<int, int> cows[MAXN + 5];
int n;
 
int dp[2][MAXSUM * 2 + 5];
int f(int val){ return val + OFFSET + 1; }
 
void solve(){
    memset(dp, -0x3f, sizeof dp);
    const int INF = dp[0][0];
 
    dp[0][f(0)] = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = -MAXSUM; j <= MAXSUM; ++j){
            if(j - cows[i].first >= -MAXVAL){
                dp[1][f(j)] = dp[0][f(j - cows[i].first)] + cows[i].second;
            }
 
            dp[1][f(j)] = max(
                dp[1][f(j)],
                dp[0][f(j)]
            );
        }
 
        memcpy(dp[0], dp[1], sizeof dp[0]);
    }
 
    // for(int i = 0; i <= n; ++i){
    //     for(int j = 0; j <= 10; ++j){
    //         cerr << dp[i][f(j)] << ' ';
    //     }
    //     cerr << '\n';
    // }
 
    int ans = -1e18;
    for(int IQ = 0; IQ <= MAXSUM; ++IQ){
        if(dp[1][f(IQ)] != INF)
        ans = max(ans, IQ + dp[1][f(IQ)]);
    }
 
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> cows[i].first >> cows[i].second;
    }
 
    solve();
 
    return 0;
}