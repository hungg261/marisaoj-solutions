/******************************************************************************
Link: https://cses.fi/problemset/task/1190
Code: 1190
Time (YYYY-MM-DD-hh.mm.ss): 2025-09-29-08.28.52
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
struct SegmentTree{
    struct Node{
        int Sum, maxPre, maxSuf, maxSum;
 
        static Node Identity(){
            Node res;
            res.Sum = 0;
            res.maxPre = res.maxSuf = res.maxSum = -1e9;
 
            return res;
        }
 
        Node merge(const Node& other){
            Node res;
            res.Sum = this->Sum + other.Sum;
            res.maxPre = max(this->maxPre, this->Sum + other.maxPre);
            res.maxSuf = max(other.maxSuf, this->maxSuf + other.Sum);
            res.maxSum = max({this->maxSum, other.maxSum, this->maxSuf + other.maxPre});
 
            return res;
        }
    };
 
    int n;
    vector<int> arr;
    vector<Node> nodes;
 
    SegmentTree() = default;
    SegmentTree(int sz): n(sz){
        arr.resize(sz + 1);
        nodes.resize(sz * 4 + 1);
    }
 
    void build(int id, int l, int r){
        if(l == r){
            nodes[id].Sum = arr[l];
            nodes[id].maxPre = nodes[id].maxSuf = nodes[id].maxSum = arr[l];
            return;
        }
 
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }
 
    void update(int id, int l, int r, int idx, int val){
        if(r < idx || idx < l) return;
        if(l == r){
            nodes[id].Sum = val;
            nodes[id].maxPre = nodes[id].maxSuf = nodes[id].maxSum = val;
            return;
        }
 
        int mid = (l + r) >> 1;
        update(id << 1, l, mid, idx, val);
        update(id << 1 | 1, mid + 1, r, idx, val);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }
 
    Node get(int id, int l, int r, int u, int v){
        if(v < l || r < u) return Node::Identity();
        if(u <= l && r <= v) return nodes[id];
 
        int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }
};
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    // freopen("1190.INP","r",stdin);
    // freopen("1190.OUT","w",stdout);
    int n, m;
    cin >> n;
 
    SegmentTree seg(n);
    for(int i = 1; i <= n; ++i){
        cin >> seg.arr[i];
    }
    seg.build(1, 1, n);
 
    cin >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
 
        cout << seg.get(1, 1, n, a, b).maxSum << '\n';
    }
 
    return 0;
}