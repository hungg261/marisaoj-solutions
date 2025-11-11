#include<bits/stdc++.h>
#define int long long
using namespace std;
 
namespace hashing{
    void createHash(const string& s, int n, int BASE, int MOD, int hashes[], int powhash[]){
        hashes[0] = 0; powhash[0] = 1;
        for(int i = 1; i <= n; ++i){
            hashes[i] = (hashes[i - 1] * BASE + (s[i] - 'a' + 1)) % MOD;
            powhash[i] = (powhash[i - 1] * BASE) % MOD;
        }
    }
 
    int getHash(int l, int r, const string& s, int MOD, int hashes[], int powhash[]){
        return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
    }
};
 
const int MAXN = 1e6;
const int BASE = 31, MOD = 1e9 + 9;
int hashes[MAXN * 2 + 5], powhash[MAXN * 2 + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s;
    cin >> s;
 
    int n = s.size();
    s = '#' + s + s;
 
    hashing::createHash(s, n * 2, BASE, MOD, hashes, powhash);
 
    int ans = 1;
    for(int i = 2; i <= n; ++i){
        int lo = 1, hi = n, res = 0;
        while(lo <= hi){
            int mid = (lo + hi) >> 1;
            if(hashing::getHash(i, i + mid - 1, s, MOD, hashes, powhash) == hashing::getHash(ans, ans + mid - 1, s, MOD, hashes, powhash)){
                res = mid;
                lo = mid + 1;
            }
            else hi = mid - 1;
        }
 
        if(res < n && s[i + res] < s[ans + res]) ans = i;
    }
 
    cout << s.substr(ans, n) << '\n';
 
    return 0;
}