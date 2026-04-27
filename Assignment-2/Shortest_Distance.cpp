#include<bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
vector<pair<int,int>> v[N];
long long dis[N];

class cmp {
public:
    bool operator()(pair<int,long long> a, pair<int,long long> b){
        return a.second > b.second;
    }
};

void dijkstra(int src, int n){
    for(int i = 1; i <= n; i++){
        dis[i] = LLONG_MAX;
    }

    priority_queue<pair<int,long long>, vector<pair<int,long long>>, cmp> pq;

    dis[src] = 0;
    pq.push({src, 0});

    while(!pq.empty()){
        auto [node, cost] = pq.top();
        pq.pop();

        if(cost > dis[node]) continue;

        for(auto [childNode, childCost] : v[node]){
            if(cost + childCost < dis[childNode]){
                dis[childNode] = cost + childCost;
                pq.push({childNode, dis[childNode]});
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,e;
    cin >> n >> e;

    while(e--){
        int a,b,c;
        cin >> a >> b >> c;
        v[a].push_back({b,c});
    }

    int q;
    cin >> q;

    vector<pair<int,int>> queries(q);
    for(int i = 0; i < q; i++){
        cin >> queries[i].first >> queries[i].second;
    }

    unordered_map<int, vector<pair<int,int>>> mp;
    for(int i = 0; i < q; i++){
        int x = queries[i].first;
        int y = queries[i].second;
        mp[x].push_back({i, y});
    }

    vector<long long> ans(q);

    for(auto &it : mp){
        int src = it.first;

        dijkstra(src, n);

        for(auto [idx, dest] : it.second){
            if(dis[dest] == LLONG_MAX) ans[idx] = -1;
            else ans[idx] = dis[dest];
        }
    }

    for(int i = 0; i < q; i++){
        cout << ans[i] << endl;
    }

    return 0;
}