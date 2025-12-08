// TEST AI: Gemini
 
#include<bits/stdc++.h>
using namespace std;
 
const int MAXCNT = 200;
int cnt;
string store[MAXCNT + 5];
 
const int MAXN = 26; // Represents 'a' through 'z'
int n = MAXN;       // Total number of characters to sort
vector<int> adj[MAXN + 5]; // Adjacency list for graph (1-indexed for characters)
int indeg[MAXN + 5];       // In-degree for each character (1-indexed)
 
void compute(){
    // Iterate through pairs of adjacent words to infer character dependencies
    for(int i = 1; i <= cnt; ++i){
        for(int j = i + 1; j <= cnt; ++j){
            int sz_i = store[i].size(), sz_j = store[j].size();
            bool diff_found = false; // Flag to check if a difference was found
            for(int k = 0; k < min(sz_i, sz_j); ++k){
                if(store[i][k] != store[j][k]){
                    // If characters differ, an ordering constraint is found
                    int cA = store[i][k] - 'a' + 1; // Convert char to 1-indexed int
                    int cB = store[j][k] - 'a' + 1; // Convert char to 1-indexed int
 
                    adj[cA].push_back(cB); // Add a directed edge cA -> cB
                    diff_found = true;
                    break; // Move to the next pair of words
                }
            }
 
            // If no difference was found up to the length of the shorter word,
            // and the first word is longer than the second, it's an invalid ordering
            // (e.g., "apple" followed by "app" is lexicographically incorrect).
            if(!diff_found && sz_i > sz_j){
                cout << "-1\n";
                exit(0); // Terminate program with an error
            }
        }
    }
 
    // Process the graph to remove duplicate edges and compute initial in-degrees
    for(int i = 1; i <= n; ++i){ // Iterate through all possible characters (1 to 26)
        sort(begin(adj[i]), end(adj[i])); // Sort adjacency list to group duplicates
        adj[i].erase(unique(begin(adj[i]), end(adj[i])), end(adj[i])); // Remove duplicates
 
        // Calculate in-degrees for all nodes
        for(int v: adj[i]){
            ++indeg[v];
        }
    }
}
 
// Kahn's algorithm for topological sort
void kahn(){
    string topo;      // String to store the topological order
    queue<int> que;   // Queue for nodes with in-degree 0
 
    // Initialize queue with all nodes having an in-degree of 0
    for(int u = 1; u <= n; ++u){
        if(indeg[u] == 0) que.push(u);
    }
 
    // Process nodes from the queue until it's empty
    while(!que.empty()){
        int u = que.front(); // Get the current node
        que.pop();           // Remove it from the queue immediately
 
        topo += (char)(u - 1 + 'a'); // Add the character to the result string
 
        // For each neighbor 'v' of the current node 'u'
        for(int v: adj[u]){
            --indeg[v]; // Decrement the in-degree of the neighbor
            // If the neighbor's in-degree becomes 0, add it to the queue
            if(indeg[v] == 0) que.push(v);
        }
    }
 
    // Check if a topological sort of all 'n' characters was possible
    // If not, it means there was a cycle in the dependency graph.
    if(topo.size() != n){
        cout << "-1\n";
        return;
    }
 
    cout << topo << '\n'; // Output the resulting topological order
}
 
signed main(){
    // Optimize C++ standard streams for faster input/output
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> cnt; // Read the number of words
    // Read all the words
    for(int i = 1; i <= cnt; ++i){
        cin >> store[i];
    }
 
    compute(); // Build the dependency graph and calculate initial in-degrees
    kahn();    // Perform topological sort
 
    return 0; // Indicate successful execution
}