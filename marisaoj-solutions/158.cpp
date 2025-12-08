#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1000, MAXK = 1e5;
int c[MAXN + 5], n, k;

int dp[MAXK + 5];
void solve(){
    sort(c + 1, c + n + 1);

    dp[0] = 1;
    for(int i = 1; i <= n; ++i){
        for(int v = c[i]; v <= k; ++v){
            (dp[v] += dp[v - c[i]]) %= MOD;
        }
    }

    cout << (dp[k]) << '\n';
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