#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN=1e5,MAXK=100;
int a[MAXN+5],n,k,last[MAXK+5],best[MAXK+5];

void solve(){
    fill(best,best+k+1,-1e18);
    for(int i=1;i<=n;++i){
        for(int j=k;j>=1;--j){
            if(i<j){
                last[j]=-1e18;
                continue;
            }
            
            last[j]=max(last[j]+a[i],best[j-1]+a[i]);
            if(j==1){
                last[j]=max(last[j],a[i]);
            }
            
            best[j]=max(best[j],last[j]);
        }
        
        // for(int k=1;k<=::k;++k){
        //     cout<<best[k]<<' ';
        // }cout<<'\n';
        // for(int k=1;k<=::k;++k){
        //     cerr<<last[k]<<' ';
        // }cerr<<'\n';
    }
    
    cout<<best[k]<<'\n';
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    k=3;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    
    solve();
    return 0;
}