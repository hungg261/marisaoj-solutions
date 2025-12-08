/******************************************************************************
Link: https://marisaoj.com/problem/349
Code: 349
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-05-16.15.43
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct MaxFlow{
    struct EdgeTo{
        int v;
        int cap;
        int rev;

        EdgeTo() = default;
        EdgeTo(int _v, int _cap, int _rev): v(_v), cap(_cap), rev(_rev){}
    };

    int n;
    vector<vector<EdgeTo>> adj;
    vector<int> level, it;

    MaxFlow() = default;
    MaxFlow(int sz): n(sz){
        adj.resize(sz + 1);
        level.resize(sz + 1, 0);
        it.resize(sz + 1, 0);
    }

    void addEdge(int u, int v, int w, bool directed = true){
        adj[u].emplace_back(v, w, (int)adj[v].size());
        adj[v].emplace_back(u, directed ? 0 : w, (int)adj[u].size() - 1);
    }

    bool bfs_findPath(int S, int T){
        queue<int> que;
        que.push(S);

        fill(begin(level), end(level), -1);
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
        if(u == T || flow == 0){
            return flow;
        }

        for(int &i = it[u]; i < (int)adj[u].size(); ++i){
            EdgeTo& e = adj[u][i];

            if(e.cap > 0 && level[u] + 1 == level[e.v]){
                int pushed = dfs_sendFlow(e.v, min(e.cap, flow), T);
                if(pushed > 0){
                    e.cap -= pushed;
                    adj[e.v][e.rev].cap += pushed;

                    return pushed;
                }
            }
        }

        return 0;
    }

    int getFlow(int S, int T){
        int ans = 0;
        while(bfs_findPath(S, T)){
            fill(begin(it), end(it), 0);
            while(int pushed = dfs_sendFlow(S, INT_MAX, T)){
                ans += pushed;
            }
        }

        return ans;
    }
};

struct House{
    int dolls, chores;
    vector<vector<int>> adj;

    House() = default;
    House(int d, int c): dolls(d), chores(c){
        adj.resize(dolls + chores + 1);
    }

    int size() const{ return dolls + chores; }

    int Doll(int id){ return id; }
    int Chore(int id){ return dolls + id; }

    int GetDoll(int id){ return id; }
    int GetChore(int id){ return id - dolls; }

    void input(){
        int d, c;
        cin >> d >> c;

        *this = House(d, c);
    }
};

House house;
int q;

bool check(int mid){
    int sz = house.size();
    MaxFlow Flow(sz + 1);
    for(int u = 1; u <= house.dolls; ++u) Flow.addEdge(0, house.Doll(u), mid);
    for(int v = 1; v <= house.chores; ++v) Flow.addEdge(house.Chore(v), sz + 1, 1);

    for(int u = 1; u <= house.dolls; ++u){
        for(int v: house.adj[u]){
            Flow.addEdge(u, v, 1);
        }
    }

    return Flow.getFlow(0, sz + 1) == house.chores;
}

void solve(){
    int l = 1, r = house.chores, res = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }

    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("349.INP","r",stdin);
    //freopen("349.OUT","w",stdout);

    house.input();
    cin >> q;

    for(int t = 1; t <= q; ++t){
        int i, j;
        cin >> i >> j;

        house.adj[house.Doll(i)].push_back(house.Chore(j));
    }

    solve();

    return 0;
}