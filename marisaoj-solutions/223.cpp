#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 20;
int n, L, R;
int P[MAXN + 5];

int solve(int ubound){
    int res = 0;
    for(int mask = 1; mask < (1 << n); ++mask){
        int mul = 0,
            tich = 1;
        for(int i = 0; i < n; ++i){
            if(mask >> i & 1){
                if(tich > ubound / P[i]){
                    goto passed;
                }

                tich *= P[i];
                ++mul;
            }
        }

        if(mul & 1) res += mul * (ubound / tich);
        else res -= mul * (ubound / tich);
        passed: NULL;
    }

    return res;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> L >> R;
    for(int i = 0; i < n; ++i){
        cin >> P[i];
    }

    // cerr << solve(L - 1) << ' ' << solve(R) << '\n';

    int ans = solve(R) - solve(L - 1);
    cout << ans << '\n';

    return 0;
}