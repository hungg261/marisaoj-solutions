#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5, MAXC = 15;
int n, dp[MAXC + 5];
 
void solve(){}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
 
    vector<int> mask_cnt(1 << MAXC, 0);
    for(int i = 0; i < n; ++i){
        string cur;
        cin >> cur;
 
        int mask = 0;
        for(int c: cur){
            mask |= 1 << (c - 'a');
        }
 
        mask_cnt[mask]++;
    }
 
    vector<int> dp = mask_cnt;
    for(int i = 0; i < MAXC; ++i){
        for(int mask = 0; mask < (1 << MAXC); ++mask){
            if(mask >> i & 1){
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
 
    int xau = 0;
    for(int mask = 0; mask < (1 << MAXC); ++mask){
        xau += mask_cnt[mask] * dp[((1 << MAXC) - 1) ^ mask];
    }
 
    int total = n * (n - 1) / 2,
        tot = total - xau / 2;
    
    cout << tot << '\n';
 
    return 0;
}