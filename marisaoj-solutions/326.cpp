/******************************************************************************
Link: https://marisaoj.com/problem/326
Code: 326
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-07-23.47.57
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e5;
int n, h[MAXN + 5];
vector<int> adj[MAXN + 5];
 
void dfs(int u, int prev){
    for(int v: adj[u]){
        if(v == prev) continue;
 
        h[v] = h[u] + 1;
        dfs(v, u);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("326.INP","r",stdin);
    //freopen("326.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;
 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    dfs(1, 0);
    for(int i = 1; i <= n; ++i) cout << h[i] << ' '; cout << '\n';
 
    return 0;
}