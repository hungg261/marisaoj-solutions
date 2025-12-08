#include<bits/stdc++.h>
#define int long long
using namespace std;
 
struct SegmentTree{
    struct Node{
        int cnt1;
        int lazy;
 
        Node(int _cnt1 = 0, int _lazy = 0): cnt1(_cnt1), lazy(_lazy){}
 
        Node merge(const Node& other){
            Node res;
            res.cnt1 = this->cnt1 + other.cnt1;
            res.lazy = 0;
 
            return res;
        }
    };
 
    vector<Node> nodes;
    int n;
 
    SegmentTree() = default;
    SegmentTree(int sz): n(sz){ nodes.resize(sz * 4 + 1); }
 
    void build(int id, int l, int r, bool arr[]){
        if(l == r){
            nodes[id].cnt1 = arr[l];
            return;
        }
 
        int mid = (l + r) >> 1;
        build(id << 1, l, mid, arr);
        build(id << 1 | 1, mid + 1, r, arr);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }
 
    void push(int id, int l, int r){
        int t = nodes[id].lazy;
        if(t % 2 == 0) return;
 
        int mid = (l + r) >> 1;
 
        nodes[id << 1].cnt1 = (mid - l + 1) - nodes[id << 1].cnt1;
        nodes[id << 1].lazy += t;
 
        nodes[id << 1 | 1].cnt1 = (r - mid) - nodes[id << 1 | 1].cnt1;
        nodes[id << 1 | 1].lazy += t;
 
        nodes[id].lazy = 0;
    }
 
    void switch_bits(int id, int l, int r, int u, int v){
        if(v < l || r < u) return;
        if(u <= l && r <= v){
            nodes[id].cnt1 = (r - l + 1) - nodes[id].cnt1;
            nodes[id].lazy++;
            return;
        }
 
        push(id, l, r);
 
        int mid = (l + r) >> 1;
        switch_bits(id << 1, l, mid, u, v);
        switch_bits(id << 1 | 1, mid + 1, r, u, v);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }
 
    Node get(int id, int l, int r, int u, int v){
        if(v < l || r < u) return Node();
        if(u <= l && r <= v) return nodes[id];
 
        push(id, l, r);
 
        int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }
};
 
const int MAXN = 1e5, BITLENGTH = 30;
bool prefix[BITLENGTH + 1][MAXN + 5];
int arr[MAXN + 5], n, q;
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
 
    int pref = 0;
    for(int i = 1; i <= n; ++i){
        int cur;
        cin >> cur;
 
        pref ^= cur;
 
        for(int j = 0; j <= BITLENGTH; ++j){
            prefix[j][i] = pref >> j & 1;
        }
 
        arr[i] = cur;
    }
 
    // for(int j = 0; j <= BITLENGTH; ++j){
    //     for(int i = 1; i <= n; ++i){
    //         cerr << prefix[j][i] << ' ';
    //     }
    //     cerr << '\n';
    // }
 
    vector<SegmentTree> segs(BITLENGTH + 1, SegmentTree(n));
    for(int j = 0; j <= BITLENGTH; ++j){
        segs[j].build(1, 1, n, prefix[j]);
    }
    
    
    while(q--){
        int type;
        cin >> type;
 
        if(type == 1){
            int i, x;
            cin >> i >> x;
 
            int delta = x ^ arr[i];
            for(int j = 0; j <= BITLENGTH; ++j){
                if(delta >> j & 1){
                    segs[j].switch_bits(1, 1, n, i, n);
                }
            }
 
            arr[i] = x;
        }
        else{
            int l, r;
            cin >> l >> r;
 
            int ans = 0;
            for(int j = 0; j <= BITLENGTH; ++j){
                int c = segs[j].get(1, 1, n, max(1LL, l - 1), r).cnt1;
 
                ans += c * (r - l + 2 - c) * (1LL << j);
            }
 
            cout << ans << '\n';
        }
    }
 
    return 0;
}