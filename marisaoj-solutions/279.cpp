/******************************************************************************
Link: https://marisaoj.com/problem/279
Code: 279
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-18.52.28
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int c[MAXN + 5];

vector<int> adj[MAXN + 5];
int n;

inline void merge(set<int>& A, const set<int>& B){
    for(const int& v: B) A.insert(v);
}

int res[MAXN + 5];
set<int> dfs(int u, int prev){
    set<int> cur = {c[u]};
    for(int v: adj[u]){
        if(v == prev) continue;

        set<int> child = dfs(v, u);
        if(cur.size() < child.size()) swap(cur, child);

        merge(cur, child);
    }

    res[u] = cur.size();
    return cur;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("279.INP","r",stdin);
    //freopen("279.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> c[i];
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);

    for(int i = 1; i <= n; ++i){
        cout << res[i] << ' ';
    }

    return 0;
}