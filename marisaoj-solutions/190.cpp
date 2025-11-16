/******************************************************************************
Link: https://marisaoj.com/problem/190
Code: 190
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-14-09.31.55
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
#define cerr if(false)cerr
using namespace std;

const int MAXN = 1e5, MAXK = 100;
int Euler[MAXN + 5], Time;
pair<int, int> T[MAXN + 5];

int n, k, A[MAXN + 5];
vector<int> adj[MAXN + 5];

void dfs(int u, int prev){
    Euler[++Time] = u;
    T[u].first = Time;

    for(int v: adj[u]){
        if(v == prev) continue;
        dfs(v, u);
    }

    T[u].second = Time;
}

vector<int> L[MAXN + 5];
int maxDp[MAXN + 5][MAXK + 5], dp[MAXN + 5][MAXK + 5];
int pre[MAXN + 5];
void solve(){
    sort(T + 1, T + n + 1, [](auto& x, auto& y){
        return x.second < y.second;
            });

    for(int i = 1; i <= n; ++i){
        cerr << i << ": " << T[i].first << ' ' << T[i].second << '\n';
        L[T[i].second].push_back(T[i].first);
        pre[i] = pre[i - 1] + A[Euler[i]];
    }

    memset(dp, -0x3f, sizeof dp);
    memset(maxDp, -0x3f, sizeof maxDp);

    dp[0][0] = 0;
    maxDp[0][0] = 0;
    for(int i = 1; i <= n; ++i){
        dp[i][0] = pre[i];
        for(int l: L[i]){
            for(int j = 1; j <= k; ++j){
                if(i == 5){
                    cerr << "print: " << j << ' ' << l << ": " << maxDp[l - 1][j - 1] << ' ' << maxDp[l - 1][j] + pre[i] - pre[l - 1] << '\n';
                }
                dp[i][j] = max(dp[i][j], maxDp[l - 1][j - 1]);
            }
        }
        for(int j = 0; j <= k; ++j){
            maxDp[i][j] = max(maxDp[i - 1][j], dp[i][j]);
        }
    }

    for(int i = 1; i <= n; ++i) cerr << A[Euler[i]] << ' '; cerr << '\n';
    for(int j = 0; j <= k; ++j){
        cerr << "best " << j << ": " << dp[n][j] << '\n';
    }

    cerr << '\n';
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= k; ++j){
            cerr << dp[i][j] << ' ';
        }
        cerr << '\n';
    }

    int res = *max_element(dp[n], dp[n] + k + 1);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("190.INP","r",stdin);
    //freopen("190.OUT","w",stdout);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> A[i];
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    solve();

    return 0;
}
