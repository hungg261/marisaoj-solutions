#include<bits/stdc++.h>
using namespace std;
 
string temp;
void solve(){
    int n = temp.size();
 
    vector<int> pi(n);
    pi[0] = 0;
    for(int i = 1; i < n; ++i){
        int j = pi[i - 1];
        while(j > 0 && temp[i] != temp[j]){
            j = pi[j - 1];
        }
 
        if(temp[i] == temp[j]) ++j;
        pi[i] = j;
    }
 
    cout << temp.substr(0, n - pi[n - 1]) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> temp;
    solve();
 
    return 0;
}