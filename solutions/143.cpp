#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1000;
int dp[MAXN + 5], A[MAXN + 5], n;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> A[i];

        dp[i] = 1;
        for(int j = 1; j < i; ++j){
            if(A[j] < A[i]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    cout << *max_element(dp + 1, dp + n + 1) << '\n';

    return 0;
}