#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5, MAXK = __lg(MAXN) + 2;
int h[MAXN + 5], st[MAXN + 5], en[MAXN + 5], table[MAXN * 2 + 5][MAXK + 5], m = 0;
int lg2[MAXN * 2 + 5];
vector<int> adj[MAXN + 5];
int n;

void compute(){
    for(int i = 1; i <= m; ++i){
        lg2[i] = __lg(i);
    }

    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i + (1 << k) - 1 <= m; ++i){
            table[i][k] = h[table[i][k - 1]] < h[table[i + (1 << (k - 1))][k - 1]] ?
                table[i][k - 1] : table[i + (1 << (k - 1))][k - 1];
        }
    }
}

int minquery(int l, int r){
    int bit = lg2[r - l + 1];
    return h[table[l][bit]] < h[table[r - (1 << bit) + 1][bit]] ? table[l][bit] : table[r - (1 << bit) + 1][bit];
}

void dfs(int u, int prev){
    table[++m][0] = u;
    st[u] = m;

    for(int v: adj[u]){
        if(v == prev) continue;

        h[v] = h[u] + 1; 
        dfs(v, u);
        table[++m][0] = u;
    }

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
    compute();

    // cerr << m << ": "; for(int i = 1; i <= m; ++i) cerr << table[i][0] << ' '; cerr << '\n';
    // cerr << minquery(3, 4) << '\n';

    while(q--){
        int u, v;
        cin >> u >> v;

        if(st[u] > st[v]) swap(u, v);
        cout << minquery(st[u], st[v]) << ' ';
    }

    return 0;
}