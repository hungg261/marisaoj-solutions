#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1000;
int A[MAXN + 5], n, k;
int dp[MAXN + 5][MAXN + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> A[i];
    }
 
    const int MOD = 1e9 + 7;
 
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
        dp[i][0] = 1;
        for(int j = 1; j <= k; ++j){
            (dp[i][j] += dp[i - 1][j - 1] * A[i] + dp[i - 1][j]) %= MOD;
        }
    }
 
    // for(int i = 0; i <= n; ++i){
    //     for(int j = 0; j <= k; ++j){
    //         cerr << dp[i][j] << ' ';
    //     }
    //     cerr << '\n';
    // }
 
    cout << dp[n][k] << '\n';
 
    return 0;
}