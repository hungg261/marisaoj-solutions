#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int BASE = 29, MOD = 1e9 + 9 ;
const int MAXN = 2e5;
int powbase[MAXN + 5];
 
void compute(){
    powbase[0] = 1;
    for(int i = 1; i <= MAXN; ++i){
        powbase[i] = powbase[i - 1] * BASE % MOD;
    }
}
 
struct FenwickTree{
    vector<int> BIT;
    int n;
 
    FenwickTree() = default;
    FenwickTree(int sz): n(sz){
        BIT.resize(sz + 1, 0);
    }
 
    void update(int idx, int val){
        for(int i = idx; i <= n; i += i & -i)
            BIT[i] = (BIT[i] + val) % MOD;
    }
 
    int get(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i)
            res = (res + BIT[i]) % MOD;
 
        return res;
    }
    int get(int L, int R){ return ((get(R) - get(L - 1)) % MOD + MOD) % MOD; }
    int at(int idx){ return get(idx, idx); }
 
    void modify(int idx, int val){
        update(idx, val - get(idx, idx));
    }
};
 
int f(char c){ return c - 'a' + 1; }
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;
    string s;
    cin >> s >> m;
    n = s.size();
    s = '#' + s;
 
    compute();
    FenwickTree fen1(n), fen2(n);
    for(int i = 1; i <= n; ++i){
        fen1.update(i, f(s[i]) * powbase[n - i]);
        fen2.update(i, f(s[n - i + 1]) * powbase[n - i]);
    }
 
    while(m--){ 
        if(1 == 0){
            int k; char x;
            cin >> k >> x;
 
            fen1.modify(k, f(x) * powbase[n - k]);
            fen2.modify(n - k + 1, f(x) * powbase[k - 1]);
        }
        else{
            int a, b;
            cin >> a >> b;
 
            int h1 = fen1.get(a, b), h2 = fen2.get(n - b + 1, n - a + 1);
            if(n - a > n - (n - b + 1)){
                h2 = h2 * powbase[(n - b + 1) - a] % MOD;
            }
            else{
                h1 = h1 * powbase[a - (n - b + 1)] % MOD;
            }
 
            cout << (h1 == h2 ? "YES\n" : "NO\n");
        }
    }
 
    return 0;
}