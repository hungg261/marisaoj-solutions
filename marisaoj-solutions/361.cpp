#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 2e5;
pair<int, int> nodes[MAXN * 4 + 5];
 
void update(int id, int l, int r, int idx, int val){
    if(r < idx || idx < l) return;
    if(l == r){
        nodes[id] = {val, idx};
        return;
    }
 
    int mid = (l + r) >> 1;
    update(id << 1, l, mid, idx, val);
    update(id << 1 | 1, mid + 1, r, idx, val);
    nodes[id] = min(nodes[id << 1], nodes[id << 1 | 1]);
}
 
pair<int, int> get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return {(int)1e9+5, -1};
    if(u <= l && r <= v) return nodes[id];
 
    int mid = (l + r) >> 1;
    return min(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}
 
int arr[MAXN + 5], n, q, pre[MAXN + 5];
vector<pair<int, int>> queries[MAXN + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        update(1, 1, n, i, 1e9);
    }
    for(int i = 1; i <= q; ++i){
        int a, b;
        cin >> a >> b;
 
        queries[b].push_back({a, i});
    }
 
    vector<int> res(q + 1);
    for(int i = 1; i <= n; ++i){
        if(pre[arr[i]]) update(1, 1, n, pre[arr[i]], 1e9);
        update(1, 1, n, i, pre[arr[i]]);
        pre[arr[i]] = i;
 
        for(const pair<int, int>& qr: queries[i]){
            pair<int, int> minL = get(1, 1, n, qr.first, i);
            if(minL.first < qr.first){
                res[qr.second] = arr[minL.second];
            }
            else res[qr.second] = 0;
        }
    }
 
    for(int i = 1; i <= q; ++i){
        cout << res[i] << '\n';
    }
 
    return 0;
}
 
//10 10
//1 3 4 2 2 4 3 1 2 1
//1 5
//3 5
//3 6
//1 10
//8 10
//6 10
//3 7
//1 4
//1 3
//1 2