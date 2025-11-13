/******************************************************************************
Link: https://marisaoj.com/problem/559
Code: 559
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-09.12.24
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Pair{
    int sum, idx1, idx2;

    static int lower_bound(const vector<Pair>& arr, int l, int r, int target){
        int res = r + 1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(arr[mid] >= target){
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        return res;
    }

    static int upper_bound(const vector<Pair>& arr, int l, int r, int target){
        int res = r + 1;
        while(l <= r){
            int mid = (l + r) / 2;
            if(arr[mid] > target){
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        return res;
    }

    static pair<int, int> equal_range(const vector<Pair>& arr, int l, int r, int target){
        return {lower_bound(arr, l, r, target), upper_bound(arr, l, r, target) - 1};
    }

    bool operator < (const Pair& other) const{
        if(this->sum == other.sum) return this->idx2 < other.idx2;
        return this->sum < other.sum;
    }

    operator int() const{
        return this->sum;
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, x;
    cin >> n >> x;

    vector<int> arr(n + 1);
    for(int i = 1; i <= n; ++i) cin >> arr[i];

    vector<Pair> sum;
    for(int i = 1; i <= n; ++i){
        for(int j = i + 1; j <= n; ++j){
            sum.push_back({arr[i] + arr[j], i, j});
        }
    }
    sort(begin(sum), end(sum));

    for(int i = 1; i <= n; ++i){
        for(int j = i + 1; j <= n; ++j){
            int target = x - arr[i] - arr[j];

            int l, r;
            tie(l, r) = Pair::equal_range(sum, 0, (int)sum.size() - 1, target);

            while(l <= r){
                int mid = (l + r) / 2;
                if(sum[mid].idx2 < i){
                    cout << "YES\n";
                    return 0;
                }
                else r = mid - 1;
            }
        }
    }

    cout << "NO\n";

    return 0;
}
