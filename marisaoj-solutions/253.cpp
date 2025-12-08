#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
bool is_prime(int x){
    for(int i = 2; i * i <= x; ++i){
        if(x % i == 0) return false;
    }
    return x > 1;
}
 
int dp[14][2][140];
int num[20], len, k;
 
int Try(int idx, int smaller, int digit_sum){
    if(idx < 0) return is_prime(digit_sum);
 
    int& memo = dp[idx][smaller][digit_sum];
    if(memo != -1) return memo;
 
    int lim = smaller ? 9 : num[idx];
    memo = 0;
    for(int digit = 0; digit <= lim; ++digit){
        memo += Try(idx - 1, smaller || (digit < lim), digit_sum + digit);
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
 
int solve(int k){
    int l = 2, r = 1e13, res = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(calc(mid) >= k){
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
 
    return res;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int k;
    cin >> k;
 
    cout << solve(k) << '\n';
 
    return 0;
}