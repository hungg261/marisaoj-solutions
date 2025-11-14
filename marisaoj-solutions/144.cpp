#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
int A[MAXN + 5], B[MAXN + 5], n;
int dp[MAXN + 5][MAXN + 5];

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> A[i];
    for(int i = 1; i <= n; ++i) cin >> B[i];

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(A[i] == B[j]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }
        }
    }

    cout << dp[n][n] << '\n';
    
    return 0;
}