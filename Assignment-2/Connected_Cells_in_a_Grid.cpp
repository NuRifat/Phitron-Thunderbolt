int connectedCell(vector<vector<int>> matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<bool>> vis(n, vector<bool>(m, false));

    vector<pair<int,int>> d = {
        {-1,-1},{-1,0},{-1,1},
        {0,-1},{0,1},
        {1,-1},{1,0},{1,1}
    };

    function<int(int,int)> dfs = [&](int x, int y) {
        vis[x][y] = true;
        int cnt = 1;

        for(auto move : d){
            int nx = x + move.first;
            int ny = y + move.second;

            if(nx >= 0 && nx < n && ny >= 0 && ny < m){
                if(matrix[nx][ny] == 1 && !vis[nx][ny]){
                    cnt += dfs(nx, ny);
                }
            }
        }
        return cnt;
    };

    int maxRegion = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(matrix[i][j] == 1 && !vis[i][j]){
                int size = dfs(i, j);
                maxRegion = max(maxRegion, size);
            }
        }
    }

    return maxRegion;
}