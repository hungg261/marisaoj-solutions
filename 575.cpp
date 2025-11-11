#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Segment{
    int L, R;

    operator int() const{
        return this->R;
    }
};

const int MAXN = 1e5;
Segment segs[MAXN + 5];
int dp[MAXN + 5], n;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> segs[i].L >> segs[i].R;
    }
    sort(segs + 1, segs + n + 1);

    dp[0] = 0;
    for(int i = 1; i <= n; ++i){
        int idx = lower_bound(segs + 1, segs + n + 1, segs[i].L) - segs - 1;
        dp[i] = max(dp[i - 1], dp[idx] + (segs[i].R - segs[i].L + 1));
    }
    
    cout << dp[n] << '\n';

    return 0;
}