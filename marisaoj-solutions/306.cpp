/******************************************************************************
Link: https://marisaoj.com/problem/306
Code: 306
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-11-11.23.03
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
int mod = 1e9 + 7;
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
                    res[i][j] += self[i][k] * other[k][j] % mod;
                    res[i][j] %= mod;
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
    //freopen("306.INP","r",stdin);
    //freopen("306.OUT","w",stdout);
    int n;
    cin >> n;
 
    if(n <= 3){
        cout << 1 << '\n';
        return 0;
    }
 
    Matrix T(5, 5, {
        {3, -2, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 2, -1, 1}
             });
    Matrix base(5, 1, {
        {1},
        {1},
        {5},
        {1},
        {15}
            });
 
    Matrix res = (T ^ (n - 3)) * base;
    int ans = res[0][0];
 
    cout << (ans % mod + mod) % mod << '\n';
 
    return 0;
}