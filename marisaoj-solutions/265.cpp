/******************************************************************************
Link: https://marisaoj.com/problem/265
Code: 265
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-10-16.07.49
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct FenwickTree{
    int n;
    vector<int> BIT;

    FenwickTree() = default;
    FenwickTree(int sz){ n = sz; BIT.resize(sz + 1, 0); }

    void update(int idx, int val){
        if(idx <= 0) return;

        for(int i = idx; i <= n; i += i & -i){
            BIT[i] += val;
        }
    }

    int get(int idx){
        if(idx <= 0) return 0;

        int res = 0;
        for(int i = idx; i > 0; i -= i & -i){
            res += BIT[i];
        }
        return res;
    }

    int get(int l, int r){ return get(r) - get(l - 1); }
};

const int MAXN = 1e5, BLOCKSIZE = ceil(sqrt(MAXN)), BLOCKCNT = MAXN / BLOCKSIZE + 1;
int n, q, arr[MAXN + 5];
FenwickTree blocks[BLOCKCNT + 1];

int query(int l, int r, int u, int v){
    int blockL = (l - 1) / BLOCKSIZE + 1,
        blockR = (r - 1) / BLOCKSIZE + 1;

    int res = 0;
    for(int b = blockL + 1; b <= blockR - 1; ++b){
        res += blocks[b].get(u, v);
    }

    auto check = [&u, &v](const int& val){
        return u <= val && val <= v;
    };

    if(blockL == blockR){
        for(int i = l; i <= r; ++i) res += check(arr[i]);
    }
    else{
        for(int i = l; i <= blockL * BLOCKSIZE; ++i) res += check(arr[i]);
        for(int i = (blockR - 1) * BLOCKSIZE + 1; i <= r; ++i) res += check(arr[i]);
    }

    return res;
}

void operate(int x, int y){
    int blockX = (x - 1) / BLOCKSIZE + 1,
        blockY = (y - 1) / BLOCKSIZE + 1;

    blocks[blockX].update(arr[x], -1);
    blocks[blockX].update(arr[y], 1);

    blocks[blockY].update(arr[y], -1);
    blocks[blockY].update(arr[x], 1);

    swap(arr[x], arr[y]);
}

void solve(){
    int ans = 0;
    while(q--){
        int x, y;
        cin >> x >> y;

        ans += -query(x + 1, y - 1, 1, arr[x] - 1);
        ans += query(x + 1, y - 1, arr[x] + 1, n);
        ans += query(x + 1, y - 1, arr[y] + 1, n);
        ans += -query(x + 1, y - 1, 1, arr[y] - 1);

        if(arr[x] < arr[y]) ++ans;
        else --ans;

        cout << ans << '\n';

        operate(x, y);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("265.INP","r",stdin);
    //freopen("265.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= BLOCKCNT; ++i) blocks[i] = FenwickTree(n);
    for(int i = 1; i <= n; ++i){
        arr[i] = i;

        int b = (i - 1) / BLOCKSIZE + 1;
        blocks[b].update(arr[i], 1);
    }

    solve();

    return 0;
}
