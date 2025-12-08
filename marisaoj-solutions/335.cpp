#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 1e5;
int arr[MAXN + 5], n, L[MAXN + 5], R[MAXN + 5];
 
void compute(){
    vector<int> sta;
    for(int i = 1; i <= n; ++i){
        while(!sta.empty() && arr[sta.back()] >= arr[i]) sta.pop_back();        
        L[i] = sta.empty() ? 0 : sta.back();
         
        sta.push_back(i);
    }
    
    sta.clear();
    for(int i = n; i >= 1; --i){
        while(!sta.empty() && arr[sta.back()] >= arr[i]) sta.pop_back();        
        R[i] = sta.empty() ? n + 1 : sta.back();
         
        sta.push_back(i);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
 
    compute();
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        ans = max(ans, arr[i] * (R[i] - L[i] - 1));
    }
 
    cout << ans << '\n';
 
    return 0;
}