#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 2e5;
const int INF = 1e18;
vector<pair<int, int>> adj[MAXN + 5];
int n, m;

int dist[MAXN + 5], parent[MAXN + 5];
void dijkstra(){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    pq.push({0, 1});
    
    fill(dist + 1, dist + n + 1, INF);
    dist[1] = 0;
    
    while(!pq.empty()){
        int curCost, u; tie(curCost, u) = pq.top();
        pq.pop();
        
        if(curCost != dist[u]) continue;
        
        for(const auto& p: adj[u]){
            int cost, v; tie(cost, v) = p;
            int newCost = dist[u] + cost;
            if(newCost < dist[v]){
                dist[v] = newCost;
                parent[v] = u;
                
                pq.push({newCost, v});
            }
        }
    }
    
    if(dist[n] == INF){
        cout << "-1\n";
        return;
    }
    
    cout << dist[n] << '\n';
    
    int cur = n;
    vector<int> res;
    while(cur != 0){
        res.push_back(cur);
        cur = parent[cur];
    }
    
    reverse(begin(res), end(res));
    for(int node: res) cout << node << ' ';
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

    return 0;
}