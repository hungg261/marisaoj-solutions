/******************************************************************************
Link: https://cses.fi/problemset/task/1734
Code: 1734
Time (YYYY-MM-DD-hh.mm.ss): 2025-09-27-23.43.39
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct FenwickTree{
    vector<int> BIT;
    int n;

    FenwickTree() = default;
    FenwickTree(int sz): n(sz){
        BIT.resize(sz + 1, 0);
    }

    void update(int idx, int val){
        for(int i = idx; i <= n; i += i & -i) BIT[i] += val;
    }

    int get(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i) res += BIT[i];
        return res;
    }

    int get(int l, int r){ return get(r) - get(l - 1); }
};

const int MAXN = 2e5;
int arr[MAXN + 5], temp[MAXN + 5], n, q;

void compress(){
    for(int i = 1; i <= n; ++i) temp[i] = arr[i];
    sort(temp + 1, temp + n + 1);

    for(int i = 1; i <= n; ++i){
        arr[i] = lower_bound(temp + 1, temp + n + 1, arr[i]) - temp;
    }
}

vector<pair<int, int>> queries[MAXN + 5];
int mp[MAXN + 5];

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("1734.INP","r",stdin);
    //freopen("1734.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    compress();

    for(int i = 1; i <= q; ++i){
        int a, b;
        cin >> a >> b;

        queries[a].push_back({b, i});
    }

    FenwickTree fwt(n);
    vector<int> res(q + 1);
    for(int i = n; i >= 1; --i){
        if(mp[arr[i]] != 0) fwt.update(mp[arr[i]], -1);
        mp[arr[i]] = i;
        fwt.update(i, 1);

        for(const pair<int, int>& qr: queries[i]){
            res[qr.second] = fwt.get(qr.first);
        }
    }

    for(int i = 1; i <= q; ++i){
        cout << res[i] << ' ';
    }

    return 0;
}