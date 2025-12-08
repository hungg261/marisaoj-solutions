#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5, MAXS = 2e3;
const int BASE = 29, MOD = 1e9 + 21;
int hashes[MAXN + 5], powhash[MAXN + 5];
string S;
int n, k;
 
void compute(){
    hashes[0] = 0;
    powhash[0] = 1;
 
    for(int i = 1; i <= n; ++i){
        hashes[i] = (hashes[i - 1] * BASE + (S[i] - 'a' + 1)) % MOD;
        powhash[i] = powhash[i - 1] * BASE % MOD;
    }
}
 
int getHash(int l, int r){
    return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}
 
bool check(int mid){
    unordered_map<int, int> store;
    for(int i = 1; i + mid - 1 <= n; ++i){
        int curHash = getHash(i, i + mid - 1);
        ++store[curHash];
 
        if(store[curHash] >= k){
            return true;
        }
    }
 
    return false;
}
 
void solve(){
    int lo = 1, hi = n, res = 0;
    while(lo <= hi){
        int mid = (lo + hi) >> 1;
        if(check(mid)){
            res = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
 
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S >> k;
    n = S.size();
    S = '#' + S;
 
    compute();
    
    solve();
 
    return 0;
}