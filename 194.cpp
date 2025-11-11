#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5, MAXK = __lg(MAXN) + 1;
int parent[MAXN + 5], h[MAXN + 5], n, q;
int table[MAXN + 5][MAXK + 5];
vector<int> adj[MAXN + 5];

void compute(){
    for(int i = 1; i <= n; ++i){
        table[i][0] = parent[i];
    }

    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i <= n; ++i){
            table[i][k] = table[table[i][k - 1]][k - 1];
        }
    }
}

void jump(int& pos, int steps){
    int bit = 0;
    while(steps > 0){
        if(steps & 1) pos = table[pos][bit];

        ++bit;
        steps >>= 1;
    }
}

int lca(int u, int v){
    if(h[u] > h[v]) swap(u, v);
    jump(v, h[v] - h[u]);

    if(u == v) return u;

    for(int bit = MAXK; bit >= 0; --bit){
        if(table[u][bit] != table[v][bit]){
            u = table[u][bit];
            v = table[v][bit];
        }
    }

    return table[u][0];
}

void dfs(int u, int prev){
    for(int v: adj[u]){
        if(v == prev) continue;

        h[v] = h[u] + 1;
        parent[v] = u;
        dfs(v, u);
    }
}

int weight[MAXN + 5];
void propagate(int u, int prev){
    for(int v: adj[u]){
        if(v == prev) continue;

        propagate(v, u);
        weight[u] += weight[v];
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    parent[1] = 0;
    dfs(1, 0);
    compute();

    for(int i = 1; i <= q; ++i){
        int u, v, w;
        cin >> u >> v >> w;

        weight[u] += w;
        weight[v] += w;
        
        int LCA = lca(u, v);
        weight[LCA] -= w;
        weight[table[LCA][0]] -= w;
    }

    propagate(1, 0);
    for(int i = 1; i <= n; ++i){
        cout << weight[i] << ' ';
    }

    return 0;
}