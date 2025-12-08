#include<bits/stdc++.h>
#define cerr if(false)cerr
using namespace std;
 
const int MAXN = 1e5, MAXVAL = 1e5, MAXLG = __lg(MAXVAL) + 1;
int n, q, L;
pair<int, int> segments[MAXN + 5];
int maxLR[MAXN + 5];
int farthest[MAXVAL + 5][MAXLG + 5];
 
int upper_bound(int value){
    int l = 1, r = n, res = n + 1;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(segments[mid].first > value){
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
 
    return res;
}
 
void compute(){
    sort(segments + 1, segments + n + 1);
    maxLR[0] = -1;
    for(int i = 1; i <= n; ++i){
        maxLR[i] = max(maxLR[i - 1], segments[i].second);
    }
 
    int maxReach = -1;
    for(int val = 1; val <= L; ++val){
        int idx = upper_bound(val) - 1;
        maxReach = max(maxReach, maxLR[idx]); 
 
        farthest[val][0] = maxReach + 1;
        cerr << farthest[val][0] << ' ';
    }
    farthest[L + 1][0] = L + 1;
 
    for(int j = 1; j <= MAXLG; ++j){
        for(int val = 1; val <= L + 1; ++val){
            int nxt = farthest[val][j - 1];
            farthest[val][j] = farthest[nxt][j - 1];
        }
    }
}
 
void query(int l, int r){
    int ans = 0;
    for(int bit = MAXLG; bit >= 0; --bit){
        int nxt = farthest[l][bit];
        cerr << nxt << '\n';
        if(nxt <= r){
            l = nxt;
            ans += 1 << bit;
        }
    }
 
    l = farthest[l][0];
    cerr << l << ' ' << r << '\n';
    if(l <= r){
        cout << "-1\n";
        return;
    }
 
    ans += 1;
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q >> L;
    for(int i = 1; i <= n; ++i){
        int x, y;
        cin >> x >> y;
 
        segments[i] = {x, y};
    }
 
    compute();
 
    while(q--){
        int l, r;
        cin >> l >> r;
 
        query(l, r);
    }
 
    return 0;
}