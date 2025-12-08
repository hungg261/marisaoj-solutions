#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e5;
int n, m;
vector<int> adj[MAXN + 5];
string str;
 
vector<int> topo;
bool mark[MAXN + 5];
void toposort(int u){
    if(mark[u]) return;
    mark[u] = true;
 
    for(int v: adj[u]){
        toposort(v);
    }
 
    topo.push_back(u);
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> str;
    str = "#" + str;
 
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;
 
        adj[a].push_back(b);
    }
 
    for(int i = 1; i <= n; ++i){
        if(!mark[i]) toposort(i);
    }
    reverse(begin(topo), end(topo));
 
    vector<vector<int>> dp(n + 1, vector<int>(26, 0));
    for(int u: topo){
        dp[u][str[u] - 'a'] = 1;
 
        cerr << u << ' ';
    } cerr << '\n';
 
    for(int i = 0; i < n; ++i){
        int u = topo[i];
        for(int v: adj[u]){
            int c = str[v] - 'a';
            for(int k = 0; k < 26; ++k){
                dp[v][k] = max(dp[v][k], dp[u][k] + (k == c));
            }
        }
    }
 
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        // for(int j = 0; j < 26; ++j){
        //     cerr << dp[i][j] << ' ';
        // } cerr << '\n';
        ans = max(ans, *max_element(begin(dp[i]), end(dp[i])));
    }
 
    cout << ans << '\n';
 
    return 0;
}