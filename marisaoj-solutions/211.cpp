#include<bits/stdc++.h>
#define cerr if(false)cerr
using namespace std;

struct SegmentTree{
    struct Node{
        int cnt[3];
        int lazy;

        static Node Identity(){
            Node res;
            res.cnt[0] = res.cnt[1] = res.cnt[2] = 0;
            res.lazy = 0;

            return res;
        }

        void shift(){
            int temp = cnt[0];
            cnt[0] = cnt[2];
            cnt[2] = cnt[1];
            cnt[1] = temp;
        }

        Node merge(const Node& other){
            Node res;
            for(int du = 0; du < 3; ++du)
                res.cnt[du] = this->cnt[du] + other.cnt[du];
            res.lazy = 0;

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

    void push(int id){
        int delta = nodes[id].lazy % 3;

        nodes[id << 1].lazy += delta;
        nodes[id << 1 | 1].lazy += delta;

        for(int rot = 1; rot <= delta; ++rot){
            nodes[id << 1].shift();
            nodes[id << 1 | 1].shift();
        }

        nodes[id].lazy = 0;
    }

    void build(int id, int l, int r){
        if(l == r){
            nodes[id].cnt[arr[l] % 3]++;
            nodes[id].lazy = 0;
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    void update(int id, int l, int r, int u, int v){
        cerr << id << ' ' << l << ' ' << r << '\n';
        if(v < l || r < u) return;
        if(u <= l && r <= v){
            nodes[id].shift();
            nodes[id].lazy++; 
            return;
        }

        push(id);
        
        int mid = (l + r) >> 1;
        update(id << 1, l, mid, u, v);
        update(id << 1 | 1, mid + 1, r, u, v);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    Node get(int id, int l, int r, int u, int v){
        if(v < l || r < u) return Node::Identity();
        if(u <= l && r <= v) return nodes[id];

        push(id);

        int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }
};

const int MAXN = 1e5;
int n, q;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
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
            int l, r;
            cin >> l >> r;

            seg.update(1, 1, n, l, r);
        }
        else{
            int l, r;
            cin >> l >> r;

            cout << seg.get(1, 1, n, l, r).cnt[0] << '\n';
        }
    }

    return 0;
}