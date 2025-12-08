/******************************************************************************
Link: https://marisaoj.com/problem/570
Code: 570
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-14.27.24
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 50;
int n;
int A[MAXN + 5][MAXN + 5], arr[MAXN * 2 + 5][MAXN * 2 + 5];
int idx[MAXN * 2 + 5];
 
void transform_input(){
    for(int i = 1; i <= n; ++i){
        int x = i, y = 1;
        while(x >= 1){
            arr[i][++idx[i]] = A[x][y];
            --x;
            ++y;
        }
    }
    for(int j = 2; j <= n; ++j){
        int x = n, y = j;
        while(y <= n){
            arr[n + j - 1][++idx[n + j - 1]] = A[x][y];
            --x;
            ++y;
        }
    }
}
 
int dp[MAXN * 2 + 5][MAXN * 2 + 5][MAXN * 2 + 5];
void solve(){
    for(int i = 2; i <= n; ++i){
        for(int x = 1; x <= idx[i]; ++x){
            dp[i][x][x + 1] = max({
                dp[i - 1][x - 1][x],
                dp[i - 1][x - 1][x + 1],
                dp[i - 1][x][x + 1]
                    }) + arr[i][x] + arr[i][x + 1];
 
            for(int y = x + 2; y <= idx[i]; ++y){
                dp[i][x][y] = max({
                    dp[i - 1][x - 1][y - 1],
                    dp[i - 1][x - 1][y],
                    dp[i - 1][x][y - 1],
                    dp[i - 1][x][y]
                        }) + arr[i][x] + arr[i][y];
            }
        }
    }
 
    for(int i = n + 1; i <= n * 2 - 1 - 1; ++i){
        for(int x = 1; x <= idx[i]; ++x){
            dp[i][x][x + 1] = max({
                dp[i - 1][x][x + 1],
                dp[i - 1][x][x + 2],
                dp[i - 1][x + 1][x + 2]
                    }) + arr[i][x] + arr[i][x + 1];
 
            for(int y = x + 2; y <= idx[i]; ++y){
                dp[i][x][y] = max({
                    dp[i - 1][x][y],
                    dp[i - 1][x][y + 1],
                    dp[i - 1][x + 1][y],
                    dp[i - 1][x + 1][y + 1]
                        }) + arr[i][x] + arr[i][y];
            }
        }
    }
 
    int ans = 0;
    for(int x = 1; x <= idx[n * 2 - 2]; ++x){
        for(int y = x + 1; y <= idx[n * 2 - 2]; ++y){
            ans = max(ans, dp[n * 2 - 2][x][y]);
        }
    }
    ans += arr[1][1] + arr[n * 2 - 1][1];
 
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("570.INP","r",stdin);
    //freopen("570.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            cin >> A[i][j];
        }
    }
 
    transform_input();
    solve();
 
    return 0;
}
 
/*
4
1 0 0 4
0 0 6 0
0 0 0 0
5 0 0 0
 
5
6 6 4 0 4
6 2 1 7 7
8 1 0 7 9
0 4 0 2 8
1 3 1 6 4
*/