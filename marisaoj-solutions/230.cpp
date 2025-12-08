/******************************************************************************
Link: https://marisaoj.com/problem/230
Code: 230
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-18-07.43.34
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n;
vector<int> adj[MAXN + 5];

int dp[MAXN + 5][2];

void dfs(int u, int prev){
    dp[u][0] = 0;
    dp[u][1] = 1;
    for(int v: adj[u]){
        if(v == prev) continue;
        dfs(v, u);

        dp[u][0] += max(dp[v][1], dp[v][0]);
        dp[u][1] += dp[v][0];
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("230.INP","r",stdin);
    //freopen("230.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << '\n';

    return 0;
}