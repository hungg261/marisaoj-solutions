#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
    int n;
    cin >> n;

    const int MOD = 1e9 + 7;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= 3 && i - j >= 0; ++j){
            (dp[i] += dp[i - j]) %= MOD;
        }
    }

    cout << dp[n] << '\n';
    return 0;
}