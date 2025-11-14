#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int BIT[MAXN + 5], n, arr[MAXN + 5];

void update(int idx, int val){
    for(int i = idx; i <= n; i += i & -i) BIT[i] += val;
}

int get(int idx){
    int res = 0;
    for(int i = idx; i > 0; i -= i & -i) res += BIT[i];
    return res;
}
int get(int l, int r){ return get(r) - get(l - 1); }

int temp[MAXN + 5];
void compress(){
    for(int i = 1; i <= n; ++i) temp[i] = arr[i];
    sort(temp + 1, temp + n + 1);

    for(int i = 1; i <= n; ++i){
        arr[i] = lower_bound(temp + 1, temp + n + 1, arr[i]) - temp;
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }
    compress();

    long long ans = 0;
    for(int i = n; i >= 1; --i){
        ans += get(arr[i] - 1);
        update(arr[i], 1);
    }

    cout << ans << '\n';

    return 0;
}