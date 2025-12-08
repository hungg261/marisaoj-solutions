#include<bits/stdc++.h>
using namespace std;
 
struct DSU{
    vector<int> parent, sz;
    int n;
    
    DSU(int __n): n(__n) { parent.resize(n + 1); sz.resize(n + 1); }
    
    void create(int v){
        parent[v] = v;
        sz[v] = 1;
    }
    
    void initialize(){
        for(int i = 1; i <= n; ++i){
            create(i);
        }
    }
    
    int id(int v){
        return parent[v] == v ? v : parent[v] = id(parent[v]);
    }
    
    void unite(int a, int b){
        a = id(a);
        b = id(b);
        
        if(a != b){
            if(sz[a] < sz[b]) swap(a, b);
            
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};
 
const int MAXN = 1e5;
int n, m, q;
vector<pair<int, int>> edges;
vector<pair<int, int>> queries;
bool removed[MAXN + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> q;
    edges.emplace_back();
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;
        
        edges.push_back({a, b});
    }
    
    for(int i = 1; i <= q; ++i){
        int e, v;
        cin >> e >> v;
        
        removed[e] = true;
        queries.push_back({e, v});
    }
    
    DSU dsu(n);
    dsu.initialize();
    
    for(int i = 1; i <= m; ++i){
        if(!removed[i]){
            dsu.unite(edges[i].first, edges[i].second);
        }
    }
    
    vector<int> res;
    for(int i = q - 1; i >= 0; --i){
        res.push_back(dsu.sz[dsu.id(queries[i].second)]);
        
        int idx = queries[i].first;
        dsu.unite(edges[idx].first, edges[idx].second);
    }
    
    reverse(begin(res), end(res));
    for(int r: res) cout << r << '\n';
    
    return 0;
}