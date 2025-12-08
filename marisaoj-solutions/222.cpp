#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN=20;
int n,L,R;
int primes[MAXN+5];

int solve(int N){
    sort(primes+1,primes+n+1);
    n=unique(primes+1,primes+n+1)-primes-1;
    int ans=0;
    for(int mask=1;mask<(1<<n);++mask){
        int tich=1,cnt=0;
        for(int i=1;i<=n;++i){
            if(mask&(1<<(i-1))){
                if(tich>N/primes[i]){
                    goto passed;
                }
                
                tich*=primes[i];
                ++cnt;
            }
        }
        
        ans+=(N/tich)*(cnt%2==1?1:-1);
        
        passed:NULL;
    }
    
    return ans;
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>L>>R;
    for(int i=1;i<=n;++i){
        cin>>primes[i];
    }
    
    cout<<solve(R)-solve(L-1)<<'\n';
    return 0;
}