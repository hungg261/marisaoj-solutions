/******************************************************************************
Link: https://marisaoj.com/problem/258
Code: 258
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-05-00.28.33
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;
 
struct AhoCorasick{
    struct Node{
        int nxt[26];
        int link;
        int cnt;
        vector<int> ends;
 
        Node(){
            memset(nxt, -1, sizeof nxt);
            cnt = 0;
            link = -1;
        }
    };
 
    vector<Node> T;
    vector<vector<int>> adj;
    AhoCorasick(){ T.emplace_back(); }
 
    void add(const string& text, int idx){
        int p = 0;
        for(int c: text){
            c -= 'a';
 
            if(T[p].nxt[c] == -1){
                T[p].nxt[c] = T.size();
                T.emplace_back();
            }
            p = T[p].nxt[c];
        }
 
        T[p].ends.push_back(idx);
    }
 
    void build(){
        queue<int> que;
        T[0].link = 0;
        for(int c = 0; c < 26; ++c){
            int &v = T[0].nxt[c];
            if(v != -1){
                T[v].link = 0;
                que.push(v);
            }
            else{
                v = 0;
            }
        }
 
        while(!que.empty()){
            int u = que.front();
            que.pop();
 
            for(int c = 0; c < 26; ++c){
                int v = T[u].nxt[c];
                if(v != -1){
                    T[v].link = T[T[u].link].nxt[c];
                    que.push(v);
                }
                else{
                    T[u].nxt[c] = T[T[u].link].nxt[c];
                }
            }
        }
 
        adj.resize(T.size());
        for(int i = 1; i < (int)T.size(); ++i){
            adj[T[i].link].push_back(i);
        }
    }
 
    int dfs(int u, vector<int>& res){
        int occ = T[u].cnt;
        for(int v: adj[u]){
            occ += dfs(v, res);
        }
 
        for(int idx: T[u].ends){
            res[idx] += occ;
        }
 
        return occ;
    }
 
    void Search(const string& Text, int q){
        int p = 0;
        for(int c: Text){
            c -= 'a';
 
            p = T[p].nxt[c];
            if(p != -1){
                T[p].cnt++;
            }
        }
 
        vector<int> res(q);
        dfs(0, res);
 
        for(int r: res){
            cout << r << '\n';
        }
    }
};
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("258.INP","r",stdin);
    //freopen("258.OUT","w",stdout);
    string S;
    cin >> S;
 
    int q;
    cin >> q;
 
    AhoCorasick aho;
    for(int i = 0; i < q; ++i){
        string cur;
        cin >> cur;
 
        aho.add(cur, i);
    }
 
    aho.build();
    aho.Search(S, q);
 
    return 0;
}