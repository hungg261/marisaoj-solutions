#include<bits/stdc++.h>
using namespace std;
 
struct Trie{
    struct Node{
        int nxt[26];
        int words;
 
        Node(){
            memset(nxt, -1, sizeof nxt);
            words = 0;
        }
    };
 
    vector<Node> T;
    int root;
 
    Trie(){
        T.emplace_back();
        root = 0;
    }
 
    void add(const string& s){
        int p = root;
        for(int c: s){
            c -= 'a';
 
            if(T[p].nxt[c] == -1){
                T[p].nxt[c] = T.size();
                T.emplace_back();
            }
            p = T[p].nxt[c];
        }
 
        ++T[p].words;        
    }
 
    bool find(const string& s){
        int p = root;
        for(int c: s){
            c -= 'a';
 
            if(T[p].nxt[c] == -1){
                return false;
            }
            p = T[p].nxt[c];
        }
 
        return T[p].words > 0;
    }
 
    bool is_substr(const string& s){
        int p = root;
        for(int c: s){
            c -= 'a';
 
            if(T[p].words > 0) return true;
            if(T[p].nxt[c] == -1){
                return false;
            }
 
            p = T[p].nxt[c];
        }
 
        return T[p].words > 0;
    }
};
 
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
 
    vector<string> store;
    while(n--){
        string cur;
        cin >> cur;
 
        store.push_back(cur);
    }
    sort(begin(store), end(store), [](auto& x, auto& y){
        return x.size() < y.size();
    });
 
    Trie trie;
    for(string cur: store){
        if(trie.is_substr(cur)){
            cout << "YES\n";
            return 0;
        }
        trie.add(cur);
    }
 
    cout << "NO\n";
 
    return 0;
}