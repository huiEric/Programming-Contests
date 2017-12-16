#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

typedef long long ll;
using namespace std;
const int MAXN = 40000 + 10;
const int MAXK = 2 * 10000 + 10;
struct Edge {
    int to, w;
    Edge(int to, int w) : to(to), w(w) {}
};
struct Query {
    int u, v, next;
    ll d;
};
int n, m, k;
vector<Edge> G[MAXN];
Query Q[MAXK];
int head[MAXN];
int father[MAXN], ranks[MAXN], ancestor[MAXN];
bool visited[MAXN];
ll dist[MAXN];

inline void init() {
    memset(visited, false, sizeof(visited));
    memset(dist, 0, sizeof(dist));
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; ++i) {
        father[i] = i;
        ranks[i] = 0;
        G[i].clear();
    }
}

inline void addQuery(int u, int v, int &m) {
    Q[m].u = u; Q[m].v = v; Q[m].d = 0; Q[m].next = head[u]; head[u] = m++;
    Q[m].u = v; Q[m].v = u; Q[m].d = 0; Q[m].next = head[v]; head[v] = m++;
}

int find(int u) {
    if(father[u] == u) 
        return u;
    return father[u] = find(father[u]);
}

void Union(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    if(ranks[u] < ranks[v]) father[u] = v;
    else {
        father[v] = u;
        if(ranks[u] == ranks[v]) ranks[u]++;
    }
}

void LCA(int u) {
    ancestor[u] = u;
    visited[u] = true;
    for(int i = 0; i < G[u].size(); ++i) {
        Edge &e = G[u][i];
        int v = e.to;
        if(!visited[v]) {
            dist[v] = dist[u] + e.w;
            LCA(v);
            Union(u, v);
            ancestor[find(u)] = u;
        }
    }
    for(int i = head[u]; i != -1; i = Q[i].next) {
        Query &query = Q[i];
        if(visited[query.v]) {
            int lca = ancestor[find(query.v)];
            query.d = (dist[query.u] - dist[lca]) + (dist[query.v] - dist[lca]);
        }
    }
}

int main() { 
    std::ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    while(scanf("%d%d", &n, &m) == 2) {
        init();
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            char d[2];
            scanf("%d%d%d%s", &u, &v, &w, d);
            G[u].push_back(Edge(v, w));
            G[v].push_back(Edge(u, w));
        }

        scanf("%d", &k);
        int m = 0;
        for (int i = 0; i < k; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            addQuery(u, v, m);
        }

        LCA(1);

        for (int i = 0; i < k; ++i) {
            bool isolated = G[Q[2 * i].u].empty() || G[Q[2 * i].v].empty();
            if(isolated) Q[2 * i].d = dist[Q[2 * i].u] + dist[Q[2 * i].v];
            printf("%lld\n", Q[2 * i].d);
        }
    }
    return 0;
}