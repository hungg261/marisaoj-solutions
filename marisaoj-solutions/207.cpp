#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN=2e5;
int a[MAXN+5],n,t,prefix[MAXN+5];
vector<int>temp;

void compress(){
    sort(begin(temp),end(temp));
    // temp.resize(unique(begin(temp),end(temp))-begin(temp)); // loai bo trung lap
}

int get_compressed_value(int value){
    return lower_bound(begin(temp),end(temp),value)-begin(temp)+1;
}

int BIT[MAXN*2+5];
void update(int idx,int val){
    while(idx<=n*2){
        BIT[idx]+=val;
        idx += idx & (-idx);
    }
}

int get(int idx){
    int res=0;
    while(idx>0){
        res+=BIT[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void solve(){
    int ans=0;
    for(int i=0;i<=n;++i){
        int compressed_prefix = get_compressed_value(prefix[i]);
        int compressed_value = get_compressed_value(prefix[i]-t);
        
        ans+=get(compressed_value);
        update(compressed_prefix,1);
    }
    
    cout<<ans<<'\n';
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    t=0;
    
    temp.push_back(0);
    temp.push_back(-t);
    for(int i=1;i<=n;++i){
        cin>>a[i];
        prefix[i]=prefix[i-1]+a[i];
        
        temp.push_back(prefix[i]);
        temp.push_back(prefix[i]-t);
    }
    
    compress();
    solve();
    return 0;
}