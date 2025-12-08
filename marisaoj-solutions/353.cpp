/******************************************************************************
Link: https://marisaoj.com/problem/353
Code: 353
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-14.42.18
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e5;
int n;
vector<int> adj[MAXN + 5];
 
int g[MAXN + 5];
int ans = 0;
string color;
 
void dfs(int u, int prev){
    g[u] = g[prev] + (color[u - 1] == '0' ? 1 : -1);
    if(g[u] > 0) ++ans;
 
    for(int v: adj[u]){
        if(v == prev) continue;
 
        dfs(v, u);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("353.INP","r",stdin);
    //freopen("353.OUT","w",stdout);
    cin >> n >> color;
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