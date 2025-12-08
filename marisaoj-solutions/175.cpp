#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 2e5;
const int INF = 1e18;
const int MOD = 1e9 + 7;
vector<pair<int, int>> adj[MAXN + 5];
int n, m;
 
int dist[MAXN + 5], minCnt[MAXN + 5];
void dijkstra(){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 1});
    
    fill(dist + 1, dist + n + 1, INF);
    dist[1] = 0;
    minCnt[1] = 1;
    
    while(!pq.empty()){
        int curCost, u; tie(curCost, u) = pq.top();
        pq.pop();
        
        if(curCost != dist[u]) continue;
        
        for(const auto& p: adj[u]){
            int cost, v; tie(cost, v) = p;
            
            int newCost = curCost + cost;
            if(newCost == dist[v]){
                minCnt[v] = (minCnt[v] + minCnt[u]) % MOD;
            }
            else if(newCost < dist[v]){
                dist[v] = newCost;
                minCnt[v] = minCnt[u];
                pq.push({newCost, v});
            }
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }
    
    dijkstra();
    cout << minCnt[n] << '\n';
    
    return 0;
}