#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 5000;
int dp[MAXN + 5][MAXN + 5], A[MAXN + 5], n;

void solve(){
    for(int i = 1; i <= n; ++i){
        dp[i][i] = n & 1 ? A[i] : -A[i];
    }

    for(int len = 2; len <= n; ++len){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;

            if((n - len + 1) & 1){
                dp[i][j] = max(A[i] + dp[i + 1][j], dp[i][j - 1] + A[j]);
            }
            else{
                dp[i][j] = min(- A[i] + dp[i + 1][j], dp[i][j - 1] - A[j]);
            }
        }
    }

    cout << dp[1][n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> A[i];
    }

    solve();

    return 0;
}