#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 5000;
int A[MAXN + 5], B[MAXN + 5], dp[MAXN + 5][MAXN + 5], n;

void solve(){
    memset(dp, -0x3f, sizeof dp);
    int ans = -1e18;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            dp[i][j] = max({A[i] * B[j], dp[i - 1][j - 1] + A[i] * B[j]});
            ans = max(ans, dp[i][j]);
        }
    }
    
    // for(int i = 1; i <= n; ++i){
    //     for(int j = 1; j <= n; ++j){
    //         cerr << dp[i][j] << ' ';
    //     }
    //     cerr << '\n';
    // }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> A[i];
    for(int i = 1; i <= n; ++i) cin >> B[i];

    solve();

    return 0;
}