#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5;
int A[MAXN + 5], B[MAXN + 5], n;
int dp[MAXN + 5][2];

void solve(){
    dp[1][0] = A[1];
    dp[1][1] = B[1];

    // dp[2][0] = max(A[1] + A[2], B[1] + A[2]);
    // dp[2][1] = max(B[1] + B[2], A[1] + B[2]);

    for(int i = 2; i <= n; ++i){
        dp[i][0] = max(dp[i - 1][1] + A[i], dp[i - 2][1] + (A[i - 1] + A[i]));
        dp[i][1] = max(dp[i - 1][0] + B[i], dp[i - 2][0] + (B[i - 1] + B[i]));
    }

    // for(int i = 1; i <= n; ++i){
    //     cerr << dp[i][0] << ' ' << dp[i][1] << '\n';
    // }

    int ans = max(dp[n][0], dp[n][1]);
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