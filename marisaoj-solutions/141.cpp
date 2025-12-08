#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 100, MAXVAL = 1e5;
int n, S;
int w[MAXN + 5], v[MAXN + 5];
 
int dp[MAXN + 5][MAXVAL + 5];
void solve(){
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= S; ++j){
            dp[i][j] = dp[i - 1][j];
            if(j >= w[i]){
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
            }
        }
    }
 
    cout << dp[n][S] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> S;
    for(int i = 1; i <= n; ++i){
        cin >> w[i] >> v[i];
    }
 
    solve();
 
    return 0;
}