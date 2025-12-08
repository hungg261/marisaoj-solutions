#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1000, MAXK = 1e5;
int c[MAXN + 5], n, k;
 
int dp[MAXK + 5];
void solve(){
    sort(c + 1, c + n + 1);
 
    dp[0] = 0;
    for(int v = 1; v <= k; ++v){
        dp[v] = 1e9;
        for(int i = 1; i <= n; ++i){
            if(v >= c[i]){
                dp[v] = min(dp[v], dp[v - c[i]] + 1);
            }
            else break;
        }
    }
 
    cout << (dp[k] == 1000000000 ? -1 : dp[k]) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> c[i];
    }
 
    solve();
 
    return 0;
}