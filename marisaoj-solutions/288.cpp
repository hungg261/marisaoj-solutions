#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e5;
vector<pair<int, int>> queries;
 
vector<int> adj[MAXN + 5];
int indeg[MAXN + 5];
 
int n, m;
 
int Time = 0;
int pos[MAXN + 5];
void kahn(){
    queue<int> que;
    for(int i = 1; i <= n; ++i){
        if(indeg[i] == 0) que.push(i);
    }
 
    while(!que.empty()){
        int u = que.front();
 
        if(indeg[u] == 0){
            pos[u] = ++Time;
            for(int v: adj[u]){
                --indeg[v];
                if(indeg[v] == 0) que.push(v);
            }
            que.pop();
        }
    }
 
    if(Time != n){
        cout << "NO\n";
        exit(0);
    }
}
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b, type;
        cin >> type >> a >> b;
 
        if(type == 0){
            queries.emplace_back(a, b);
        }
        else{
            adj[a].push_back(b);
            indeg[b]++;
        }
    }
 
    kahn();
 
    for(pair<int, int> p: queries){
        int a, b; tie(a, b) = p;
        if(pos[a] > pos[b]) swap(a, b);
 
        adj[a].push_back(b);
    }
 
    cout << "YES\n";
    for(int u = 1; u <= n; ++u){
        for(int v: adj[u]){
            cout << u << ' ' << v << '\n';
        }
    }
 
    return 0;
}