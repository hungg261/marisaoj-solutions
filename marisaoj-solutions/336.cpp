#include<bits/stdc++.h>
using namespace std;
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, d;
    cin >> n >> d;
    vector<int> arr(n);
    for(int& ele: arr) cin >> ele;
 
    deque<int> dq;
    for(int i = 0; i < n; ++i){
        if(!dq.empty() && i - dq.back() + 1 > d) dq.pop_back();
        while(!dq.empty() && arr[dq.front()] >= arr[i]) dq.pop_front();
        dq.push_front(i);
 
        if(i + 1 >= d){
            cout << arr[dq.back()] << ' ';
        }
    }
 
    return 0;
}