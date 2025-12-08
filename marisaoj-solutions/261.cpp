/******************************************************************************
Link: https://marisaoj.com/problem/261
Code: 261
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-07-15.32.05
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
const int BLOCKSIZE = 316;
const int MAXN = 1e5, MAXQ = 1e5, MAXVAL = 1e5;
int cnt[BLOCKSIZE + 5][MAXVAL + 5];
int arr[MAXN + 5], n, q;
 
int counter[MAXN + 5], freq[MAXVAL + 5];
 
struct Query{
    int l, r, x;
    int idx;
 
    void input(int i){
        cin >> l >> r >> x;
        idx = i;
    }
 
    bool operator < (const Query& other){
        int block1 = (l - 1) / BLOCKSIZE + 1;
        int block2 = (other.l - 1) / BLOCKSIZE + 1;
 
        if(block1 == block2){
            return (block1 & 1) ? r < other.r : r > other.r;
        }
 
        return block1 < block2;
    }
} queries[MAXQ + 5];
 
void add(int val){
    --counter[freq[val]];
    ++freq[val];
    ++counter[freq[val]];
}
 
void pop(int val){
    --counter[freq[val]];
    --freq[val];
    ++counter[freq[val]];
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("261.INP","r",stdin);
    //freopen("261.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        add(arr[i]);
    }
 
    for(int i = 1; i <= q; ++i){
        queries[i].input(i);
    }
 
    sort(queries + 1, queries + q + 1);
 
    int pl = 1, pr = n;
    vector<int> ans(q + 1);
    for(int i = 1; i <= q; ++i){
        int l = queries[i].l, r = queries[i].r, x = queries[i].x;
 
        while(pl < l) pop(arr[pl++]);
        while(pl > l) add(arr[--pl]);
        while(pr < r) add(arr[++pr]);
        while(pr > r) pop(arr[pr--]);
 
        ans[queries[i].idx] = counter[x];
    }
 
    for(int i = 1; i <= q; ++i){
        cout << ans[i] << '\n';
    }
 
    return 0;
}