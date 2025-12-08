#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 5000, MAXK = 5000;
int arr[MAXN + 5], n, k;
 
int dp[2][MAXK + 5][2];
void solve(){
    for(int i = 1; i <= n; ++i){
        dp[1][0][0] = dp[0][0][0] + arr[i];
        for(int j = 1; j <= k; ++j){
            dp[1][j][0] = max(dp[0][j][1], dp[0][j][0]) + arr[i];
            dp[1][j][1] = max(dp[0][j - 1][0], dp[0][j][1]);
        }
 
        memcpy(dp[0], dp[1], sizeof(dp[0]));
    }
 
    int ans = -1e18;
    for(int j = 0; j <= k; ++j){
        ans = max({ans, dp[1][j][0], dp[1][j][1]});
    }
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
 
    solve();
 
    return 0;
}