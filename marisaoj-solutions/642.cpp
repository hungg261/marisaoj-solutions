/******************************************************************************
Link: https://marisaoj.com/problem/642
Code: 642
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-08-19.12.50
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5;
struct SegmentTree1{
    static const int INF = 1e18;
    struct Node{
        int minVal, cnt;
        int lazy;

        Node(int _minV = 0, int _cnt = 1, int _lazy = 0): minVal(_minV), cnt(_cnt), lazy(_lazy){};

        static Node Identity(){
            Node res;
            res.minVal = INF;
            res.cnt = 0;
            res.lazy = 0;
            return res;
        }

        Node merge(const Node& other) const{
            Node res;
            res.lazy = 0;

            if(minVal == other.minVal){
                res.minVal = minVal;
                res.cnt = cnt + other.cnt;
            }
            else if(minVal < other.minVal){
                res.minVal = minVal;
                res.cnt = cnt;
            }
            else{
                res.minVal = other.minVal;
                res.cnt = other.cnt;
            }

            return res;
        }

        void debug(){
            cerr << minVal << ' ' << cnt << ' ' << lazy << '\n';
        }
    };

    int n;
    vector<Node> nodes;

    SegmentTree1() = default;
    SegmentTree1(int _n): n(_n){
        nodes.resize(_n * 4 + 5);
    }

    void build(int id, int l, int r){
        if(l == r){
            nodes[id].minVal = 0;
            nodes[id].cnt = 1;
            nodes[id].lazy = 0;
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    void push(int id, int l, int r){
        if(l == r) return;

        int mid = (l + r) >> 1;
        int &t = nodes[id].lazy;

        nodes[id << 1].minVal += t;
        nodes[id << 1].lazy += t;

        nodes[id << 1 | 1].minVal += t;
        nodes[id << 1 | 1].lazy += t;

        t = 0;
    }

    void update(int id, int l, int r, int u, int v, int val){
        if(v < l || r < u) return;
        if(u <= l && r <= v){
            nodes[id].minVal += val;
            nodes[id].lazy += val;
            return;
        }

        push(id, l, r);

        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v, val);
        update(id << 1 | 1, mid + 1, r, u, v, val);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    Node get(int id, int l, int r, int u, int v){
        if(v < l || r < u) return Node::Identity();
        if(u <= l && r <= v) return nodes[id];

        push(id, l, r);

        int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }

    void build(){ build(1, 1, n); }
    void update(int u, int v, int val){ update(1, 1, n, u, v, val); }
    Node get(int u, int v){ return get(1, 1, n, u, v); }
    Node getAll(){ return nodes[1]; }
};

int n, q;
vector<int> adj[MAXN + 5];

int h[MAXN + 5], par[MAXN + 5], sz[MAXN + 5];
int ChainHead[MAXN + 5],
    ChainID[MAXN + 5],

    Pos[MAXN + 5],
    Arr[MAXN + 5],

    curChain = 1,
    curPos = 0;

void dfs(int u, int prv){
    sz[u] = 1;

    for(int v: adj[u]){
        if(v == prv) continue;

        h[v] = h[u] + 1;
        par[v] = u;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void Hld(int u, int prv){
    if(!ChainHead[curChain]) ChainHead[curChain] = u;
    ChainID[u] = curChain;

    Pos[u] = ++curPos;
    Arr[curPos] = u;

    int nxt = -1;
    for(int v: adj[u]){
        if(v == prv) continue;

        if(nxt == -1 || sz[v] > sz[nxt]) nxt = v;
    }

    if(nxt != -1) Hld(nxt, u);

    for(int v: adj[u]){
        if(v == prv || v == nxt) continue;

        ++curChain;
        Hld(v, u);
    }
}

SegmentTree1 segg;

void Update(int u, int v, int k){
    while(ChainID[u] != ChainID[v]){
        if(h[ChainHead[ChainID[u]]] < h[ChainHead[ChainID[v]]]) swap(u, v);

        segg.update(Pos[ChainHead[ChainID[u]]], Pos[u], k);
        u = par[ChainHead[ChainID[u]]];
    }

    if(h[u] > h[v]) swap(u, v);
    segg.update(Pos[u], Pos[v], k);
}

int minQuery(int u, int v){
    int res = SegmentTree1::INF;
    while(ChainID[u] != ChainID[v]){
        if(h[ChainHead[ChainID[u]]] < h[ChainHead[ChainID[v]]]) swap(u, v);

        res = min(res, segg.get(Pos[ChainHead[ChainID[u]]], Pos[u]).minVal);
        u = par[ChainHead[ChainID[u]]];
    }

    if(h[u] > h[v]) swap(u, v);

    res = min(res, segg.get(Pos[u], Pos[v]).minVal);
    return res;
}

void solve(){
    while(q--){
        int type;
        cin >> type;

        int u, v, k;
        cin >> u >> v >> k;

        if(type == 1){
            Update(u, v, k);
        }
        else{
            k = -min(k, minQuery(u, v));
            Update(u, v, k);
        }

        SegmentTree1::Node res = segg.get(1, n);
        int ans = 0;
        if(res.minVal > 0) ans = n;
        else ans = n - res.cnt;

        cout << ans << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("642.INP","r",stdin);
    //freopen("642.OUT","w",stdout);

    cin >> n >> q;
    segg = SegmentTree1(n);
    segg.build();

    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    Hld(1, 0);

    solve();

    return 0;
}
