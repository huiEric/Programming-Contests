#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 50000 + 10;
const int MAXQ = 50000 + 10;
int father[MAXN], ranks[MAXN], ancestor[MAXN];
int M[MAXN], m[MAXN], up[MAXN], down[MAXN];
vector<int> G[MAXN], Q[MAXN], pos[MAXN];
vector<int> st[MAXN], ed[MAXN], id[MAXN];
int ans[MAXQ];
int N, q;
bool visited[MAXN];

inline void init()
{
    memset(visited, false, sizeof(visited));
    for(int i = 1; i <= N; ++i)
    {
        father[i] = i;
        ranks[i] = 0;
    }
}
int find(int u)
{
    if(father[u] == u) return u;
    int p = father[u];
    father[u] = find(p);
    up[u] = max(up[u], max(up[p], M[p] - m[u]));
    down[u] = max(down[u], max(down[p], M[u] - m[p]));
    M[u] = max(M[u], M[p]);
    m[u] = min(m[u], m[p]);
    return father[u];
}
void Union(int u, int v)
{
    u = find(u);
    v = find(v);
    if(u == v) return;
    if(ranks[u] < ranks[v])
        father[u] = v;
    else
    {
        father[v] = u;
        if(ranks[u] == ranks[v]) ranks[u]++;
    }
}
void dfs(int u)
{
    visited[u] = true;
    //ancestor[u] = u;
    for(int i = 0; i < Q[u].size(); ++i)
    {
        int v = Q[u][i];
        if(visited[v])
        {
            int lca = find(v);
            int index = pos[u][i];
            if(index > 0)
            {
                st[lca].push_back(u);
                ed[lca].push_back(v);
                id[lca].push_back(index);
            }
            else
            {
                st[lca].push_back(v);
                ed[lca].push_back(u);
                id[lca].push_back(-index);
            }
        }
    }
    for(int i = 0; i < G[u].size() ; ++i)
    {
        int v = G[u][i];
        if(visited[v]) continue;
        dfs(v);
        //Union(u, v);
        father[v] = u;
        //ancestor[u] = u;
    }
    for(int i = 0; i < st[u].size(); ++i)
    {
        int s = st[u][i], e = ed[u][i];
        ans[id[u][i]] = max(M[e] - m[s], max(up[s], down[e]));
    }
}

int main()
{
    ios::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    scanf("%d", &N);
    init();
    for(int i = 1; i <= N; ++i)
    {
        int w;
        scanf("%d", &w);
        M[i] = w;
        m[i] = w;
    }
    for(int i = 1; i <= N - 1; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d", &q);
    for(int i = 1; i <= q; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        Q[u].push_back(v);
        pos[u].push_back(i);
        Q[v].push_back(u);
        pos[v].push_back(-i);
    }

    dfs(1);

    for(int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}