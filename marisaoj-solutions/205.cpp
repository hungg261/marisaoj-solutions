#include<bits/stdc++.h>
#define int long long
using namespace std;

const int INF = 1e18;
const int MAXN = 1e5;
struct Interval{
    int l, r, c;

    bool operator < (const Interval& other){
        return this->r < other.r;
    }
};

struct SegmentTree{
    struct Node{
        int value;

        static Node Identity(){
            Node res;
            res.value = 1e18;

            return res;
        }

        Node merge(const Node& other){
            Node res;
            res.value = min(this->value, other.value);

            return res;
        }
    };

    vector<int> arr;
    vector<Node> nodes;
    int n;

    SegmentTree() = default;
    SegmentTree(int sz): n(sz){
        arr.resize(sz + 1);
        nodes.resize(sz * 4 + 1);
    }

    void build(int id, int l, int r){
        if(l == r){
            nodes[id].value = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    void update(int id, int l, int r, int idx, int val){
        if(idx < l || r < idx) return;
        if(l == r){
            nodes[id].value = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        update(id << 1, l, mid, idx, val);
        update(id << 1 | 1, mid + 1, r, idx, val);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    Node get(int id, int l, int r, int u, int v){
        if(r < u || v < l) return Node::Identity();
        if(u <= l && r <= v) return nodes[id];

        int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }

    void build(){ build(1, 1, n); }
    void update(int idx, int val){ arr[idx] = val; update(1, 1, n, idx, val); }
    Node get(int u, int v){ return get(1, 1, n, u, v); }

    int& operator[] (int idx){ return arr[idx]; }
    int operator[] (int idx) const{ return arr[idx]; }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    
    vector<Interval> intervals(q + 1);
    for(int i = 1; i <= q; ++i){
        cin >> intervals[i].l >> intervals[i].r >> intervals[i].c;
        ++intervals[i].l; ++intervals[i].r;
    }
    sort(begin(intervals) + 1, end(intervals));

    SegmentTree dp(n + 1);
    for(int i = 2; i <= n + 1; ++i) dp[i] = INF;
    dp[1] = 0;
    dp.build();

    for(int i = 1; i <= q; ++i){
        int l = intervals[i].l, r = intervals[i].r,
            c = intervals[i].c;
        
        int newCost = dp.get(l - 1, r).value + c;
        if(newCost < dp[r]){
            dp.update(r, newCost);
        }
    }

    // for(int i = 1; i <= n + 1; ++i){
    //     cerr << dp[i] << ' ';
    // }

    if(dp[n + 1] == INF) cout << "-1\n";
    else cout << dp[n + 1] << '\n';

    return 0;
}