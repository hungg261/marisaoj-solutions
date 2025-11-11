#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4;
int n, t, arr[MAXN + 5];

int dp[MAXN + 5];
bool check(int mid){
    deque<int> dq;
    dp[0] = 0; dq.push_front(0);
    for(int i = 1; i <= n; ++i){
        dp[i] = dp[dq.back()] + arr[i];

        if(!dq.empty() && dq.back() < i - mid) dq.pop_back();
        while(!dq.empty() && dp[dq.front()] >= dp[i]) dq.pop_front();
        dq.push_front(i);
    }

    return dp[dq.back()] <= t;
}

void solve(){
    int l = 0, r = MAXN + 1, res = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)){
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }

    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> t;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    solve();
    
    return 0;
}