#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 500;
int arr[MAXN + 5], pre[MAXN + 5], n;

int dp[MAXN + 5][MAXN + 5];
void solve(){
    for(int len = 2; len <= n; ++len){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;

            dp[i][j] = 1e18;
            for(int k = i; k < j; ++k){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + (pre[j] - pre[i - 1]));
            }
        }
    }

    cout << dp[1][n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }

    solve();
    return 0;
}