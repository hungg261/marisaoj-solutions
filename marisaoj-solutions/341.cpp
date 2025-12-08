#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MOD = 1e9 + 7;
const int MAXN = 1e5;
int n, A[MAXN + 5];
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> A[i];
    }
 
    vector<int> dp = {A[1]};
    for(int i = 2; i <= n; ++i){
        if(A[i] > dp.back()) dp.push_back(A[i]);
        else *lower_bound(begin(dp), end(dp), A[i]) = A[i];
    }
 
    cout << dp.size() << '\n';
 
    return 0;
}