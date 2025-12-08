#include<bits/stdc++.h>
#define stack vector
using namespace std;
 
#define int long long
 
const int MAXN = 2e5, MAXLG = __lg(MAXN) + 1;
int n, q;
int arr[MAXN + 5], pre[MAXN + 5];
int R[MAXN + 5];
 
pair<int, int> nxt[MAXN + 5][MAXLG + 5];
void compute(){
    stack<int> sta;
    for(int i = n; i >= 1; --i){
        while(!sta.empty() && arr[sta.back()] <= arr[i]) sta.pop_back();
 
        R[i] = sta.empty() ? n + 1 : sta.back();
        sta.push_back(i);
    }
 
    for(int i = 1; i <= n; ++i){
        nxt[i][0] = {R[i], arr[i] * (R[i] - i) - (pre[R[i] - 1] - pre[i - 1])};
    }
    nxt[n + 1][0] = {n + 1, 0};
 
    for(int j = 1; j <= MAXLG; ++j){
        for(int i = 1; i <= n + 1; ++i){
            int nxt_pos, nxt_cost; tie(nxt_pos, nxt_cost) = nxt[i][j - 1];
            nxt[i][j] = {nxt[nxt_pos][j - 1].first,
                        nxt_cost + nxt[nxt_pos][j - 1].second};
        }
    }
}
 
pair<int, int> lift(int pos, int steps){
    pair<int, int> res = {pos, 0};
    for(int bit = MAXLG; bit >= 0; --bit){
        if(steps >> bit & 1){
            res = nxt[pos][bit];
        }
    }
 
    return res;
}
 
void query(int l, int r){
    int ans = 0;
    for(int bit = MAXLG; bit >= 0; --bit){
        int nxt_pos, cost; tie(nxt_pos, cost) = nxt[l][bit];
 
        if(nxt_pos <= r){
            l = nxt_pos;
            ans += cost;
        }
    }
 
    ans += arr[l] * (r - l + 1) - (pre[r] - pre[l - 1]);
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }
 
    compute();
 
    while(q--){
        int l, r;
        cin >> l >> r;
 
        query(l, r);
    }
 
    return 0;
}