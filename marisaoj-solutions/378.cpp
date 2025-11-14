#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 1e9 + 7;
const int MAXN = 10, MAXM = 200;
int n, m;

bool checkAdj1(int mask){
    for(int i = 0; i < n; ++i){
        if((mask & (1 << i)) &&
            ((i < n - 1 && (mask & (1 << (i + 1)))) ||
            (i > 0 && (mask & (1 << (i - 1)))))){

                return false;
        }
    }

    return true;
}

int dp[MAXM + 5][(1 << MAXN) + 5];

void solve(){
    vector<int> masks;
    for(int mask = 0; mask < (1 << n); ++mask){
        if(checkAdj1(mask)){
            dp[0][mask] = 1;
            masks.push_back(mask);
        }

    }

    int sz = masks.size();

    for(int j = 1; j < m; ++j){
        for(int mask: masks){
            for(int prevMask: masks){
                if((mask & prevMask) == 0){
                    dp[j][mask] += dp[j - 1][prevMask];
                    dp[j][mask] %= MOD;
                }
            }
        }
    }
    

    int ans = 0;
    for(int mask = 0; mask < (1 << n); ++mask){
        ans += dp[m - 1][mask]; ans %= MOD;
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;

    solve();

    return 0;
}