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
    int u, v, w, idx;

    bool operator < (const Edge& other){
        return this->w < other.w;
    }
};

const int MAXN = 1e5;
int n, m;
vector<Edge> edges;

void solve(){
    sort(begin(edges), end(edges));
    DSU dsu(n);
    dsu.init();

    string res(m, '0');
    for(int i = 0; i < m;){

        int j = i;
        while(j < m && edges[i].w == edges[j].w){
            if(!dsu.inGroup(edges[j].u, edges[j].v)){
                res[edges[j].idx - 1] = '1';
            }
            ++j;
        }
        
        for(; i < j; ++i){
            dsu.unite(edges[i].u, edges[i].v);
        }
    }

    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b, w;
        cin >> a >> b >> w;

        edges.push_back({a, b, w, i});
    }    

    solve();

    return 0;
}