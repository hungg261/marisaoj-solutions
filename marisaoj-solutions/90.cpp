#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAX=1e5;
int n,k,a[MAX+1],P[MAX+1],Pmin[MAX+1];

bool check(int mid){
    for(int i=1;i<=n;++i){
        P[i]=P[i-1]+a[i]-mid;
        Pmin[i]=min(Pmin[i-1],P[i]);
        
        if(i>=k&&P[i]-Pmin[i-k]>=0){
            return true;
        }
    }
    return false;
}

void solve(int l,int h){
    int res=-1;
    while(l<=h){
        int mid=(l+h)/2;
        if(check(mid)){
            res=mid;
            l=mid+1;
        }
        else h=mid-1;
    }
    cout<<fixed<<setprecision(3)<<res/10000.0<<'\n';
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    int max_avg=-2e18,min_avg=2e18;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        a[i]*=10000;
        P[i]=P[i-1]+a[i];

        min_avg=min(min_avg,a[i]);
        max_avg=max(max_avg,a[i]);
    }
    
    solve(min_avg,max_avg);
    return 0;
}