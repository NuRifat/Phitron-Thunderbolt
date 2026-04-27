#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<pair<int,int>> d = {
    {-2, -1}, {-2, 1},{-1, -2}, {-1, 2},
    {1, -2},  {1, 2},{2, -1},  {2, 1}
};

bool valid(int i, int j)
{
    return (i >= 0 && i < n && j >= 0 && j < m);
}

int bfs(int si, int sj, int di, int dj)
{
    vector<vector<int>> dis(n, vector<int>(m, -1));
    queue<pair<int,int>> q;

    q.push({si, sj});
    dis[si][sj] = 0;

    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if(x == di && y == dj)
            return dis[x][y];

        for(auto move : d)
        {
            int nx = x + move.first;
            int ny = y + move.second;

            if(valid(nx, ny) && dis[nx][ny] == -1)
            {
                dis[nx][ny] = dis[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while(t--)
    {
        cin >> n >> m;

        int ki, kj, qi, qj;
        cin >> ki >> kj;
        cin >> qi >> qj;

        cout << bfs(ki, kj, qi, qj) << endl;
    }

    return 0;
}