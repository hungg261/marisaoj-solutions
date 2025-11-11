#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1000;
int dp[MAXN + 5][MAXN + 5], n;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            int cur; cin >> cur;

            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + cur;
        }
    }

    cout << dp[n][n] << '\n';

    return 0;
}