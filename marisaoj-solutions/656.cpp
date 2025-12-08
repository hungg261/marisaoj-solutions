#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5, MAXK = __lg(MAXN) + 1;
int St[MAXN + 5], En[MAXN + 5], euler[MAXN + 5], Time;
int parent[MAXN + 5], h[MAXN + 5], n, q;
int table[MAXN + 5][MAXK + 5];
vector<int> adj[MAXN + 5];
 
int maxTableA[MAXN + 5][MAXK + 5], maxTableB[MAXN + 5][MAXK + 5];
int distA[MAXN + 5], distB[MAXN + 5];
void computeMaxDist(){
    for(int i = 1; i <= Time; ++i){
        maxTableA[i][0] = distA[euler[i]];
        maxTableB[i][0] = distB[euler[i]];
    }
 
    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i + (1 << k) - 1 <= Time; ++i){
            maxTableA[i][k] = max(maxTableA[i][k - 1], maxTableA[i + (1 << (k - 1))][k - 1]);
            maxTableB[i][k] = max(maxTableB[i][k - 1], maxTableB[i + (1 << (k - 1))][k - 1]);
        }
    }
}
 
int max_query(int l, int r, int tab[MAXN + 5][MAXK + 5]){
    if(l > r) return -1e18;
 
    int lg = __lg(r - l + 1);
    return max(tab[l][lg], tab[r - (1 << lg) + 1][lg]);
}
 
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
 
int jump(int pos, int steps){
    int bit = 0;
    while(steps > 0){
        if(steps & 1) pos = table[pos][bit];
 
        ++bit;
        steps >>= 1;
    }
 
    return pos;
}
 
int find_lca(int u, int v){
    if(h[u] > h[v]) swap(u, v);
    v = jump(v, h[v] - h[u]);
 
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
    euler[++Time] = u;
    St[u] = Time;
 
    h[u] = h[prev] + 1;
    parent[u] = prev;
    for(int v: adj[u]){
        if(v == prev) continue;
 
        dfs(v, u);
    }
 
    En[u] = Time;
}
 
struct Diameter{
    int a = -1, b = -1, length = 0;
 
    Diameter() = default;
    Diameter(int _a, int _b, int _length): a(_a), b(_b), length(_length){}
};
Diameter d;
 
Diameter dfs_farthest(int u, int prev){
    Diameter best(u, u, 0);
 
    for(int v: adj[u]){
        if(v == prev) continue;
 
        Diameter candidate = dfs_farthest(v, u);
        if(best.length <= 1 + candidate.length){
            best = Diameter(u, candidate.b, 1 + candidate.length);
        }
    }
 
    return best;
}
 
void dfs_dist(int u, int prev, int len[]){
    for(int v: adj[u]){
        if(v == prev) continue;
 
        len[v] = len[u] + 1;
        dfs_dist(v, u, len);
    }
}
 
int find_dist(int u, int v){
    return h[u] + h[v] - 2 * h[find_lca(u, v)];
}
 
int toward(int u, int v, int w){
        int LCA = find_lca(u, v);
        int x = u;
        x = jump(x, w);
 
        if(h[x] >= h[LCA]){
            return x;
        }
 
        w -= h[u] - h[LCA];
        w = (h[v] - h[LCA]) - w;
        x = v;
 
        if(w < 0){
            return v;
        }
 
        x = jump(x, w);
        return x;  
}
 
void query(int u, int v){
    swap(u, v);
 
    int dist = find_dist(u, v);
    int bridgeU = toward(u, v, (dist - 1) / 2),
        bridgeV = toward(u, v, (dist - 1) / 2 + 1);
    
 
    if(bridgeU == parent[bridgeV]){
        int bestA, bestB;
 
        if(St[bridgeV] <= St[d.a] && En[d.a] <= En[bridgeV])
            bestA = max(max_query(1, St[bridgeV] - 1, maxTableA), max_query(En[bridgeV] + 1, Time, maxTableA))
                    - find_dist(d.a, bridgeU);
        else
            bestA = find_dist(d.a, bridgeU);
        
        if(St[bridgeV] <= St[d.b] && En[d.b] <= En[bridgeV])
            bestB = max(max_query(1, St[bridgeV] - 1, maxTableB), max_query(En[bridgeV] + 1, Time, maxTableB))
                    - find_dist(d.b, bridgeU);
        else
            bestB = find_dist(d.b, bridgeU);
        
        int res = max(bestA, bestB) + find_dist(v, bridgeU);
        cout << res << '\n';
    }
    else if(bridgeV == parent[bridgeU]){
        int bestA, bestB;
 
        if(St[bridgeU] <= St[d.a] && En[d.a] <= En[bridgeU])
            bestA = find_dist(d.a, bridgeU);
        else
            bestA = max_query(St[bridgeU], En[bridgeU], maxTableA)
                    - find_dist(d.a, bridgeU);
        
        if(St[bridgeU] <= St[d.b] && En[d.b] <= En[bridgeU])
            bestB = find_dist(d.b, bridgeU);
        else
            bestB = max_query(St[bridgeU], En[bridgeU], maxTableB)
                    - find_dist(d.b, bridgeU);
        
        int res = max(bestA, bestB) + find_dist(v, bridgeU);
        cout << res << '\n';
    }
    else exit(-1);
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
 
    dfs(1, 0);
    compute();
 
    d = dfs_farthest(dfs_farthest(1, 0).b, 0);
    dfs_dist(d.a, 0, distA);
    dfs_dist(d.b, 0, distB);
 
    computeMaxDist();
 
    while(q--){
        int u, v;
        cin >> u >> v; 
 
        query(u, v);
    }
 
    return 0;
}