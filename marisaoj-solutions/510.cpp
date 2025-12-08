#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 18;
string s;
int n;
 
int to_int(string s){
    int res = 0;
    for(char c: s){
        res = res * 10 + (c - '0');
    }
    return res;
}
 
int dp[MAXN + 5];
void solve(){
    dp[0] = 1;
    dp[1] = s[1] - '0' + 1;
    for(int i = 2; i <= n; ++i){
        int cnt1 = s[i] - '0' + 1;
        int cnt2 = 0;
 
        int num = to_int(s.substr(i - 1, 2));
        if(num > 9) for(int d1 = 0; d1 <= 9; ++d1){
            for(int d2 = 0; d2 <= 9; ++d2){
                if(d1 + d2 == num) ++cnt2;
            }
        }
 
        dp[i] = dp[i - 1] * cnt1 + dp[i - 2] * cnt2;
    }
 
    // for(int i = 1; i <= n; ++i){
    //     cout << dp[i] << ' ';
    // }
 
    cout << dp[n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> s;
    n = s.size();
    s = '#' + s;
 
    solve();
 
    return 0;
}