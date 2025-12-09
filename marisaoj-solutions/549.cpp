/******************************************************************************
Link: https://marisaoj.com/problem/549
Code: 549
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-09-20.47.27
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Point{
    int x, y;

    bool operator < (const Point& other){
        return x < other.x || (x == other.x && y < other.y);
    }
};

struct cmp{
    bool operator()(const Point& A, const Point& B){
        return A.y < B.y || (A.y == B.y && A.x < B.x);
    }
};

int sqdist(const Point& A, const Point& B){
    return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

double dist(const Point& A, const Point& B){ return sqdist(A, B); }

const int MAXN = 3e5, INF = 1e9;
Point arr[MAXN + 5];
set<Point, cmp> T;
int n;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("A.INP","r",stdin);
    //freopen("A.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i].x >> arr[i].y;
    }
    sort(arr + 1, arr + n + 1);

    int sq_d = sqdist(arr[1], arr[2]);

    for(int i = 1; i <= n; ++i){
        int x = arr[i].x, y = arr[i].y;

        int d = (int)sqrt(sq_d) + 1;
        while(!T.empty()){
            Point p = *T.begin();
            if(x - p.x > d) T.erase(p);
            else break;
        }

        auto it_low = T.lower_bound({0, y - d}),
            it_high = T.upper_bound({0, y + d});

        for(auto it = it_low; it != it_high; ++it){
            int new_d = sqdist(arr[i], *it);
            if(new_d < sq_d){
                sq_d = new_d;
            }
        }

        T.insert(arr[i]);
    }

    cout << sq_d << '\n';

    return 0;
}
