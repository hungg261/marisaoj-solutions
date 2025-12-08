#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const long long MAX = 1e12;
 
vector<int> primes;
void pfactor(long long n){
    if(n % 2 == 0) primes.push_back(2);
    while(n % 2 == 0){
        n /= 2;
    }
 
    for(int i = 3; 1LL * i * i <= n; i += 2){
        if(n % i == 0) primes.push_back(i);
        while(n % i == 0){
            n /= i;
        }
    }
 
    if(n > 1) primes.push_back(n); 
    sort(begin(primes), end(primes));
}
 
struct Term{
    int prod, sign;
 
    bool operator < (const Term& other){
        return prod < other.prod;
    }
};
vector<Term> terms;
 
void precompute(){
    int sz = primes.size();
    for(int mask = 1; mask < (1 << sz); ++mask){
        long long tich = 1;
        int cnt = 0;
        for(int i = 0; i < sz; ++i){
            if(mask >> i & 1){
                if(tich > MAX / primes[i]) goto passed;
 
                tich *= primes[i];
                ++cnt;
            }
        }
 
        terms.push_back({tich, cnt & 1 ? 1 : -1});
 
        passed: NULL;
    }
 
    sort(begin(terms), end(terms));
}
 
long long Solver(long long l, long long r){
    long long ans = 0;
    for(const Term& T: terms){
        if(T.prod > r) break;
 
        ans += (r / T.prod - (l - 1) / T.prod) * T.sign;
    }
 
    return (r - l + 1) - ans;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int t; long long n;
    cin >> n >> t;
 
    pfactor(n);
    precompute();
 
    while(t--){
        long long l, r;
        cin >> l >> r;
 
        cout << Solver(l, r) << '\n';
    }
 
    return 0;
}