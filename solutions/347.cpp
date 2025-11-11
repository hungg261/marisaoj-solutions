#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5, MAXK = 200;
int n, m, k;
int arr[MAXN + 5];

long long dp[MAXN + 5][MAXK + 5];
int maxIdx[MAXN + 5];

void solve(){
    vector<deque<long long>> dq(k + 1);
    long long ans = 0;

    dp[1][1] = arr[1];
    for(int i = 1; i <= n; ++i){
        if(i > 1){
            for(int j = 1; j <= k; ++j){
                dp[i][j] = dp[dq[j - 1].back()][j - 1] + 1LL * j * arr[i];
            }

            ans = max(ans, dp[i][k]);
        }

        for(int j = 0; j < k; ++j){
            if(!dq[j].empty() && i - dq[j].back() + 1 > m) dq[j].pop_back();
            while(!dq[j].empty() && dp[dq[j].front()][j] <= dp[i][j]) dq[j].pop_front();
            dq[j].push_front(i);
        }
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    solve();

    return 0;
}