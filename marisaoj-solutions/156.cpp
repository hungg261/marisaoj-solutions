#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 100, MAXVAL = 1e4;
int knapsack(int S,
            vector<int> W,
            vector<int> V){
    vector<vector<int>> dp(2, vector<int>(S + 1, -1e9));
 
    int n = (int) W.size() - 1;
 
    dp[0][0] = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= S; ++j){
            if(j >= W[i]){
                dp[1][j] = max(dp[1][j], dp[0][j - W[i]] + V[i]);
            }
            dp[1][j] = max(dp[1][j], dp[0][j]);
        }
 
        dp[0] = dp[1];
    }
 
    int ans = 0;
    for(int j = 0; j <= S; ++j){
        ans = max(ans, dp[1][j]);
    }
    return ans;
}
 
int n, S;
int w[MAXN + 5], v[MAXN + 5], a[MAXN + 5];
 
void solve(){
    vector<int> W = {0}, V = {0};
    for(int i = 1; i <= n; ++i){
        int j = 0;
        while((1 << j) < a[i]){
            a[i] -= 1 << j;
            W.push_back(w[i] * (1 << j));
            V.push_back(v[i] * (1 << j));
 
            ++j;
        }
        W.push_back(w[i] * a[i]);
        V.push_back(v[i] * a[i]);
    }
 
    // for(int i = 1; i < W.size(); ++i){
    //     cerr << W[i] << ' ' << V[i] << '\n';
    // }
    cout << knapsack(S, W, V) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> S;
    for(int i = 1; i <= n; ++i){
        cin >> w[i] >> v[i] >> a[i];
    }
 
    solve();
    return 0;
}