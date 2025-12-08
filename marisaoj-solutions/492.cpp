/******************************************************************************
Link: https://marisaoj.com/problem/492
Code: 492
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-13.33.49
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int MAXN = 100;
int n;
string S;
 
int dp[MAXN + 5][MAXN + 5];
 
char close(char o){
    if(o == '(') return ')';
    else if(o == '[') return ']';
    return '#';
}
 
void solve(){
    for(int i = 1; i <= n; ++i){
        dp[i][i] = 0;
        if(i > 1) dp[i - 1][i] = close(S[i - 1]) == S[i] ? 1 : 0;
    }
 
    for(int len = 3; len <= n; ++len){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;
 
            if(close(S[i]) == S[j]) dp[i][j] = dp[i + 1][j - 1] + 1;
            for(int k = i; k < j; ++k){
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }
 
    cout << n - 2 * dp[1][n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("492.INP","r",stdin);
    //freopen("492.OUT","w",stdout);
    cin >> S;
    n = S.size();
    S = '#' + S;
 
    solve();
 
    return 0;
}