#include<bits/stdc++.h>
using namespace std;

#define int long long

int dp[20][2][120];
int num[20], len;

int Try(int idx, int smaller, int sum){
    if(idx < 0) return sum;

    int& memo = dp[idx][smaller][sum];
    if(memo != -1) return memo;

    int lim = smaller ? 9 : num[idx];
    memo = 0;
    for(int digit = 0; digit <= lim; ++digit){
        memo += Try(idx - 1, smaller || (digit < lim), sum + digit);
    }

    return memo;
}

int calc(int x){
    len = 0;
    while(x > 0){
        num[len++] = x % 10;
        x /= 10;
    }

    memset(dp, -1, sizeof dp);
    return Try(len - 1, 0, 0);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int l, r;
    cin >> l >> r;

    cout << calc(r) - calc(l - 1) << '\n';

    return 0;
}