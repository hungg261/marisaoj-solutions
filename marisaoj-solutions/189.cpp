#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5;
int n, q, st[MAXN + 5], en[MAXN + 5], tour[MAXN + 5], m = 0;
vector<int> adj[MAXN + 5];

struct FenwickTree{
    int n;
    vector<int> BIT;

    FenwickTree() = default;
    FenwickTree(int sz): n(sz){
        BIT.resize(n + 1, 0);
    }

    void update(int idx, int val){
        for(int i = idx; i <= n; i += i & -i) BIT[i] += val;
    }

    int get(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i) res += BIT[i];
        return res;
    }

    int get(int l, int r){ return get(r) - get(l - 1); }

    void modify(int idx, int val){
        update(idx, val - get(idx, idx));
    }
};

void dfs(int u, int prev){
    tour[++m] = u;
    st[u] = m;

    for(int v: adj[u]){
        if(v == prev) continue;

        dfs(v, u);
    }

    en[u] = m;
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
    
    FenwickTree fwt(n + 1);
    for(int qr = 1; qr <= q; ++qr){
        int i, x;
        cin >> i >> x;

        fwt.update(st[i], x);
        fwt.update(en[i] + 1, -x);
    }

    for(int i = 1; i <= n; ++i){
        cout << fwt.get(st[i]) << ' ';
    }

    return 0;
}