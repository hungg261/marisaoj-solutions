/******************************************************************************
Link: https://marisaoj.com/problem/232
Code: 232
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-18-07.58.51
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5;
const int MOD = 1e9 + 7;
int n;
vector<int> adj[MAXN + 5];

int dp[MAXN + 5][3];
void dfs(int u, int prev){
    dp[u][0] = 1;
    dp[u][1] = 1;
    dp[u][2] = 1;

    for(int v: adj[u]){
        if(v == prev) continue;
        dfs(v, u);

        dp[u][0] = dp[u][0] * (dp[v][1] + dp[v][2]) % MOD;
        dp[u][1] = dp[u][1] * (dp[v][0] + dp[v][2]) % MOD;
        dp[u][2] = dp[u][2] * (dp[v][0] + dp[v][1]) % MOD;
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("232.INP","r",stdin);
    //freopen("232.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    int ans = dp[1][0] + dp[1][1] + dp[1][2];
    ans %= MOD;

    cout << ans << '\n';

    return 0;
}