#include<bits/stdc++.h>
#define int long long
using namespace std;
 
struct DSU{
    vector<int> parent, sz;
    int n;
 
    DSU() = default;
    DSU(int __n): n(__n){ parent.resize(n + 1, -1); sz.resize(n + 1); }
 
    void create(int v){
        parent[v] = v;
        sz[v] = 1;
    }
    void init(){ for(int i = 0; i <= n; ++i) create(i); }
 
    int id(int v){
        return parent[v] == v ? v : parent[v] = id(parent[v]);
    }
    bool inGroup(int a, int b){ return id(a) == id(b); }
 
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
 
struct Edge{
    int u, v, w;
 
    bool operator < (const Edge& other){
        return this->w < other.w;
    }
};
 
const int MAXN = 500;
int n;
vector<Edge> edges;
 
void kruskal(){
    sort(begin(edges), end(edges));
    DSU dsu(n);
    dsu.init();
 
    int ans = 0;
    for(const Edge& e: edges){
        if(dsu.unite(e.u, e.v)) ans += e.w;
    }
 
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        int w; cin >> w;
        edges.push_back({0, i, w});
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            int w; cin >> w;
            edges.push_back({i, j, w});
        }
    }
 
    kruskal();
 
    return 0;
}