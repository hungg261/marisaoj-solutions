#include<bits/stdc++.h>
using namespace std;

const int MAXN=1e5;
int parent[MAXN+5],sz[MAXN+5];

void make_set(int v){
    parent[v]=v;
    sz[v]=1;
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
    }
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,q;
    cin>>n>>q;
    
    while(n--){
        make_set(n);
    }
    
    while(q--){
        int type,u,v;
        cin>>type>>u>>v;
        
        if(type==1){
            union_sets(u,v);
        }
        else{
            cout<<(find_set(u)==find_set(v)?"YES\n":"NO\n");
        }
    }
    return 0;
}