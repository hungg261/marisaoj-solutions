#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
int dp[18][2][11][11][2][2];
int num[20], len;
 
int Try(int idx, int smaller, int pre1, int pre2, bool valid, bool full0){
    if(idx < 0) return full0 || valid;
 
    int& memo = dp[idx][smaller][pre1][pre2][valid][full0];
    if(memo != -1) return memo;
 
    int lim = smaller ? 9 : num[idx];
    memo = 0;
    for(int digit = 0; digit <= lim; ++digit){
        memo += Try(idx - 1, smaller || (digit < lim), digit, full0 ? 10 : pre1,
            full0 || (valid && digit != pre1 && digit != pre2),
            full0 && digit == 0);
    }
 
    return memo;
}
 
int calc(int x){
    if(x < 0) return 0;
 
    len = 0;
    while(x > 0){
        num[len++] = x % 10;
        x /= 10;
    }
 
    memset(dp, -1, sizeof dp);
    return Try(len - 1, 0, 10, 10, 1, 1);
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int l, r;
    cin >> l >> r;
 
    cout << calc(r) - calc(l - 1) << '\n';
 
    return 0;
}