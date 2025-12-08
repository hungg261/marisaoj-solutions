/******************************************************************************
Link: https://marisaoj.com/problem/229
Code: 229
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-18-08.23.13
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5;
int n, c[MAXN + 5];
vector<int> adj[MAXN + 5];
 
int dp[MAXN + 5], best[MAXN + 5];
void dfs(int u, int prev){
    dp[u] = c[u];
 
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int v: adj[u]){
        if(v == prev) continue;
 
        dfs(v, u);
 
        dp[u] = max(dp[u], c[u] + dp[v]);
 
        pq.push(dp[v]);
        if(pq.size() > 2) pq.pop();
    }
 
    while(pq.size() < 2) pq.push(0);
 
    int v1 = pq.top(); pq.pop();
    int v2 = pq.top(); pq.pop();
    best[u] = max({c[u], c[u] + v1, c[u] + v2, c[u] + v1 + v2});
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("229.INP","r",stdin);
    //freopen("229.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> c[i];
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;
 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    dfs(1, 0);
    int ans = *max_element(best + 1, best + n + 1);
 
    cout << ans << '\n';
 
    return 0;
}