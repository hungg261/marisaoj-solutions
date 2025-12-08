#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
const int MAXN = 1e6;
int n, p[MAXN * 2 + 5], d[MAXN * 2 + 5], pre[MAXN * 2 + 5], suf[MAXN * 2 + 5];
 
bool res[MAXN + 5] = {};
void solve(){
    deque<int> dq;
    for(int i = 1; i <= n * 2; ++i){
        if(!dq.empty() && i - dq.back() + 1 > n) dq.pop_back();
        while(!dq.empty() && pre[dq.front()] >= pre[i]) dq.pop_front();
        dq.push_front(i);
 
        if(i >= n + 1){
            res[i - n] |= pre[dq.back()] - pre[i - n] >= 0;
        }
    }
 
    dq.clear();
 
    for(int i = n * 2; i >= 1; --i){
        if(!dq.empty() && dq.back() - i + 1 > n) dq.pop_back();
        while(!dq.empty() && suf[dq.front()] >= suf[i]) dq.pop_front();
        dq.push_front(i);
 
        if(i <= n){
            res[i] |= suf[dq.back()] - suf[i + n] >= 0;
        }
    }
 
    for(int i = 1; i <= n; ++i){
        cout << (res[i] ? "TAK" : "NIE") << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> p[i] >> d[i];
        p[i + n] = p[i]; d[i + n] = d[i];
    }
    
    for(int i = 1; i <= n * 2; ++i){
        pre[i] = pre[i - 1] + (p[i - 1] - d[i - 1]);
    }
    for(int i = n * 2; i >= 1; --i){
        suf[i] = suf[i + 1] + (p[i + 1] - d[i]);
    }
 
    solve();
 
    return 0;
}