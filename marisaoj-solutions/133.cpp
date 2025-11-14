#include<bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> parent, sz;
    
    DSU() = default;
    DSU(int n){
        parent.resize(n + 1);
        sz.resize(n + 1);
    }
    
    void create(int v){
        parent[v] = v;
        sz[v] = 1;
    }
    
    int find_set(int v){
        if(parent[v] == v) return v;
        return parent[v] = find_set(parent[v]);
    }
    
    bool union_sets(int u, int v){
        int a = find_set(u), b = find_set(v);
        if(a == b) return false;
        
        if(sz[a] < sz[b]) swap(a,  b);
        parent[b] = a;
        sz[a] += sz[b];
    }
    
    void occupy(int v, int n){
        int next = v + 1 <= n ? v + 1 : 1;
        parent[v] = next;
        sz[next] += sz[v];
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    
    DSU dsu(n);
    for(int i = 1; i <= n; ++i) dsu.create(i);
    
    for(int i = 1; i <= n; ++i){
        int p; cin >> p;
        
        if(dsu.parent[p] == p){
            cout << p << ' ';
            dsu.occupy(p, n);
        }
        else{
            int chosen = dsu.find_set(p);
            cout << chosen << ' ';
            dsu.occupy(chosen, n);
        }
    }
    cout << '\n';
    
    return 0;
}