#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int INF = 1e18;
const int MAXN = 3e5, MAXK = __lg(MAXN) + 1;
int up[MAXN + 5][MAXK + 5], h[MAXN + 5], n, m;
vector<pair<int, int>> mst_adj[MAXN + 5];
 
struct MaxWeights{
    int first, second;
 
    MaxWeights(){ first = second = -INF; }
    MaxWeights(int a, int b){
        first = second = -INF;
        push(a); push(b);
    }
 
    void push(int w){
        if(w > first){
            second = first;
            first = w;
        }
        else if(w > second && w != first){
            second = w;
        }
    }
} maxw[MAXN + 5][MAXK + 5];
 
struct Edge{
    int u, v, w;
 
    bool operator < (const Edge& other){
        return this->w < other.w;
    }
};
vector<Edge> edges;
 
void mst_dfs(int u, int prev){
    up[u][0] = prev;
    for(const pair<int, int>& p: mst_adj[u]){
        int w, v; tie(w, v) = p;
        if(v == prev) continue;
 
        h[v] = h[u] + 1;
        maxw[v][0].push(w);
        mst_dfs(v, u);
    }
}
 
void compute(){
    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i <= n; ++i){
            up[i][k] = up[up[i][k - 1]][k - 1];
            maxw[i][k].push(maxw[i][k - 1].first);
            maxw[i][k].push(maxw[i][k - 1].second);
            maxw[i][k].push(maxw[up[i][k - 1]][k - 1].first);
            maxw[i][k].push(maxw[up[i][k - 1]][k - 1].second);
        }
    }
}
 
int lift_max(int pos, int steps, int ubound){
    int res = -INF;
    for(int bit = MAXK; bit >= 0; --bit){
        if(steps >> bit & 1){
            if(maxw[pos][bit].first <= ubound) res = max(res, maxw[pos][bit].first);
            else if(maxw[pos][bit].second <= ubound) res = max(res, maxw[pos][bit].second); 
            pos = up[pos][bit];
        }
    }
    return res;
}
 
int lift(int pos, int steps){
    for(int bit = MAXK; bit >= 0; --bit){
        if(steps >> bit & 1) pos = up[pos][bit];
    }
    return pos;
}
 
int find_lca(int u, int v){
    if(h[u] > h[v]) swap(u, v);
    v = lift(v, h[v] - h[u]);
 
    if(u == v) return u;
 
    for(int bit = MAXK; bit >= 0; --bit){
        if(up[u][bit] != up[v][bit]){
            u = up[u][bit];
            v = up[v][bit];
        }
    }
 
    return up[u][0];
}
 
struct DSU{
    vector<int> parent, sz;
    int n;
 
    DSU() = default;
    DSU(int __sz): n(__sz){
        parent.resize(__sz + 1, -1);
        sz.resize(__sz + 1);
    }
 
    void create(int v){
        parent[v] = v;
        sz[v] = 1;
    }
    void init(){ for(int i = 0; i <= n; ++i) create(i); }
 
    int id(int v){
        return parent[v] == v ? v : parent[v] = id(parent[v]);
    }
 
    bool unite(int a, int b){
        a = id(a); b = id(b);
 
        if(a != b){
            if(sz[a] < sz[b]) swap(a, b);
 
            parent[b] = a;
            sz[a] += sz[b];
 
            return true;
        }
        return false;
    }
};
 
vector<Edge> que;
int mst_w = 0;
void kruskal(){
    sort(begin(edges), end(edges));
    DSU dsu(n);
    dsu.init();
 
    for(const Edge& e: edges){
        if(dsu.unite(e.u, e.v)){
            mst_adj[e.u].push_back({e.w, e.v});
            mst_adj[e.v].push_back({e.w, e.u});
            mst_w += e.w;
        }
        else{
            que.push_back(e);
        }
    }
}
 
void solve(){
    int diff = INF;
    for(const Edge& e: que){
        int LCA = find_lca(e.u, e.v);
        int cur = max(
            lift_max(e.u, h[e.u] - h[LCA], e.w - 1),
            lift_max(e.v, h[e.v] - h[LCA], e.w - 1)
        );
 
        diff = min(diff, e.w - cur);
    }
 
    cout << mst_w + diff << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        
        edges.push_back({a, b, c});
    }
 
    kruskal();
 
    mst_dfs(3, 0);
    compute();
 
    solve();
    
    // while(q--){
    //     int u, v;
    //     cin >> u >> v;
 
    //     cout << find_lca(u, v) << ' ';
    // }
 
    return 0;
}