/******************************************************************************
Link: https://marisaoj.com/problem/250
Code: 250
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-12.52.36
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5;
int c[MAXN + 5];
vector<int> adj[MAXN + 5], rev_adj[MAXN + 5];
int n, m;

vector<int> topo1;
bool mark1[MAXN + 5];
void dfs1(int u){
    if(mark1[u]) return;
    mark1[u] = true;

    for(int v: adj[u]){
        dfs1(v);
    }
    topo1.push_back(u);
}

int sccs_id[MAXN + 5], scc_cnt = 0, sccs_cost[MAXN + 5];
void kosaraju(int u){
    if(sccs_id[u] != 0) return;
    sccs_id[u] = scc_cnt;
    sccs_cost[scc_cnt] = min(sccs_cost[scc_cnt], c[u]);

    for(int v: rev_adj[u]){
        kosaraju(v);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("250.INP","r",stdin);
    //freopen("250.OUT","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        cin >> c[i];
    }
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) dfs1(i);
    reverse(begin(topo1), end(topo1));
    for(int u: topo1){
        if(!sccs_id[u]){
            ++scc_cnt;
            sccs_cost[scc_cnt] = c[u];
            kosaraju(u);
        }
    }

    int ans = 0;
    for(int i = 1; i <= scc_cnt; ++i){
        ans += sccs_cost[i];
    }
    cout << ans << '\n';

    return 0;
}
