#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5, MOD = 1e9 + 7;

const string SAMPLE = "#marisa";
const int SIZE = 6;
int dp[MAXN + 5][SIZE + 1];
string S;
int n;

void solve(){
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= SIZE; ++j){
            dp[i][j] = dp[i - 1][j];
        }

        for(int j = 1; j <= SIZE; ++j){
            if(S[i] == SAMPLE[j]){
                (dp[i][j] += dp[i - 1][j - 1]) %= MOD;
            }
        }
    }

    cout << dp[n][SIZE] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin >> S;
    n = S.size();
    S = '#' + S;

    solve();
    return 0;
}