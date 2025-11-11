#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5, MAXK = __lg(MAXN) + 1;
int parent[MAXN + 5], h[MAXN + 5], w_to[MAXN + 5], n, q;
int table[MAXN + 5][MAXK + 5], maxweight[MAXN + 5][MAXK + 5];
vector<pair<int, int>> adj[MAXN + 5];

void compute(){
    for(int i = 1; i <= n; ++i){
        table[i][0] = parent[i];
        maxweight[i][0] = w_to[i];
    }

    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i <= n; ++i){
            table[i][k] = table[table[i][k - 1]][k - 1];
            maxweight[i][k] = max(maxweight[i][k - 1], maxweight[table[i][k - 1]][k - 1]);
        }
    }
}

int get_maxW_jump(int pos, int steps){
    int bit = 0;
    int res = -1e18;
    while(steps > 0){
        if(steps & 1){
            res = max(res, maxweight[pos][bit]);
            pos = table[pos][bit];
        }

        ++bit;
        steps >>= 1;
    }

    return res;
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
    for(const auto& p: adj[u]){
        int v, w; tie(w, v) = p;
        if(v == prev) continue;

        h[v] = h[u] + 1;
        parent[v] = u;
        w_to[v] = w;
        dfs(v, u);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b, w;
        cin >> a >> b >> w;

        adj[a].push_back({w, b});
        adj[b].push_back({w, a});
    }

    parent[1] = 1;
    w_to[1] = 0;
    dfs(1, -1);
    compute();

    for(int i = 1; i <= q; ++i){
        int u, v;
        cin >> u >> v;

        int LCA = lca(u, v);
        int ans = max(get_maxW_jump(u, h[u] - h[LCA]), get_maxW_jump(v, h[v] - h[LCA]));
        cout << ans << '\n';
    }

    return 0;
}