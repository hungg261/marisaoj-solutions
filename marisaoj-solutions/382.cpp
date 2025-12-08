#include<bits/stdc++.h>
#define stack vector
using namespace std;

string S;
int n, k;

void output(stack<int> sta){
    for(int digit: sta){
        cout << S[digit];
    }
}

stack<int> solve(){
    stack<int> sta;
    for(int i = 0; i < n; ++i){
        while(k > 0 && !sta.empty() && S[sta.back()] < S[i]){
            sta.pop_back();
            --k;
        }
        sta.push_back(i);
    }

    while(k--) sta.pop_back();

    return sta;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S >> k;
    n = S.size();

    output(solve());

    return 0;
}