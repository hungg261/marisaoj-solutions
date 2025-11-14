#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 500;
int val[MAXN + 5][MAXN + 5], dp[MAXN + 5][MAXN + 5];

int n;
int arr[MAXN + 5];

void solve(){
    memset(val, -1, sizeof val);
    memset(dp, 0x3f, sizeof dp);
    for(int i = 1; i <= n; ++i){
        dp[i][i] = 1;
        val[i][i] = arr[i];
    }

    for(int len = 2; len <= n; ++len){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;

            for(int k = i; k < j; ++k){
                if(val[i][k] != - 1 && val[i][k] == val[k + 1][j]){
                    dp[i][j] = 1;
                    val[i][j] = val[i][k] + 1;
                }
                else dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    cout << dp[1][n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> arr[i];

    solve();

    return 0;
}