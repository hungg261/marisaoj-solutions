#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MOD = 1e9 + 7;
const int MAXN = 5000;
int n;
string S;
int dp[MAXN + 5][MAXN + 5];
 
void solve(){
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= n; ++j){
            if(S[i] == '?' || S[i] == '('){
                if(j > 0) dp[i][j] += dp[i - 1][j - 1];
            }
            if(S[i] == '?' || S[i] == ')'){
                dp[i][j] += dp[i - 1][j + 1];
            }
 
            dp[i][j] %= MOD;
        }
    }
 
    cout << dp[n][0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S;
    n = S.size();
    S = '#' + S;
 
    solve();
 
    return 0;
}