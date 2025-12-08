/******************************************************************************
Link: https://marisaoj.com/problem/256
Code: 256
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-23-20.29.10
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
#define int long long
int dp[60][2][2];
int num[60];
int x[60], s[60];
 
int Try(int idx, int smaller, int bound){
    if(idx < 0){
        return 1;
    }
 
    int& memo = dp[idx][smaller][bound];
    if(memo != -1) return memo;
 
    int lim = smaller ? 1 : num[idx];
 
    memo = 0;
    for(int digit = 0; digit <= lim; ++digit){
//        int nbound = bound;
//
//        if(!bound){
//            if((x[idx] ^ digit) < s[idx]) nbound = 1;
//            else if((x[idx] ^ digit) > s[idx]) continue;
//        }
 
        if(bound || (x[idx] ^ digit) <= s[idx]) memo += Try(idx - 1, smaller || (digit < lim), bound || ((x[idx] ^ digit) < s[idx]));
    }
    return memo;
}
 
int solve(int N){
    for(int i = 0; i < 60; ++i){
        num[i] = N % 2;
        N /= 2;
    }
 
    memset(dp, -1, sizeof dp);
    return Try(59, 0, 0);
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("256.INP","r",stdin);
    //freopen("256.OUT","w",stdout);
    int X, L, R, S;
    cin >> X >> L >> R >> S;
 
    for(int i = 0; i < 60; ++i){
        x[i] = X % 2;
        X /= 2;
    }
 
    for(int i = 0; i < 60; ++i){
        s[i] = S % 2;
        S /= 2;
    }
 
    cout << solve(R) - solve(L - 1) << '\n';
 
    return 0;
}
/*
79 65 94 89
*/