#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, m;
vector<int> adj[MAXN + 5];

bool mark[MAXN + 5];
vector<int> res;
void toposort(int u){
    if(mark[u]) return;
    mark[u] = true;
    
    for(int v: adj[u]){
        toposort(v);
    }
    
    res.push_back(u);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    
    for(int i = 1; i <= n; ++i){
        if(!mark[i]) toposort(i);
    }
    reverse(begin(res), end(res));
    
    vector<int> dp(n + 1, 1);
    for(int i: res){
        for(int j: adj[i]){
            dp[j] = max(dp[j], dp[i] + 1);
        }
    }
    
    cout << *max_element(begin(dp), end(dp)) << '\n';
    
    return 0;
}