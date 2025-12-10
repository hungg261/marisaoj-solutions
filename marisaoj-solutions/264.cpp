/******************************************************************************
Link: https://marisaoj.com/problem/264
Code: 264
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-10-12.57.59
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

//#define int long long

const int MAXN = 5e4, MAXK = __lg(MAXN) + 1, BLOCKSIZE = ceil(sqrt(MAXN));
int n, q, h[MAXN + 5], c[MAXN + 5];
vector<int> adj[MAXN + 5];
vector<int> colors[MAXN + 5];

int table[MAXN * 2 + 5][MAXK + 5], m = 0, st[MAXN + 5], lg2[MAXN + 5];
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

void compute(){
    for(int i = 1; i <= m; ++i) lg2[i] = __lg(i);
    for(int k = 1; k <= MAXK; ++k){
        for(int i = 1; i + (1 << k) - 1 <= m; ++i){
            table[i][k] = h[table[i][k - 1]] < h[table[i + (1 << (k - 1))][k - 1]] ?
                            table[i][k - 1] : table[i + (1 << (k - 1))][k - 1];
        }
    }
}

int find_lca(int u, int v){
    u = st[u];
    v = st[v];
    if(u > v) swap(u, v);

    int bit = lg2[v - u + 1];
    return h[table[u][bit]] < h[table[v - (1 << bit) + 1][bit]] ? table[u][bit] : table[v - (1 << bit) + 1][bit];
}

int find_dist(int u, int v){
    return h[u] + h[v] - h[find_lca(u, v)] * 2;
}

int find_closet(int node, int x){
    if(c[node] == x) return 0;

    queue<tuple<int, int, int>> que;
    que.push({node, 0, 0});
    while(!que.empty()){
        int u, prv, cnt; tie(u, prv, cnt) = que.front();
        que.pop();

        for(int v: adj[u]){
            if(v == prv) continue;

            if(c[v] == x) return cnt + 1;
            que.push({v, u, cnt + 1});
        }
    }

    return INT_MAX;
}

void solve(){
    while(q--){
        int u, x;
        cin >> u >> x;

        int best = INT_MAX;
        if((int)colors[x].size() > BLOCKSIZE){
            best = find_closet(u, x);
        }
        else{
            for(int cl: colors[x]){
                best = min(best, find_dist(u, cl));
            }
        }

        cout << (best == INT_MAX ? -1 : best) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("264.INP","r",stdin);
    //freopen("264.OUT","w",stdout);
    cin >> n >> q;
    for(int u = 1; u <= n; ++u){
        cin >> c[u];
        colors[c[u]].push_back(u);
    }
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    compute();

    solve();

    return 0;
}

/*
3 5
2 2 5
3 2
1 2
3 2
2 2
3 1
1 2
3 1
*/
