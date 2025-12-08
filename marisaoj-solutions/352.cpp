/******************************************************************************
Link: https://marisaoj.com/problem/352
Code: 352
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-07-23.51.36
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n;
vector<int> adj[MAXN + 5];

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("352.INP","r",stdin);
    //freopen("352.OUT","w",stdout);
    cin >> n;
    if(n <= 2){
        cout << "1\n";
        return 0;
    }

    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int ans = 0;
    for(int i = 1; i <= n; ++i){
        if(adj[i].size() == 1) ++ans;
    }

    cout << ans << '\n';

    return 0;
}