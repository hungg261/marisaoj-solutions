#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5, MAXK = __lg(MAXN) + 1;
int n, q, table[MAXN + 5][MAXK + 5], h[MAXN + 5], childcnt[MAXN + 5];
vector<int> adj[MAXN + 5];

void compute(){
    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i <= n; ++i){
            table[i][k] = table[table[i][k - 1]][k - 1];
        }
    }
}

int jump(int pos, int steps){
    for(int bit = MAXK; bit >= 0; --bit){
        if(steps >> bit & 1) pos = table[pos][bit];
    }
    return pos;
}

int lca(int u, int v){
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
    childcnt[u] = 1;
    for(int v: adj[u]){
        if(prev == v) continue;

        h[v] = h[u] + 1;
        table[v][0] = u;
        dfs(v, u);
        childcnt[u] += childcnt[v];
    }
}

void solve(int u, int v){
    if(h[u] > h[v]) swap(u, v);
    int LCA = lca(u, v),
        length = h[u] + h[v] - 2 * h[LCA];

    if(length & 1){
        cout << "0\n";
        return;
    }

    int half = length / 2;
    int mid = jump(v, half);

    int ans = n;
    if(h[u] == h[v]) ans -= childcnt[jump(u, half - 1)] + childcnt[jump(v, half - 1)];
    else ans -= childcnt[jump(v, half - 1)] + (childcnt[1] - childcnt[mid]);

    cout << ans << '\n';
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
    dfs(1, -1);
    compute();
    
    for(int qr = 1; qr <= q; ++qr){
        int u, v;
        cin >> u >> v;

        solve(u, v);
    }

    return 0;
}