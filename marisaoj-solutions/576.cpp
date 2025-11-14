#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e8;
const int INF = 1e18;
map<int, int> dp;

int Try(int n){
    if(dp.count(n)) return dp[n];
    int& memo = dp[n];

    if(n == 0) return memo = 0;
    int nxt = Try(n / 2) + Try(n / 3) + Try(n / 4);

    return memo = max(nxt, n);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t = 1;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        cout << Try(n) << '\n';
    }

    return 0;
}