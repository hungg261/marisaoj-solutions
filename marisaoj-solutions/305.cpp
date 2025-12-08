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
    int n;
    cin >> n;
    
    Matrix trans(2, 2, {
        {1, 1},
        {1, 0}
    }), base(2, 1, {
        {1},
        {0}
    });
    
    Matrix res = (trans ^ (n - 1)) * base;
    cout << (n <= 1 ? n : res[0][0]) << '\n';
    
    return 0;
}