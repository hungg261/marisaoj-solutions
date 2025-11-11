#include<bits/stdc++.h>
using namespace std;

#define int long long

int dp[12][2][120][120];
int num[20], len, k;

int Try(int idx, int smaller, int digit_sum, int mod){
    if(idx < 0) return mod == 0 && digit_sum % k == 0;

    int& memo = dp[idx][smaller][digit_sum][mod];
    if(memo != -1) return memo;

    int lim = smaller ? 9 : num[idx];
    memo = 0;
    for(int digit = 0; digit <= lim; ++digit){
        memo += Try(idx - 1, smaller || (digit < lim), digit_sum + digit, (mod * 10 + digit) % k);
    }

    return memo;
}

int calc(int x){
    len = 0;
    while(x > 0){
        num[len++] = x % 10;
        x /= 10;
    }

    if(len * 9 < k) return 1;

    memset(dp, -1, sizeof dp);
    return Try(len - 1, 0, 0, 0);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int t;
    cin >> t;

    while(t--){
        int l, r;
        cin >> l >> r >> k;

        cout << calc(r) - calc(l - 1) << '\n';
    }

    return 0;
}