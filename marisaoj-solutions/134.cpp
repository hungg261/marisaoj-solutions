#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN=1e5,MAXM=1e5;
int n,m;
struct edge{
    int u,v,w;
} edges[MAXM+5];

bool cmp(edge&a,edge&b){
    return a.w<b.w;
}

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
        if(sz[a]<sz[b])swap(a,b);
        
        parent[b]=a;
        sz[a]+=sz[b];
    }
}

void solve(){
    sort(edges+1,edges+m+1,cmp);
    int ans=0;
    for(int i=1;i<=m;++i){
        if(find_set(edges[i].u)!=find_set(edges[i].v)){
            union_sets(edges[i].u,edges[i].v);
            ans+=edges[i].w;
        }
    }
    cout<<ans<<'\n';
}

signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int v=1;v<=n;++v)make_set(v);
    for(int i=1;i<=m;++i){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }
    
    solve();
    return 0;
}