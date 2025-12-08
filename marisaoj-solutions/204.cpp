#include<bits/stdc++.h>
using namespace std;
 
struct SegmentTree{
    struct Node{
        int value;
        int lazy;
 
        static Node Identity(){
            Node res;
            res.value = 1e9;
            res.lazy = 0;
 
            return res;
        }
 
        Node merge(const Node& other){
            Node res;
            res.value = min(this->value, other.value);
            res.lazy = 0;
            
            return res;
        }
    };
 
    int n;
    vector<Node> nodes;
    vector<int> arr;
 
    SegmentTree() = default;
    SegmentTree(int sz): n(sz){
        nodes.resize(sz * 4 + 1);
        arr.resize(sz + 1);
    }
 
    void push(int id){
        int delta = nodes[id].lazy;
        
        nodes[id << 1].value += delta;
        nodes[id << 1].lazy += delta;
 
        nodes[id << 1 | 1].value += delta;
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
            nodes[id].value += val;
            nodes[id].lazy += val;
            return;
        }
 
        int mid = (l + r) >> 1;
        push(id);
 
        update(id << 1, l, mid, u, v, val);
        update(id << 1 | 1, mid + 1, r, u, v, val);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }
 
    Node get(int id, int l, int r, int u, int v){
        if(v < l || r < u) return Node::Identity();
        if(u <= l && r <= v){
            return nodes[id];
        }
 
        int mid = (l + r) >> 1;
        push(id);
 
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }
};
 
const int MAXN = 1e5;
int n;
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int q;
    cin >> n >> q;
    SegmentTree seg(n);
    for(int i = 1; i <= n; ++i){
        cin >> seg.arr[i];
    }
    seg.build(1, 1, n);
 
    while(q--){
        int type;
        cin >> type;
 
        if(type == 1){
            int l, r, x;
            cin >> l >> r >> x;
 
            seg.update(1, 1, n, l, r, x);
        }
        else{
            int l, r;
            cin >> l >> r;
 
            cout << seg.get(1, 1, n, l, r).value << '\n';
        }
    }
 
    return 0;
}