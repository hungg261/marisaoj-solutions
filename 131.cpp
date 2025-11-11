#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5;
int parent[MAXN+5],sz[MAXN+5];
long long sum[MAXN+5];

void make_set(int v){
    parent[v]=v;
    sz[v]=1;
    sum[v]=v;
}

int find_set(int v){
    if(parent[v]==v){
        return v;
    }
    
    int new_parent=find_set(parent[v]);
    parent[v]=new_parent;
    
    return new_parent;
}

void union_sets(int u,int v){
    int a=find_set(u),
        b=find_set(v);
    
    if(a!=b){
        if(sz[a]<sz[b]){
            swap(a,b);
        }
        
        parent[b]=a;
        sz[a]+=sz[b];
        sum[a]+=sum[b];
    }
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,q;
    cin>>n>>q;
    
    for(int v=1;v<=n;++v){
        make_set(v);
    }
    
    while(q--){
        int type;
        cin>>type;
        
        if(type==1){
            int u,v;
            cin>>u>>v;
            union_sets(u,v);
        }
        else{
            int u;
            cin>>u;
            cout<<sum[find_set(u)]<<'\n';
        }
    }
    return 0;
}