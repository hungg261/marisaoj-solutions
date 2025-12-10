/******************************************************************************
Link: https://marisaoj.com/problem/260
Code: 260
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-10-00.30.46
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5, BLOCKSIZE = ceil(sqrt(MAXN));
int n, q, deg[MAXN + 5];
vector<int> adj[MAXN + 5], heavy[MAXN + 5];
int lazy[MAXN + 5], val[MAXN + 5];

void solve(){
    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int u, d;
            cin >> u >> d;

            if(deg[u] > BLOCKSIZE) lazy[u] += d;
            else for(int v: adj[u]){
                val[v] += d;
            }
        }
        else{
            int u;
            cin >> u;

            int res = val[u];
            for(int v: heavy[u]){
                res += lazy[v];
            }

            cout << res << '\n';
        }
    }
}


signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("260.INP","r",stdin);
    //freopen("260.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
        ++deg[a]; ++deg[b];
    }

    for(int u = 1; u <= n; ++u){
        for(int v: adj[u]){
            if(deg[u] > BLOCKSIZE || deg[v] > BLOCKSIZE){
                heavy[u].push_back(v);
            }
        }
    }

    solve();

    return 0;
}
