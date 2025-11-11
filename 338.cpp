#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 5000, MAXH = 5000;
int n, d, c[MAXN + 5], h[MAXN + 5];

int dp[MAXN + 5][MAXH + 5];
int minDp[2][MAXN + 5];

int getL(int i, int j){
    return dp[i][j] + c[i] * j;
}

int getR(int i, int j){
    return dp[i][j] - c[i] * j;
}

int pow2(int x){ return x * x; } 

void trau(){
    memset(dp, 0x3f, sizeof dp);
    memset(minDp, 0x3f, sizeof minDp);

    memset(dp[0], 0, sizeof dp[0]);    
    for(int i = 1; i <= n; ++i){
        for(int j = h[i]; j <= MAXH; ++j){
            for(int jj = max(0LL, j - d); jj <= min(MAXH, j + d); ++jj){
                
            // for(int jj = max(0LL, j - d); jj <= j; ++jj){
            // for(int jj = j; jj <= min(MAXH, j + d); ++jj){

                int newMin = dp[i - 1][jj] + c[i - 1] * abs(jj - j) + pow2(j - h[i]);
                dp[i][j] = min(dp[i][j], newMin);
            }
        }
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 0; j <= 10; ++j){
            cerr << dp[i][j] << ' ';
        }
        cerr << '\n';
    }

    int ans = *min_element(dp[n], dp[n] + MAXH + 1);
    cout << ans << '\n';
}

void solve(){
    memset(dp, 0x3f, sizeof dp);
    memset(dp[0], 0, sizeof dp[0]);
    for(int i = 1; i <= n; ++i){
        deque<int> dq;

        for(int j = 0; j <= MAXH; ++j){
            if(!dq.empty() && dq.back() < j - d) dq.pop_back();
            while(!dq.empty() && getR(i - 1, dq.front()) >= getR(i - 1, j)) dq.pop_front();
            dq.push_front(j);

            if(j >= h[i]){
                int newMin = getR(i - 1, dq.back()) + c[i - 1] * j + pow2(j - h[i]);
                dp[i][j] = min(dp[i][j], newMin);
            }
        }

        dq.clear();
        
        for(int j = MAXH; j >= h[i]; --j){
            if(!dq.empty() && dq.back() > j + d) dq.pop_back();
            while(!dq.empty() && getL(i - 1, dq.front()) >= getL(i - 1, j)) dq.pop_front();
            dq.push_front(j);
            
            int newMin = getL(i - 1, dq.back()) - c[i - 1] * j + pow2(j - h[i]);
            dp[i][j] = min(dp[i][j], newMin);
        }
    }

    // for(int i = 1; i <= n; ++i){
    //     for(int j = 0; j <= 10; ++j){
    //         cerr << dp[i][j] << ' ';
    //     }
    //     cerr << '\n';
    // }

    int ans = *min_element(dp[n], dp[n] + MAXH + 1);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> d;
    for(int i = 1; i < n; ++i){
        cin >> c[i];
    }
    for(int i = 1; i <= n; ++i){
        cin >> h[i];
    }

    solve();
    // trau();
    
    return 0;
}