#include<bits/stdc++.h>
// #define int long long
using namespace std;

struct DSU{
    vector<int> parent, sz, head;
    int n;
    
    DSU() = default;
    DSU(int __n): n(__n){ parent.resize(n + 1, -1); sz.resize(n + 1); head.resize(n + 1); }
    
    void create(int v){
        parent[v] = v; sz[v] = 1;
        head[v] = v;
    }
    void init(){ for(int i = 0; i <= n; ++i) create(i); }
    
    int id(int v){ return parent[v] == v ? v : parent[v] = id(parent[v]); }
    void unite(int a, int b){
        a = id(a); b = id(b);
        
        if(a != b){
            head[a] = head[b];
            if(sz[a] < sz[b]) swap(a, b);
            
            parent[b] = a;
            sz[a] += sz[b];
        }
    }
};

const int MAXN = 1e5;
int par[MAXN + 5];
DSU dsu;

int res[MAXN + 5];
void query(){
    int x, y, z;
    cin >> x >> y >> z;
    
    while(dsu.id(y) != dsu.id(x)){
        if(res[y] == 0) res[y] = z;
        
        dsu.unite(y, par[y]);
        y = dsu.head[dsu.id(y)];
    }
    if(res[y] == 0) res[y] = z;
    
    // while(y != x){
    //     dsu.unite(y, par[y]);
    //     y = par[y];
    // }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    dsu = DSU(n);
    
    for(int i = 1; i < n; ++i){
        int a, b; cin >> a >> b;
        par[b] = a;
    }
    
    dsu.init();
    for(int qr = 1; qr <= q; ++qr){
        query();
    }
    
    for(int i = 1; i <= n; ++i){
        cout << res[i] << ' ';
    }
    
    // cout << dsu.head[dsu.id(3)];
    
    return 0;
}