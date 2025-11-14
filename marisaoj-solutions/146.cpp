#include<bits/stdc++.h>
#define int long long
using namespace std;

bool is_prime(int n){
    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0) return false;
    }
    return n > 1;
}

const int MOD = 1e9 + 7;
const int MAXN = 100, MAXK = 1000;
int dp[MAXN + 5][MAXK + 5];
int n, k;

vector<pair<int, int>> sum_primes;
void compute(){
    for(int i = 0; i <= k; ++i){
        for(int j = 0; j <= k; ++j){
            if(is_prime(i + j)){
                sum_primes.push_back({i, j});
            }
        }
    }
}

void solve(){
    fill(dp[1], dp[1] + k + 1, 1);
    for(int i = 2; i <= n; ++i){
        for(const pair<int, int>& p: sum_primes){
            (dp[i][p.first] += dp[i - 1][p.second]) %= MOD;
        }
    }

    // for(int i = 0; i <= n; ++i){
    //     for(int j = 0; j <= k; ++j){
    //         cerr << dp[i][j] << ' ';
    //     }
    //     cerr << '\n';
    // }

    int ans = 0;
    for(int j = 0; j <= k; ++j){
        ans = (ans + dp[n][j]) % MOD;
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    compute();
    solve();

    return 0;
}