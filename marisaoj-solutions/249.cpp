#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e5+5;
int n, m, timer = 0, scc_cnt = 0;
vector<int> adj[MAXN];
int disc[MAXN], low[MAXN], stk[MAXN], top = 0;
bool inStack[MAXN];
int scc_id[MAXN], scc_size[MAXN];

void tarjan(int u){
    disc[u] = low[u] = ++timer;
    stk[++top] = u; inStack[u] = 1;
    for(int v: adj[u]){
        if(!disc[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]){
            low[u] = min(low[u], disc[v]);
        }
    }
    if(low[u] == disc[u]){
        ++scc_cnt;
        while(true){
            int v = stk[top--];
            inStack[v] = 0;
            scc_id[v] = scc_cnt;
            ++scc_size[scc_cnt];
            if(v == u) break;
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    for(int i = 1; i <= n; i++)
        if(!disc[i]) tarjan(i);

    vector<int> outdeg(scc_cnt+1, 0);
    for(int u = 1; u <= n; u++){
        for(int v: adj[u]){
            if(scc_id[u] != scc_id[v]){
                outdeg[scc_id[u]]++;
            }
        }
    }

    int sink = -1, cnt = 0;
    for(int i = 1; i <= scc_cnt; i++){
        if(outdeg[i] == 0){
            cnt++;
            sink = i;
        }
    }

    if(cnt == 1) cout << scc_size[sink] << "\n";
    else cout << 0 << "\n";
}