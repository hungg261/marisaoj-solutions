#include<bits/stdc++.h>
using namespace std;
 
#define int long long
struct MaxFlow{
    static const int INF = LLONG_MAX;
    struct EdgeTo{
        int v;
        int cap;
        int rev;
 
        EdgeTo() = default;
        EdgeTo(int _v, int _w, int _rev): v(_v), cap(_w), rev(_rev){}
    };
 
    int n, m;
    vector<vector<EdgeTo>> adj;
    vector<int> level, it;
 
    MaxFlow() = default;
    MaxFlow(int V): n(V){
        adj.resize(V + 1);
        level.resize(V + 1);
        it.resize(V + 1);
    }
 
    void addEdge(int a, int b, int c, bool directed = true){
        adj[a].emplace_back(b, c, (int)adj[b].size());
        adj[b].emplace_back(a, directed ? 0 : c, (int)adj[a].size() - 1);
    }
 
    bool bfs_findPath(int S, int T){
        queue<int> que;
        que.push(S);
 
        fill(begin(level) + 1, end(level), -1);
        level[S] = 0;
        while(!que.empty()){
            int u = que.front(); que.pop();
            for(const EdgeTo& e: adj[u]){
                if(e.cap > 0 && level[e.v] == -1){
                    level[e.v] = level[u] + 1;
                    que.push(e.v);
                }
            }
        }
 
        return level[T] >= 0;
    }
 
    int dfs_sendFlow(int u, int flow, int T){
        if(u == T || flow == 0) return flow;
 
        for(int& i = it[u]; i < (int)adj[u].size(); ++i){
            EdgeTo& e = adj[u][i];
 
            if(e.cap > 0 && level[u] + 1 == level[e.v]){
                int pushed = dfs_sendFlow(e.v, min(flow, e.cap), T);
                if(pushed > 0){
                    e.cap -= pushed;
                    adj[e.v][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
 
        return 0;
    }
 
    vector<pair<int, int>> minCut(int S, int T, const vector<pair<int, int>>& edges){
        vector<bool> reachable(n + 1);
 
        queue<int> que;
        que.push(S);
        reachable[S] = true;
 
        while(!que.empty()){
            int u = que.front(); que.pop();
            for(const EdgeTo& e: adj[u]){
                if(e.cap > 0 && !reachable[e.v]){
                    reachable[e.v] = true;
                    que.push(e.v);
                }
            }
        }
 
        vector<pair<int, int>> res;
        for(const pair<int, int>& p: edges){
            if(reachable[p.first] ^ reachable[p.second]){
                res.push_back(p);
            }
        }
        return res;
    }
 
    int getFlow(int S, int T){
        int ans = 0;
        while(bfs_findPath(S, T)){
            fill(begin(it) + 1, end(it), 0);
            ans += dfs_sendFlow(S, INF, T);
        }
 
        return ans;
    }
};
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int n, m, S, T;
    cin >> n >> m >> S >> T;
 
    MaxFlow G(n);
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
 
        G.addEdge(a, b, c);
    }
 
    cout << G.getFlow(S, T) << '\n';
 
    return 0;
}