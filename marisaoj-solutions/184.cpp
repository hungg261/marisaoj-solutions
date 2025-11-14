#include<bits/stdc++.h>
#define cerr if(false)cerr
using namespace std;

const short MAXN = 5000;
bool mark[MAXN + 5][MAXN + 5];
short n, r;

const short dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

struct State{
    short x, y, mov;
};

void solve(){
    cin >> n >> r;
    queue<State> que;
    for(short i = 0; i < n; ++i){
        string cur;
        cin >> cur;

        for(int j = 0; j < n; ++j){
            if(cur[j] == 'X'){
                que.push({i, j, 0});
            }
        }
    }
    
    while(!que.empty()){
        State cur = que.front();
        que.pop();

        if(mark[cur.x][cur.y]) continue;
        mark[cur.x][cur.y] = true;

        for(int d = 0; d < 4; ++d){
            short nx = cur.x + dx[d], ny = cur.y + dy[d];
            if(0 <= nx && nx < n && 0 <= ny && ny < n && cur.mov + 1 <= r && !mark[nx][ny]){
                que.push({nx, ny, cur.mov + 1});
            }
        }
    }

    int ans = 0;
    for(short i = 0; i < n; ++i){
        for(short j = 0; j < n; ++j){
            cerr << mark[i][j] << ' ';
            ans += mark[i][j];
        }
        cerr << '\n';
    }

    cout << n * n - ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();

    return 0;
}