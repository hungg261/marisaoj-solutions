#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5, MAXM = 100;
int A[MAXN + 5], n, m;

bool dp[MAXN + 5];
void solve(){
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(i >= A[j]){
                dp[i] |= !dp[i - A[j]];
            }
        }
    }

    cout << (dp[n] ? "Marisa" : "Reimu") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        cin >> A[i];
    }

    solve();

    return 0;
}