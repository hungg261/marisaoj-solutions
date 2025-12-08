#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5;
int t[MAXN + 5], r[MAXN + 5], n;
int dp[MAXN + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> t[i];
    for(int i = 2; i <= n; ++i) cin >> r[i];
 
    dp[1] = t[1];
    for(int i = 2; i <= n; ++i){
        dp[i] = min(dp[i - 2] + r[i], dp[i - 1] + t[i]);
    }
 
    cout << dp[n] << '\n';
 
    return 0;
}