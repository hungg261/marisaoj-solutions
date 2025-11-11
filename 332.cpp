#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int st[MAXN + 5], en[MAXN + 5], tour[MAXN * 2 + 5], m;
vector<int> adj[MAXN + 5];
int n;

void dfs(int u, int prev){
    tour[++m] = u;
    st[u] = m;

    for(int v: adj[u]){
        if(v == prev) continue;

        dfs(v, u);
    }

    tour[++m] = u;
    en[u] = m;
}

struct SegmentTree{
    struct Node{
        int value;
        int lazy;

        static Node Identity(){
            Node res;
            res.value = 0;
            res.lazy = 0;

            return res;
        }

        Node merge(const Node& other){
            Node res;
            res.value = this->value + other.value;
            res.lazy = 0;

            return res;
        }
    };

    int n;
    vector<int> arr;
    vector<Node> nodes;

    SegmentTree() = default;
    SegmentTree(int sz): n(sz){
        arr.resize(sz + 1, 0);
        nodes.resize(sz * 4 + 1);
    }

    void push(int id, int l, int r){
        int delta = nodes[id].lazy;
        int mid = (l + r) >> 1;

        nodes[id << 1].value += delta * (mid - l + 1);
        nodes[id << 1].lazy += delta;

        nodes[id << 1 | 1].value += delta * (r - mid);
        nodes[id << 1 | 1].lazy += delta;

        nodes[id].lazy = 0;
    }

    void build(int id, int l, int r){
        if(l == r){
            nodes[id].value = arr[l];
            nodes[id].lazy = 0;
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    void update(int id, int l, int r, int u, int v, int val){
        if(v < l || r < u) return;
        if(u <= l && r <= v){
            nodes[id].value += val * (r - l + 1);
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
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);

    // for(int i = 1; i <= n; ++i){
    //     cerr << i << ": " << st[i] << ' ' << en[i] << '\n';
    // }

    SegmentTree seg(m);
    seg.build(1, 1, m);

    for(int i = 1; i <= n; ++i){
        int cur;
        cin >> cur;

        cout << seg.get(1, 1, m, st[1], st[cur]).value << '\n';
        seg.update(1, 1, m, st[cur], st[cur], 1);
        seg.update(1, 1, m, en[cur], en[cur], -1);
    }

    return 0;
}