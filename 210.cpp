#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
vector<int> nodes[MAXN * 2 + 5];
int arr[MAXN + 5], n;

void build(){
    for(int i = 0; i < n; ++i){
        nodes[i + n].push_back(arr[i + 1]);
    }

    for(int id = n - 1; id > 0; --id){
        nodes[id].resize(nodes[id << 1].size() + nodes[id << 1 | 1].size());
        merge(
            begin(nodes[id << 1]), end(nodes[id << 1]),
            begin(nodes[id << 1 | 1]), end(nodes[id << 1 | 1]),
            begin(nodes[id])
            );
    }
}

int get(int l, int r, int k){
    --l;
    l += n; r += n;

    int res = 0;
    while(l < r){
        if(l & 1){
            res += end(nodes[l]) - upper_bound(begin(nodes[l]), end(nodes[l]), k);
            l++;
        }
        if(r & 1){
            --r;
            res += end(nodes[r]) - upper_bound(begin(nodes[r]), end(nodes[r]), k);
        }
        l >>= 1; r >>= 1;
    }

    return res;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cerr.tie(0);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    build();

    while(q--){
        int l, r, k;
        cin >> l >> r >> k;

        cout << get(l, r, k) << '\n';
    }

    cerr << "Time elapsed: " << fixed << setprecision(10) << 1.0 * clock() / CLOCKS_PER_SEC << '\n';

    return 0;
}