#include<bits/stdc++.h>
#define int long long
using namespace std;
 
struct DSU{
    vector<int> parent, sz;
    int n;
    
    DSU(int __n): n(__n) { parent.resize(n + 1, -1); sz.resize(n + 1, 0); }
    
    bool existed(int v){
        return parent[v] != -1;
    }
    
    void create(int v){
        parent[v] = v;
        sz[v] = 1;
    }
    
    void initialize(){
        for(int i = 0; i <= n; ++i){
            create(i);
        }
    }
    
    int id(int v){
        return parent[v] == v ? v : parent[v] = id(parent[v]);
    }
    
    bool inGroup(int a, int b){
        return id(a) == id(b);
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
pair<int, int> arr[MAXN + 5];
int maxGroup[MAXN + 5];
int n, q;
 
int upperbound(int value){
    int l = 1, r = n, res = n + 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(arr[mid].first > value){
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    
    return res;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr + 1, arr + n + 1);
    
    DSU dsu(n + 1);
    for(int i = 1; i <= n; ++i){
        int idx = arr[i].second;
        dsu.create(idx);
        
        if(dsu.existed(idx - 1)) dsu.unite(idx - 1, idx);
        if(dsu.existed(idx + 1)) dsu.unite(idx + 1, idx);
        maxGroup[i] = max(maxGroup[i - 1], dsu.sz[dsu.id(arr[i].second)]);
    }
    
    for(int i = 1; i <= q; ++i){
        int k; cin >> k;
        
        int sep = upperbound(k) - 1;
        cout << maxGroup[sep] << '\n';
    }
    
    return 0;
}