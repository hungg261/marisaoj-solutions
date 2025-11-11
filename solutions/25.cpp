#include<bits/stdc++.h>
#define int long long
using namespace std;

int mulmod(int a, int b, int m){
    int res = 0;
    a %= m;

    while(b > 0){
        if(b & 1) res = (res + a) % m;
        a = (a << 1) % m;
        b >>= 1;
    }

    return res;
}

int powmod(int a, int b, int m){
    int res = 1;
    a %= m;

    while(b > 0){
        if(b & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        b >>= 1;
    }

    return res;
}

bool check(int a, int n){
    return powmod(a, n - 1, n) == 1;
}

bool miller_rabin(int n){
    if(n < 2) return false;

    vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
    for(int a: bases){
        if(a >= n) break;

        if(!check(a, n)) return false;
    }
    return true;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;

    cout << (miller_rabin(n) ? "YES\n" : "NO\n");

    return 0;
}