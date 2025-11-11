/******************************************************************************
Link: https://marisaoj.com/problem/221
Code: 221
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-11-20.51.42
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10, MAXMASK = 1 << (MAXN * 2);
int n, A[MAXN * 2][MAXN * 2];
int dp[MAXMASK];

void solve(){
    memset(dp, -0x3f, sizeof dp);
    dp[0] = 0;
    for(int mask = 1; mask < (1 << (n * 2)); ++mask){
        for(int i = 0; i < n * 2; ++i){
            if(mask >> i & 1){
                for(int j = 0; j < n * 2; ++j){
                    if(mask >> j & 1){
                        dp[mask] = max(dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] + A[i][j]);
                    }
                }
            }
        }
    }

    cout << dp[(1 << (n * 2)) - 1] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("221.INP","r",stdin);
    //freopen("221.OUT","w",stdout);
    cin >> n;
    for(int i = 0; i < n * 2; ++i){
        for(int j = 0; j < n * 2; ++j){
            cin >> A[i][j];
        }
    }

    solve();

    return 0;
}
