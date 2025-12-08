#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, m;
vector<int> adj[MAXN + 5];

int mark[MAXN + 5];
bool dfs(int u){
    mark[u] = 1;
    
    for(int v: adj[u]){
        if(mark[v] == 1) return false;
        else if(mark[v] == 2) continue;
        
        if(!dfs(v)){
            return false;
        }
    }
    
    mark[u] = 2;
    return true;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    
    for(int i = 1; i <= n; ++i){
        if(!mark[i]){
            if(!dfs(i)){
                cout << "NO\n";
                return 0;
            }
        }
    }
    
    cout << "YES\n";
    
    return 0;
}