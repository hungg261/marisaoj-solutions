#include<bits/stdc++.h>
using namespace std;
 
const int REPETITIONS = 105;
const int MAXN = 1e5;
int v[MAXN + 5], w[MAXN + 5];
int n, k;
 
bool check(double mid){
    vector<double> store;
    for(int i = 1; i <= n; ++i){
        store.push_back(w[i] * mid - v[i]);
    }
    sort(begin(store), end(store));
 
    double res = 0;
    for(int i = 0; i < k; ++i){
        res += store[i];
    }
 
    return res <= 0;
}
 
double tknp(){
    double l = 0, r = 1e14, res = -1;
    for(int rep = 1; rep <= REPETITIONS; ++rep){
        double mid = (l + r) / 2;
        if(check(mid)){
            res = mid;
            l = mid;
        }
        else r = mid;
    }
 
    return res;
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> v[i] >> w[i];
    }
 
    double res = tknp();
    cout << fixed << setprecision(6) << res << '\n';
 
    return 0;
}