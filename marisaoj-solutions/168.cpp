#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5;
const int BASE = 29, MOD = 1e9 + 21;
int hashes[MAXN + 5], powhash[MAXN + 5];
string S;
int n;

void compute(){
    hashes[0] = 0;
    powhash[0] = 1;

    for(int i = 1; i <= n; ++i){
        hashes[i] = (hashes[i - 1] * BASE + (S[i] - '0' + 1)) % MOD;
        powhash[i] = powhash[i - 1] * BASE % MOD;
    }
}

int getHash(int l, int r){
    return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1]) % MOD + MOD) % MOD;
}

char solve(int a, int b, int l){
    if(getHash(a, a + l) == getHash(b, b + l)) return '=';

    int lo = 0, hi = l - 1, res = -1;
    while(lo <= hi){
        int mid = (lo + hi) >> 1;
        if(getHash(a, a + mid) == getHash(b, b + mid)){
            res = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }

    return S[a + res + 1] > S[b + res + 1] ? '>' : '<';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S;
    n = S.size();
    S = '#' + S;

    compute();

    int q;
    cin >> q;

    while(q--){
        int a, b, l;
        cin >> a >> b >> l;

        cout << solve(a, b, l) << '\n';
    }

    return 0;
}