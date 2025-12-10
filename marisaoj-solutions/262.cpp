/******************************************************************************
Link: https://marisaoj.com/problem/262
Code: 262
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-09-20.52.48
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

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

    int get(int l, int r){
        if(l > r) return 0;
        return get(r) - get(l - 1);
    }
};

const int MAXN = 1e5, MAXQ = 1e5;
const int BLOCKSIZE = ceil(sqrt(MAXN));
int arr[MAXN + 5], n, q;

struct Query{
    int l, r;
    int idx;

    bool operator < (const Query& other){
        int block1 = l / BLOCKSIZE;
        int block2 = other.l / BLOCKSIZE;

        if(block1 == block2){
            return (block1 & 1) ? r < other.r : r > other.r;
        }

        return block1 < block2;
    }

    void input(int i){
        cin >> l >> r;
        idx = i;
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("262.INP","r",stdin);
    //freopen("262.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    vector<Query> queries(q);
    for(int i = 0; i < q; ++i){
        queries[i].input(i);
    }
    sort(begin(queries), end(queries));

    vector<int> res(q);
    int ans = 0;
    FenwickTree mark(n);

    int pl = 1, pr = 0;
    for(int i = 0; i < q; ++i){
        int l = queries[i].l, r = queries[i].r, idx = queries[i].idx;

        while(pl < l){
            ans -= mark.get(1, arr[pl] - 1);
            mark.update(arr[pl++], -1);
        }
        while(pr > r){
            ans -= mark.get(arr[pr] + 1, n);
            mark.update(arr[pr--], -1);
        }

        while(pl > l){
            mark.update(arr[--pl], 1);
            ans += mark.get(1, arr[pl] - 1);
        }
        while(pr < r){
            mark.update(arr[++pr], 1);
            ans += mark.get(arr[pr] + 1, n);
        }

        res[idx] = ans;
    }

    for(int i = 0; i < q; ++i){
        cout << res[i] << '\n';
    }

    return 0;
}
