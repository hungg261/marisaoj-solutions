/******************************************************************************
Link: https://marisaoj.com/problem/264
Code: 264
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-10-12.57.59
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

//#define int long long

const int MAXN = 5e4, MAXK = __lg(MAXN) + 1, BLOCKSIZE = 200;
int n, q, h[MAXN + 5], c[MAXN + 5];
vector<int> adj[MAXN + 5];
vector<int> colors[MAXN + 5];

int table[MAXN + 5][MAXK + 5];
void dfs(int u, int prv){
    for(int v: adj[u]){
        if(v == prv) continue;

        h[v] = h[u] + 1;
        table[v][0] = u;
        dfs(v, u);
    }
}

void compute(){
    for(int j = 1; j <= MAXK; ++j){
        for(int i = 1; i <= n; ++i){
            table[i][j] = table[table[i][j - 1]][j - 1];
        }
    }
}

int lift(int u, int steps){
    for(int bit = MAXK; bit >= 0; --bit){
        if(steps >> bit & 1){
            u = table[u][bit];
        }
    }
    return u;
}

int find_lca(int u, int v){
    if(h[v] < h[u]) swap(u, v);
    v = lift(v, h[v] - h[u]);

    if(u == v) return u;

    for(int bit = MAXK; bit >= 0; --bit){
        if(table[u][bit] != table[v][bit]){
            u = table[u][bit];
            v = table[v][bit];
        }
    }

    return table[u][0];
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
