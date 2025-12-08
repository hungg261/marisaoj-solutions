#include<bits/stdc++.h>
using namespace std;
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int& ele: arr) cin >> ele;
 
    vector<int> sta;
    for(int i = 0; i < n; ++i){
        while(!sta.empty() && arr[sta.back()] >= arr[i]) sta.pop_back();
        int cur = sta.empty() ? 0 : sta.back() + 1;
 
        cout << cur << ' ';
 
        sta.push_back(i);
    }
 
    return 0;
}