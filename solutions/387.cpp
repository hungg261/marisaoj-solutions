#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int INF = 2e9 + 5;
int h[MAXN + 5],
    sz[MAXN + 5],
    par[MAXN + 5],

    ChainHead[MAXN + 5],
    ChainID[MAXN + 5],

    Arr[MAXN + 5],
    Pos[MAXN + 5],
    LastPos[MAXN + 5],
    curChain = 1, curPos = 0;

vector<int> adj[MAXN + 5];
int c[MAXN + 5];
int n;

void dfs(int u, int prev){
    sz[u] = 1;
    for(int v: adj[u]){
        if(v == prev) continue;

        h[v] = h[u] + 1;
        par[v] = u;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void Hld(int u, int prev){
    if(!ChainHead[curChain]) ChainHead[curChain] = u;
    ChainID[u] = curChain;

    Arr[++curPos] = u;
    Pos[u] = curPos;

    int nxt = -1;
    for(int v: adj[u]){
        if(v == prev) continue;

        if(nxt == -1 || sz[nxt] < sz[v]) nxt = v;
    }
    if(nxt != -1) Hld(nxt, u);

    for(int v: adj[u]){
        if(v == prev || v == nxt) continue;

        ++curChain;
        Hld(v, u);
    }

    LastPos[u] = curPos;
}

struct Node{
    int Sum, maxPre, maxSuf, maxSum;

    static Node Identity(){
        Node res;
        res.Sum = 0;
        res.maxPre = res.maxSuf = res.maxSum = 0;

        return res;
    }

    void setValue(int val, int l, int r){
        Sum = val * (r - l + 1);
        if(val >= 0){
            maxPre = val * (r - l + 1);
            maxSuf = val * (r - l + 1);
            maxSum = val * (r - l + 1);
        }
        else{
            maxPre = 0;
            maxSuf = 0;
            maxSum = 0;
        }
    }

    Node merge(const Node& other){
        Node res;
        res.Sum = this->Sum + other.Sum;
        res.maxPre = max(this->maxPre, this->Sum + other.maxPre);
        res.maxSuf = max(other.maxSuf, this->maxSuf + other.Sum);
        res.maxSum = max({this->maxSum, other.maxSum, this->maxSuf + other.maxPre});

        return res;
    }

    void debug(){
        cerr << Sum << ' ' << maxPre << ' ' << maxSuf << ' ' << maxSum << '\n';
    }
};

Node nodes[MAXN * 4 + 5];
int lazy[MAXN * 4 + 5];

void build(int id, int l, int r){
    lazy[id] = INF;
    if(l == r){
        nodes[id].setValue(c[Arr[l]], l, r);
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
}

void down(int id, int l, int r){
    int t = lazy[id];
    if(t == INF) return;

    int mid = (l + r) >> 1;
    nodes[id << 1].setValue(t, l, mid);
    lazy[id << 1] = t;

    nodes[id << 1 | 1].setValue(t, mid + 1, r);
    lazy[id << 1 | 1] = t;

    lazy[id] = INF;
}

void update(int id, int l, int r, int u, int v, int val){
    if(r < u || v < l) return;
    if(u <= l && r <= v){
        nodes[id].setValue(val, l, r);
        lazy[id] = val;
        return;
    }

    down(id, l, r);

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
    nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
}

Node get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return Node::Identity();
    if(u <= l && r <= v) return nodes[id];

    down(id, l, r);

    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
}

int query1(int u, int v){
    Node resU = Node::Identity(), resV = Node::Identity();
    
    while(ChainID[u] != ChainID[v]){
        if(ChainID[u] > ChainID[v]){
            resU = get(1, 1, n, Pos[ChainHead[ChainID[u]]], Pos[u]).merge(resU);
            u = par[ChainHead[ChainID[u]]];
        }
        else{
            resV = get(1, 1, n, Pos[ChainHead[ChainID[v]]], Pos[v]).merge(resV);
            v = par[ChainHead[ChainID[v]]];
        }
    }

    if(h[u] > h[v]){
        swap(u, v);
        swap(resU, resV);
    }
    resV = get(1, 1, n, Pos[u], Pos[v]).merge(resV);

    int res = max({resU.maxSum, resV.maxSum, resU.maxPre + resV.maxPre});
    return res;
}

void query2(int u, int v, int x){
    while(ChainID[u] != ChainID[v]){
        if(ChainID[u] > ChainID[v]){
            update(1, 1, n, Pos[ChainHead[ChainID[u]]], Pos[u], x);
            u = par[ChainHead[ChainID[u]]];
        }
        else{
            update(1, 1, n, Pos[ChainHead[ChainID[v]]], Pos[v], x);
            v = par[ChainHead[ChainID[v]]];
        }
    }

    if(h[u] > h[v]) swap(u, v);
    update(1, 1, n, Pos[u], Pos[v], x);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> c[i];
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    Hld(1, 0);
    build(1, 1, n);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int u, v;
            cin >> u >> v;

            cout << query1(u, v) << '\n';
        }
        else{
            int u, v, x;
            cin >> u >> v >> x;

            query2(u, v, x);
        }
    }

    return 0;
}