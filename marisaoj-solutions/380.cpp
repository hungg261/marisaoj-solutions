#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e5, MAXVAL = 1e5;
struct FenwickTree{
    int n;
    vector<int> BIT;
 
    FenwickTree() = default;
    FenwickTree(int sz): n(sz){ BIT.resize(sz + 1, 0); }
 
    void update(int idx, int val){
        for(int i = idx; i <= n; i += i & -i){
            BIT[i] += val;
        }
    }
 
    int get(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i){
            res += BIT[i];
        }
        return res;
    }
 
    int get(int L, int R){ return get(R) - get(L - 1); }
};
 
struct Segment{
    int L, R, idx;
 
    bool operator == (const Segment& other){
        return this->L == other.L && this->R == other.R;
    }
 
    bool operator < (const Segment& other){
        return this->L < other.L || (this->L == other.L && this->R > other.R);
    }
} segments[MAXN + 5];
int n;
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> segments[i].L >> segments[i].R;
        segments[i].idx = i;
    }
    sort(segments + 1, segments + n + 1);
 
    FenwickTree fwt(MAXVAL + 5);
    vector<int> result(n + 1);
    for(int i = n; i >= 1; --i){
        int j = i;
        while(j > 1 && segments[j] == segments[j - 1]){
            --j;
        }
 
        int res = fwt.get(segments[i].L, segments[i].R);
 
        for(int cur = i; cur >= j; --cur){
            result[segments[cur].idx] = res + (i - j);
            fwt.update(segments[cur].R, 1);
        }
        
        i = j;
    }
 
    for(int i = 1; i <= n; ++i){
        cout << result[i] << '\n';
    }
 
    return 0;
}