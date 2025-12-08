/******************************************************************************
Link: https://marisaoj.com/problem/329
Code: 329
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-12-13.15.02
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 40, MAXHALF = MAXN + 1 >> 1;
int storeA[1 << MAXHALF], lenA,
    storeB[1 << MAXHALF], lenB;
 
int n, k;
int a[MAXN];
 
void __generate(int arr[], int m, int store[], int& len){
    for(int mask = 0; mask < (1 << m); ++mask){
        int sum = 0;
        for(int i = 0; i < m; ++i){
            if(mask & (1 << i)){
                sum += arr[i];
            }
        }
 
        store[len++] = sum;
    }
}
 
void solve(){
    int mid = n / 2;
    int spaceL[mid], spaceR[n - mid];
    for(int i = 0; i < mid; ++i) spaceL[i] = a[i];
    for(int i = mid; i < n; ++i) spaceR[i - mid] = a[i];
 
    __generate(spaceL, mid, storeA, lenA);
    __generate(spaceR, n - mid, storeB, lenB);
 
    sort(storeB, storeB + lenB);
    for(int i = 0; i < lenA; ++i){
        if(binary_search(storeB, storeB + lenB, k - storeA[i])){
            cout << "YES\n";
            return;
        }
    }
 
    cout << "NO\n";
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("329.INP","r",stdin);
    //freopen("329.OUT","w",stdout);
    cin >> n >> k;
    for(int i = 0; i < n; ++i) cin >> a[i];
 
    solve();
 
    return 0;
}