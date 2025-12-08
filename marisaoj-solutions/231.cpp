/******************************************************************************
Link: https://marisaoj.com/problem/231
Code: 231
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-18-15.12.42
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int MAXN = 1e5, MAXK = 100;
int n, k;
vector<int> adj[MAXN + 5];
 
int dp[MAXN + 5][MAXK + 5];
int ans = 0;
void dfs(int u, int prev){
    dp[u][0] = 1;
    for(int v: adj[u]){
        if(v == prev) continue;
 
        dfs(v, u);
 
        for(int j = 0; j < k; ++j){
            ans += (dp[u][j]) * dp[v][k - j - 1];
        }
        for(int j = 1; j <= k; ++j){
            dp[u][j] += dp[v][j - 1];
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("231.INP","r",stdin);
    //freopen("231.OUT","w",stdout);
    cin >> n >> k;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;
 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    dfs(1, 0);
 
    cout << ans << '\n';
 
    return 0;
}