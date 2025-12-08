/******************************************************************************
Link: https://marisaoj.com/problem/17
Code: 17
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-20-21.04.54
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("17.INP","r",stdin);
    //freopen("17.OUT","w",stdout);
    long long n;
    cin >> n;
 
    long long sum = 0;
    for(int i = 1; 1LL * i * i <= n; ++i){
        if(n % i == 0){
            sum += i;
            if(i != n / i) sum += n / i;
        }
    }
 
    cout << sum << '\n';
 
    return 0;
}