/******************************************************************************
Link: https://marisaoj.com/problem/384
Code: 384
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-11-16.32.14
*******************************************************************************/
#include<bits/stdc++.h>
#define cerr if(false)cerr
using namespace std;

#define int long long
int MOD = 998244353;
set<int> mark;
struct Matrix{
    static const int SIZE = 3;

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

    Matrix operator * (const Matrix& other) const{
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

    Matrix powMat(int b, const vector<Matrix>& Tp) const{
        assert(n == m);

        Matrix res = Matrix::Identity(n);
        for (int i = 0; i <= 60; ++i) {
            if (b >> i & 1) res = Tp[i] * res;
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

const int MAXM = 1e4;
int n, m;
int M[MAXM + 5];
vector<Matrix> Tp(61);

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("384.INP","r",stdin);
    //freopen("384.OUT","w",stdout);
    int temp;
    cin >> n >> temp;
    bool m2 = false;
    for(int i = 1; i <= temp; ++i){
        cin >> M[++m];
        m2 |= M[m] == 2;
        if(M[m] <= 2 || M[m] > n) --m;
    }
    M[++m] = 2;
    M[++m] = n + 1;

    Matrix T(3, 3, {
        {0, 1, 1},
        {1, 0, 0},
        {0, 1, 0}
            });
    Tp[0] = T;
    for (int i = 1; i <= 60; ++i) Tp[i] = Tp[i-1] * Tp[i-1];

    Matrix base(3, 1, {
        {m2 ? 0 : 1},
        {0},
        {1}
            });

    if(n <= 2){
        cout << base[2 - n][0] << '\n';
        return 0;
    }

    sort(M + 1, M + m + 1);
    for(int i = 2; i <= m; ++i){
        base = T.powMat((M[i] - M[i - 1] - 1), Tp) * base;

        base[2][0] = base[1][0];
        base[1][0] = base[0][0];
        base[0][0] = 0;
    }

    cout << base[1][0] << '\n';

    return 0;
}
