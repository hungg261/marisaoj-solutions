#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5, MAXS = 2e3;
const int BASE = 29, MOD = 1e9 + 21;
int hashes[MAXN + 5], powhash[MAXN + 5];
string S;
int n, sz;
 
void compute(){
    hashes[0] = 0;
    powhash[0] = 1;
 
    for(int i = 1; i <= sz; ++i){
        hashes[i] = (hashes[i - 1] * BASE + (S[i] - 'a' + 1)) % MOD;
        powhash[i] = powhash[i - 1] * BASE % MOD;
    }
}
 
int computeHash(const string& s){
    int hash = 0;
    for(const char& c: s){
        hash = (hash * BASE + (c - 'a' + 1)) % MOD;
    }
 
    return hash;
}
 
int getHash(int l, int r){
    return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}
 
int dp[MAXS + 5];
set<int> store;
 
void solve(){
    for(int j = 1; j <= sz; ++j){
        for(int i = 1; i <= j; ++i){
            if(store.count(getHash(i, j))){
                dp[j] = max(dp[j], dp[i - 1] + (j - i + 1));
            }
        }
    }
 
    int ans = *max_element(dp, dp + sz + 1);
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> S;
    sz = S.size();
    S = '#' + S;
 
    compute();
 
    for(int i = 1; i <= n; ++i){
        string cur;
        cin >> cur;
 
        store.insert(computeHash(cur));
    }
 
    solve();
 
    return 0;
}