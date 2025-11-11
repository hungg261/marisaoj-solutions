#include<bits/stdc++.h>
using namespace std;

const int MAXCNT = 200;
int cnt;
string store[MAXCNT + 5];

const int MAXN = 26;
int n = MAXN, m;
vector<int> adj[MAXN + 5];
int indeg[MAXN + 5];

void compute(){
    for(int i = 1; i <= cnt; ++i){
        for(int j = i + 1; j <= cnt; ++j){
            int sz_i = store[i].size(), sz_j = store[j].size();
            for(int k = 0; k < min(sz_i, sz_j); ++k){
                if(store[i][k] != store[j][k]){
                    int cA = store[i][k] - 'a' + 1,
                        cB = store[j][k] - 'a' + 1;

                    adj[cA].push_back(cB);
                    goto passed;
                }
            }

            if(sz_i > sz_j){
                cout << "-1\n";
                exit(0);
            }

            passed: NULL;
        }
    }

    for(int i = 1; i <= n; ++i){
        sort(begin(adj[i]), end(adj[i]));
        adj[i].erase(unique(begin(adj[i]), end(adj[i])), end(adj[i]));

        for(int v: adj[i]){
            ++indeg[v];
        }
    }

    // for(int u = 1; u <= n; ++u){
    //     for(int v: adj[u]){
    //         cerr << u << ' ' << v << " | " << indeg[u] << ' ' << indeg[v] << '\n';
    //     }
    // }
}

void kahn(){
    string topo;
    queue<int> que;
    for(int u = 1; u <= n; ++u){
        if(indeg[u] == 0) que.push(u);
    }

    while(!que.empty()){
        int u = que.front();
        
        if(indeg[u] == 0){
            topo += u - 1 + 'a';
            for(int v: adj[u]){
                --indeg[v];
                if(indeg[v] == 0) que.push(v);
            }
            que.pop();
        }
    }

    if(topo.size() != n){
        cout << "-1\n";
        return;
    }

    cout << topo << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> cnt;
    for(int i = 1; i <= cnt; ++i){
        cin >> store[i];
    }

    compute();
    kahn();

    return 0;
}