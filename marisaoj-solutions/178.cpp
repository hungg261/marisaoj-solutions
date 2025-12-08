#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;
const int INF = 1e9;
vector<pair<int, int>> adj[MAXN + 5];
int A[MAXN + 5];
int n;

vector<int> dx, dy, dz;
void computeDir(){
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y){
            for(int z = -1; z <= 1; ++z){
                if(abs(x) + abs(y) + abs(z) == 1){
                    dx.push_back(x);
                    dy.push_back(y);
                    dz.push_back(z);
                }
            }
        }
    }
}

int encode(int i, int j, int k){
    return ((i - 1) * n + j - 1) * n + k;
}

bool in_bound(int x){
    return 1 <= x && x <= n;
}

int dist[MAXN + 5];
void dijkstra(){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 1});
    
    fill(dist + 1, dist + n * n * n + 1, INF);
    dist[1] = 0;
    
    while(!pq.empty()){
        int curCost, u; tie(curCost, u) = pq.top();
        pq.pop();
        
        if(curCost != dist[u]) continue;
        
        for(const auto& p: adj[u]){
            int cost, v; tie(cost, v) = p;
            
            if(curCost + cost < dist[v]){
                dist[v] = curCost + cost;
                pq.push({dist[v], v});
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    
    computeDir();
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            for(int k = 1; k <= n; ++k){
                cin >> A[encode(i, j, k)];
            }
        }
    }
    
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            for(int k = 1; k <= n; ++k){
                int cur = encode(i, j, k);
                for(int d = 0; d < 6; ++d){
                    int nx = i + dx[d], ny = j + dy[d], nz = k + dz[d];
                    
                    if(in_bound(nx) && in_bound(ny) && in_bound(nz)){
                        int nxt = encode(nx, ny, nz);
                        adj[cur].push_back({A[nxt], nxt});
                    }
                }
            }
        }
    }
    
    dijkstra();
    cout << dist[encode(n, n, n)] << '\n';
    
    
    // for(int i = 1; i <= n; ++i){
    //     for(int j = 1; j <= n; ++j){
    //         for(int k = 1; k <= n; ++k){
    //             int cur = encode(i, j, k);
                
    //             cerr << encode(i, j, k) << ". " << i << ' ' << j << ' ' << k << ": " << A[cur] << '\n';
    //         }
    //     }
    // }
    
    // cerr << '\n';
    
    // for(int u = 1; u <= n * n * n; ++u){
    //     cerr << u << ": ";
    //     for(const auto& v: adj[u]){
    //         cerr << v.second << ' ';
    //     }
    //     cerr << '\n';
    // }
    
    // cerr << '\n';
    
    // for(int u = 1; u <= n * n * n; ++u){
    //     cerr << dist[u] << ' ';
    // }
    
    return 0;
}