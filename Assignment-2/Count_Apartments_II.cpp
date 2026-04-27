#include<bits/stdc++.h>
using namespace std;

char mat[1005][1005];
bool vis[1005][1005];

vector<pair<int,int>> d = {{0,1},{0,-1},{-1,0},{1,0}};

int n, m;

bool valid(int i, int j){
    if(i < 0 || i >= n || j < 0 || j >= m){
        return false;
    }
    return true;
}

int bfs(int si, int sj){
    queue<pair<int,int>> q;
    q.push({si, sj});
    vis[si][sj] = true;

    int cnt = 1;

    while(!q.empty()){
        auto par = q.front();
        q.pop();

        int a = par.first, b = par.second;

        for(int i = 0; i < 4; i++){
            int ci = a + d[i].first;
            int cj = b + d[i].second;

            if(valid(ci, cj) && mat[ci][cj] == '.' && !vis[ci][cj]){
                q.push({ci, cj});
                vis[ci][cj] = true;
                cnt++;
            }
        }
    }

    return cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> mat[i][j];
        }
    }

    memset(vis, false, sizeof(vis));
    vector<int> apart;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == '.' && !vis[i][j]){
                int size = bfs(i, j);
                apart.push_back(size);
            }
        }
    }

    if(apart.empty()){
        cout << 0 << endl;
        return 0;
    }
    sort(apart.begin(), apart.end());

    for(int x : apart){
        cout << x << " ";
    }
    cout << endl;

    return 0;
}