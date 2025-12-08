/******************************************************************************
Link: https://marisaoj.com/problem/126
Code: 126
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-07-23.40.34
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
struct DSU{
    int n;
    vector<int> par, sz;
 
    DSU() = default;
    DSU(int _sz): n(_sz){
        par.resize(_sz + 1);
        sz.resize(_sz + 1);
    }
 
    void create(int v){
        par[v] = v;
        sz[v] = 1;
    }
 
    int find_set(int v){
        return par[v] == v ? v : par[v] = find_set(par[v]);
    }
 
    void union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);
 
        if(a != b){
            if(sz[a] < sz[b]) swap(a, b);
            par[b] = a;
            sz[a] += sz[b];
        }
    }
};
 
void solve(){
    int n, m;
    cin >> n >> m;
 
    if(n - 1 != m){
        cout << "NO\n";
        return;
    }
 
    DSU dsu(n);
    for(int i = 1; i <= n; ++i) dsu.create(i);
 
    bool ok = true;
    for(int i = 1; i <= m; ++i){
        int u, v;
        cin >> u >> v;
 
        if(dsu.find_set(u) != dsu.find_set(v)) dsu.union_sets(u, v);
        else ok = false;
    }
 
    cout << (ok ? "YES\n" : "NO\n");
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("126.INP","r",stdin);
    //freopen("126.OUT","w",stdout);
    solve();
 
    return 0;
}