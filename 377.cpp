/******************************************************************************
Link: MIXTURES
Code: MIXTURES
Time (YYYY-MM-DD-hh.mm.ss): 2024-09-02-19.06.22
*******************************************************************************/
#include<bits/stdc++.h>
#define endl '\n'
#define st first
#define nd second
#define pb push_back
#define it(A) begin(A),end(A)
#define inp(A,n) for(int i=0;i<n;++i)cin>>A[i]
using namespace std;

void print(int dp[505][505],int n){
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout<<dp[i][j]<<'\t';
        }
        cout<<'\n';
    }
}

void solve(){
    int n,A[505],dp[505][505],color[505][505];
    cin>>n;
    inp(A,n);

    for(int i=0;i<n;++i)for(int j=0;j<n;++j)dp[i][j]=1e9;
    for(int i=0;i<n;++i){
        dp[i][i]=0;
        color[i][i]=A[i];
    }

    for(int len=2;len<=n;++len){
        for(int i=0;i<=n-len;++i){
            int j=i+len-1;
            for(int k=i;k<j;++k){
                int q=dp[i][k]+dp[k+1][j]+color[i][k]*color[k+1][j];
                if(q<dp[i][j]){
                    dp[i][j]=q;
                    color[i][j]=(color[i][k]+color[k+1][j])%100;
                }
            }
//            cout<<i<<' '<<j<<'\n';
//            print(dp,n);
//            cout<<'\n';
        }
    }

    cout<<dp[0][n-1]<<'\n';
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // freopen("MIXTURES.INP","r",stdin);
    // freopen("MIXTURES.OUT","w",stdout);

    int t = 1;
    while(t--)solve();
    return 0;
}