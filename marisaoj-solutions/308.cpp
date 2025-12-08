#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5;
 
struct SegmentTree{
    struct Node{
        int value, idx;
 
        Node() = default;
 
        static Node Identity(){
            Node res;
            res.value = 1e18;
 
            return res;
        }
 
        Node merge(const Node& other){
            Node res;
            if(this->value < other.value){
                res.value = this->value;
                res.idx = this->idx;
            }
            else if(this->value > other.value){
                res.value = other.value;
                res.idx = other.idx;
            }
            else{
                res.value = this->value;
                res.idx = min(this->idx, other.idx);
            }
 
            return res;
        }
    };
 
    vector<int> arr;
    vector<Node> nodes;
    int n;
 
    SegmentTree() = default;
    SegmentTree(int sz): n(sz){
        arr.resize(n + 1);
        nodes.resize(sz * 4 + 1);
    }
 
    void build(int id, int l, int r){
        if(l == r){
            nodes[id].value = arr[l];
            nodes[id].idx = l;
            return;
        }
 
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }
 
    Node query(int id, int l, int r, int u, int v){
        if(r < u || v < l) return Node::Identity();
        if(u <= l && r <= v) return nodes[id];
 
        int mid = (l + r) >> 1;
        return query(id << 1, l, mid, u, v).merge(query(id << 1 | 1, mid + 1, r, u, v));
    }
 
    void build(){ build(1, 1, n); }
    Node query(int u, int v){ return query(1, 1, n, u, v); }
 
    int operator[] (int idx) const{ return this->arr[idx]; }
    int& operator[] (int idx){ return this->arr[idx]; }
};
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
 
    SegmentTree seg(n);
    for(int i = 1; i <= n; ++i){
        cin >> seg[i];
    }
    seg.build();
 
    for(int qr = 1; qr <= q; ++qr){
        int l, r;
        cin >> l >> r;
 
        int res = seg.query(l, r).idx;
        cout << res << '\n';
    }
 
    return 0;
}