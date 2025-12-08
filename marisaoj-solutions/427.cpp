#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN=1e6,MAXVAL=1e6;
int n,a[MAXN+5],gcd_cnt[MAXVAL+5],freq[MAXVAL+5];
 
void solve(){
    for(int i=1;i<=n;++i){
        ++freq[a[i]];
    }
    
    for(int i=1;i<=n;++i){
        for(int j=i;j<=n;j+=i){
            gcd_cnt[i]+=freq[j];
        }
        gcd_cnt[i]=gcd_cnt[i]*(gcd_cnt[i]-1)/2;
    }
    
    for(int i=n;i>=1;--i){
        for(int j=i*2;j<=n;j+=i){
            gcd_cnt[i]-=gcd_cnt[j];
        }
    }
    
    for(int i=1;i<=n;++i){
        cout<<gcd_cnt[i]<<' ';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    
    solve();
    return 0;
}