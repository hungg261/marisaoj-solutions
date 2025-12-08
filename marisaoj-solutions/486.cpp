#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e5;
int h[MAXN + 5],
    sz[MAXN + 5],
    par[MAXN + 5],
 
    ChainHead[MAXN + 5],
    ChainID[MAXN + 5],
 
    Arr[MAXN + 5],
    St[MAXN + 5], En[MAXN + 5],
    curChain = 1, curPos = 0;
 
vector<int> adj[MAXN + 5];
int c[MAXN + 5];
int n;
 
void dfs(int u, int prev){
    sz[u] = 1;
    for(int v: adj[u]){
        if(v == prev) continue;
 
        h[v] = h[u] + 1;
        par[v] = u;
        dfs(v, u);
        sz[u] += sz[v];
    }
}
 
void Hld(int u, int prev){
    if(!ChainHead[curChain]) ChainHead[curChain] = u;
    ChainID[u] = curChain;
 
    Arr[++curPos] = u;
    St[u] = curPos;
 
    int nxt = -1;
    for(int v: adj[u]){
        if(v == prev) continue;
 
        if(nxt == -1 || sz[nxt] < sz[v]) nxt = v;
    }
    if(nxt != -1) Hld(nxt, u);
 
    for(int v: adj[u]){
        if(v == prev || v == nxt) continue;
 
        ++curChain;
        Hld(v, u);
    }
 
    En[u] = curPos;
}
 
int nodes[MAXN * 4 + 5], lazy[MAXN * 4 + 5];
 
void down(int id, int l, int r){
    int t = lazy[id];
    int mid = (l + r) >> 1;
    if(t == -1) return;
 
    if(t == 0){
        nodes[id << 1] = 0;
        nodes[id << 1 | 1] = 0;
    }
    else{
        nodes[id << 1] = mid - l + 1;
        nodes[id << 1 | 1] = r - mid;
    }
 
    lazy[id << 1] = t;
    lazy[id << 1 | 1] = t;
 
    lazy[id] = -1;
}
 
void update(int id, int l, int r, int u, int v, int color){
    if(r < u || v < l) return;
    if(u <= l && r <= v){
        nodes[id] = color == 0 ? 0 : r - l + 1;
        lazy[id] = color;
 
        return;
    }
 
    down(id, l, r);
 
    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, color);
    update(id << 1 | 1, mid + 1, r, u, v, color);
    nodes[id] = nodes[id << 1] + nodes[id << 1 | 1];
}
 
int get(int id, int l, int r, int u, int v){
    if(r < u || v < l) return 0;
    if(u <= l && r <= v) return nodes[id];
 
    down(id, l, r);
 
    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}
 
int query1(int u, int v){
    int res = 0;
    while(ChainID[u] != ChainID[v]){
        if(ChainID[u] > ChainID[v]){
            int l = St[ChainHead[ChainID[u]]], r = St[u];
            int modified = (r - l + 1) - get(1, 1, n, l, r);
            res += modified;
 
            update(1, 1, n, l, r, 1);
            u = par[ChainHead[ChainID[u]]];
        }
        else{
            int l = St[ChainHead[ChainID[v]]], r = St[v];
            int modified = (r - l + 1) - get(1, 1, n, l, r);
            res += modified;
 
            update(1, 1, n, l, r, 1);
            v = par[ChainHead[ChainID[v]]];
        }
    }
 
    if(h[u] > h[v]) swap(u, v);
    res += (St[v] - St[u] + 1) - get(1, 1, n, St[u], St[v]);
    update(1, 1, n, St[u], St[v], 1);
 
    return res;
}
 
int query2(int u){
    int modified = get(1, 1, n, St[u], En[u]);
    update(1, 1, n, St[u], En[u], 0);
 
    return modified;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;
 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    dfs(1, 0);
    Hld(1, 0);
 
    while(q--){
        int type;
        cin >> type;
 
        if(type == 1){
            int u;
            cin >> u;
 
            cout << query1(St[1], u) << '\n';
        }
        else{
            int u;
            cin >> u;
 
            cout << query2(u) << '\n';
        }
    }
 
    return 0;
}