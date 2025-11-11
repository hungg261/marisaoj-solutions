#include<bits/stdc++.h>
#define int long long
using namespace std;

void solve(){
    int n;
    cin >> n;

    int res = 0;
    while(n--){
        int x; cin >> x;
        res ^= x;
    }

    cout << (res == 0 ? "REIMU" : "MARISA") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}