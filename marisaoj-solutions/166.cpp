#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5;
const int BASE = 31, MOD = 1e9 + 9;
int hashes[MAXN + 5], revhashes[MAXN + 5], powhash[MAXN + 5];
string S;
int n;
 
void compute(){
    powhash[0] = 1;
    for(int i = 1; i <= n; ++i){
        hashes[i] = (hashes[i - 1] * BASE + (S[i] - 'a' + 1)) % MOD;
        revhashes[i] = (revhashes[i - 1] * BASE + (S[n - i + 1] - 'a' + 1)) % MOD;
        powhash[i] = powhash[i - 1] * BASE % MOD;
    }
}
 
int getHash(int l, int r){
    return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}
 
int getRevhash(int l, int r){
    return ((revhashes[r] - revhashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}
 
bool is_palindrome(int l, int r){
    return getHash(l, r) == getRevhash(n - r + 1, n - l + 1);
}
 
int tknp_chan(int i){
    int l = 0, r = min(n - i, i - 2), res = -1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(is_palindrome(i - 1 - mid, i + mid)){
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
 
    return res * 2 + 2;
}
 
int tknp_le(int i){
    int l = 0, r = min(n - i, i - 1), res = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(is_palindrome(i - mid, i + mid)){
            res = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
 
    return res * 2 + 1;
}
 
void solve(){
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        ans += tknp_chan(i) / 2;
        ans += (tknp_le(i) + 1) / 2;
    }
 
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S;
    n = S.size();
    S = '#' + S;
 
    compute();
    solve();
 
    return 0;
}