#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 2e5, MAXK = 5;
const int INF = 1e18;
vector<pair<int, int>> adj[MAXN + 5];
int n, m, k;
 
struct State{
    int v, cost, kcnt;
    
    tuple<int, int, int> get() const{
        return {v, cost, kcnt};
    }
    
    bool operator > (const State& other){
        return this->cost > other.cost;
    }
};
 
int dist[MAXN + 5][MAXK + 5];
void dijkstra(){
    priority_queue<State, vector<State>, greater<>> pq;
    
    pq.push({1, 0, 0});
    
    for(int i = 1; i <= n; ++i) for(int j = 0; j <= k; ++j) dist[i][j] = INF;
    dist[1][0] = 0;
    
    while(!pq.empty()){
        int u, curCost, kcnt; tie(u, curCost, kcnt) = pq.top().get();
        pq.pop();
        
        if(curCost != dist[u][kcnt]) continue;
        
        for(const auto& p: adj[u]){
            int cost, v; tie(cost, v) = p;
            // cerr << u << ' ' << v << ": " << cost << " | " << curCost << " | " << kcnt << '\n';
 
            if(dist[u][kcnt] + cost < dist[v][kcnt]){
                dist[v][kcnt] = dist[u][kcnt] + cost;
                pq.push({v, dist[v][kcnt], kcnt});
            }
            
            if(kcnt < k){
                if(dist[u][kcnt] < dist[v][kcnt + 1]){
                    dist[v][kcnt + 1] = dist[u][kcnt];
                    pq.push({v, dist[v][kcnt + 1], kcnt + 1});
                }
            }
        }
    }
    
    // for(int i = 1; i <= n; ++i){
    //     for(int j = 0; j <= k; ++j){
    //         cerr << dist[i][j] << ' ';
    //     }
    //     cerr << '\n';
    // }
    
    int ans = *min_element(dist[n], dist[n] + k + 1);
    if(ans == INF){
        cout << "-1\n";
        return;
    }
    
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }
    
    dijkstra();
 
    return 0;
}