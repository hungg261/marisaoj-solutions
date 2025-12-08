/******************************************************************************
Link: https://marisaoj.com/problem/385
Code: 385
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-11-12.02.27
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long
int MOD = 1e9 + 7;
struct Matrix{
    static const int SIZE = 100;

    int n, m;
    int self[SIZE][SIZE];

    Matrix() = default;
    Matrix(int _n, int _m, int val = 0): n(_n), m(_m){
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) self[i][j] = val;
    }
    Matrix(int _n, int _m, vector<vector<int>> mat){
        n = _n; m = _m;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                self[i][j] = mat[i][j];
            }
        }
    }

    static Matrix Identity(int n){
        Matrix res(n, n);
        for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) res[i][j] = i == j;
        return res;
    }

    Matrix operator * (const Matrix& other){
        assert(m == other.n);

        Matrix res(n, other.m);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < other.m; ++j){
                for(int k = 0; k < m; ++k){
                    res[i][j] += self[i][k] * other[k][j] % MOD;
                    res[i][j] %= MOD;
                }
            }
        }

        return res;
    }

    Matrix operator ^ (int b){
        assert(n == m);
        Matrix res = Identity(n), temp = *this;

        while(b > 0){
            if(b & 1) res = res * temp;
            temp = temp * temp;
            b >>= 1;
        }

        return res;
    }

    void output(){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                cerr << self[i][j] << ' ';
            }
            cerr << '\n';
        }
    }

    int* operator[] (int idx){ return self[idx]; }
    const int* operator[] (int idx) const{ return self[idx]; }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("385.INP","r",stdin);
    //freopen("385.OUT","w",stdout);

    Matrix f(26, 26);
    for(int i = 0; i < 26; ++i){
        for(int j = 0; j < 26; ++j){
            cin >> f[i][j];
        }
    }

    Matrix dp(1, 26);
    for(int i = 0; i < 26; ++i) dp[0][i] = 1;

    int q;
    cin >> q;

    while(q--){
        int n; char c;
        cin >> n >> c;

        Matrix res = dp * (f ^ (n - 1));

        cout << res[0][c - 'a'] << '\n';
    }

    return 0;
}