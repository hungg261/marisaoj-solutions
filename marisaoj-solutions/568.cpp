#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1000;
string s;
int n;
 
int dp[MAXN + 5][MAXN + 5];
void solve(){
    for(int i = 1; i <= n; ++i){
        dp[i][i] = 1;
    }
 
    for(int len = 2; len <= n; ++len){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;
 
            if(s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
            else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
 
    cout << n - dp[1][n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    n = s.size();
    s = '#' + s;
 
    solve();
 
    return 0;
}