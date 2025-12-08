/******************************************************************************
Link: https://marisaoj.com/problem/251
Code: 251
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-13.07.29
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int MAXN = 1e5, MAXM = 2e5;
int n, m;
bool visited[MAXN + 5];
int scc_id[MAXN + 5], scc_count = 0;
vector<int> adj[MAXN + 5], rev_adj[MAXN + 5];
vector<int> dag[MAXN + 5];
int w[MAXN + 5], scc_w[MAXN + 5];
 
vector<int> order;
void dfs1(int u){
    if(visited[u]) return;
    visited[u] = true;
    for(int v: adj[u]) dfs1(v);
    order.push_back(u);
}
 
void dfs2(int u){
    if(scc_id[u] != 0) return;
    scc_id[u] = scc_count;
    for(int v: rev_adj[u]) dfs2(v);
}
 
void scc(){
    for(int i = 1; i <= n; ++i)
        if(!visited[i]) dfs1(i);
 
    reverse(order.begin(), order.end());
    for(int u: order){
        if(scc_id[u] == 0){
            ++scc_count;
            dfs2(u);
        }
    }
}
 
void compress(){
    for(int u = 1; u <= n; ++u){
        scc_w[scc_id[u]] += w[u];
        for(int v: adj[u]){
            if(scc_id[u] != scc_id[v]){
                dag[scc_id[u]].push_back(scc_id[v]);
            }
        }
    }
 
    for(int i = 1; i <= scc_count; ++i){
        sort(dag[i].begin(), dag[i].end());
        dag[i].erase(unique(dag[i].begin(), dag[i].end()), dag[i].end());
    }
}
 
vector<int> topo;
void topological_sort(int u){
    if(visited[u]) return;
    visited[u] = true;
 
    for(int v: dag[u]){
        topological_sort(v);
    }
    topo.push_back(u);
}
 
void solve(){
    fill(visited + 1, visited + n + 1, false);
    for(int i = 1; i <= scc_count; ++i){
        if(!visited[i]) topological_sort(i);
    }
 
    reverse(begin(topo), end(topo));
    vector<int> dp(scc_count + 1, 0);
 
    for(int u = 1; u <= scc_count; ++u){
        dp[u] = max(dp[u], scc_w[u]);
        for(int v: dag[u]){
            dp[v] = max(dp[v], dp[u] + scc_w[v]);
        }
    }
 
    int ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> w[i];
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;
 
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }
 
    scc();
    compress();
 
    solve();
 
    return 0;
}