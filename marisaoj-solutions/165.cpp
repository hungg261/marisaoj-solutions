#include<bits/stdc++.h>
using namespace std;
 
string S, T;
void solve(){
    string temp = T + "#" + S;
    int target = T.size();
    int n = (int)temp.size();
 
    int ans = 0;
    vector<int> pi(n);
    pi[0] = 0;
    for(int i = 1; i < n; ++i){
        int j = pi[i - 1];
        while(j > 0 && temp[i] != temp[j]){
            j = pi[j - 1];
        }
 
        if(temp[i] == temp[j]) ++j;
        pi[i] = j;
 
        if(j == target) ++ans;
    }
 
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S >> T;
    solve();
 
    return 0;
}