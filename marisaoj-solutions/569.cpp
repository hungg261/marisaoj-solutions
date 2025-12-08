#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1000;
string s;
int n;
 
int prv[MAXN + 5];
int dp[MAXN + 5][MAXN + 5];
 
void solve(){
    for(int i = 1; i <= n; ++i){
        dp[i][i] = 1;
    }
 
    for(int len = 2; len <= n; ++len){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;
 
            dp[i][j] = dp[i][j - 1] + 1;
 
            int k = j;
            while(i <= k){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j - 1]);
                k = prv[k];
            }
        }
    }
 
    cout << dp[1][n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    n = s.size();
    s = '#' + s;
 
    int last[26] = {};
    for(int i = 1; i <= n; ++i){
        prv[i] = last[s[i] - 'a'];
        last[s[i] - 'a'] = i;
    }
 
    solve();
 
    return 0;
}