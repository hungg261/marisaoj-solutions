/******************************************************************************
Link: https://marisaoj.com/problem/59
Code: 59
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-12.46.14
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e5;
int n, pre[MAXN + 5];

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("59.INP","r",stdin);
    //freopen("59.OUT","w",stdout);
    int q;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        pre[i] = pre[i - 1] + cur;
    }

    while(q--){
        int l, r;
        cin >> l >> r;

        cout << pre[r] - pre[l - 1] << '\n';
    }

    return 0;
}
